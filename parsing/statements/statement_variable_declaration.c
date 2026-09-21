#include "statement_variable_declaration.h"
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

statement_parsing_result_t statement_variable_declaration_get_data_from(tokens_t tokens, bool is_strict) {
    if (tokens.count < 3)
        return FAILED_TO_PARSE_STATEMENT;
    CHOP_SEMICOLON;

    token_t *equals = find_operator(tokens, operator_equals, chop_direction_front);
    tokens_t left = equals ? split_by(equals, &tokens) : tokens;

    token_t *name = chop_back(&left, token_kind_name);
    if (!name)
        return FAILED_TO_PARSE_STATEMENT;

    type_t *type = parse_type(left, is_strict);
    if (!type)
        return FAILED_TO_PARSE_STATEMENT;

    expression_t *value = equals ? parse_expression(tokens, is_strict) : NULL;
    if (equals && !value) {
        if (is_strict)
            display_parsing_error(list_view_on(equals, tokens_t ), "expression expected after '='.");

        free_type(type);
        return FAILED_TO_PARSE_STATEMENT;
    }

    statement_variable_declaration_data_t data = {type, &name->data.as_name, value};
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