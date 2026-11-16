#include "statement_variable_declaration.h"
#include "../types/type_array.h"
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

static bool parse_left_simple(tokens_t left, statement_variable_declaration_data_t *data, bool is_strict) {
    token_t *name = chop_back(&left, token_kind_name);
    if (!name)
        return false;

    data->name = &name->data.as_name;

    if (left.count == 0)
        return false;

    data->type = parse_type(left, is_strict);
    return data->type;
}

static bool parse_left_array(tokens_t left, statement_variable_declaration_data_t *data, bool is_strict) {
    tokens_t original = left;

    if (!chop_operator(&left, operator_close_square, chop_direction_back))
        return false;

    token_t *bracket = get_paired_bracket(left, operator_open_square, operator_close_square, chop_direction_back);
    if (!bracket)
        return false;

    tokens_t simple = split_by(bracket, &left);
    if (!data->value && !left.count) {
        if (is_strict)
            display_parsing_error(list_slice(original, -2, TO_END), "Array length must me specified.");
        return false;
    }

    if (!parse_left_simple(simple, data, is_strict))
        return false;

    expression_t *size = parse_expression(left, is_strict);
    if (left.count && !size) {
        free_type(data->type);
        return false;
    }

    data->type = make_parsed_type_array(data->type, size);
    return true;
}

static bool parse_left(tokens_t left, statement_variable_declaration_data_t *data, bool is_strict) {
    if (parse_left_simple(left, data, is_strict))
        return true;

    return parse_left_array(left, data, is_strict);
}

statement_parsing_result_t statement_variable_declaration_get_data_from(tokens_t tokens, bool is_strict) {
    if (tokens.count < 3)
        return FAILED_TO_PARSE_STATEMENT;
    CHOP_SEMICOLON;

    token_t *equals = find_operator(tokens, operator_equals, chop_direction_front);
    tokens_t left = equals ? split_by(equals, &tokens) : tokens;

    statement_variable_declaration_data_t data;
    data.value = equals ? parse_expression(tokens, is_strict) : NULL;
    if (equals && !data.value) {
        if (is_strict)
            display_parsing_error(list_view_on(equals, tokens_t ), "Expression expected after '='.");
        return FAILED_TO_PARSE_STATEMENT;
    }

    if (!parse_left(left, &data, is_strict)) {
        if (data.value)
            free_expression(data.value);
        return FAILED_TO_PARSE_STATEMENT;
    }

    return STATEMENT_PARSED(.as_variable_declaration, data);
}

void write_statement_variable_declaration_data_from(statement_data_t data, char **buffer) {
    *buffer += sprintf(*buffer, "(\"%s\"):", data.as_variable_declaration.name->name);

    string_extend(buffer, "\n.type = ");
    write_type(data.as_variable_declaration.type, buffer);

    if (!data.as_variable_declaration.value)
        return;

    string_extend(buffer, "\n.value = ");
    write_expression(data.as_variable_declaration.value, buffer);
}

void free_statement_variable_declaration_data(statement_data_t data) {
    free_type(data.as_variable_declaration.type);
    if (data.as_variable_declaration.value)
        free_expression(data.as_variable_declaration.value);
}