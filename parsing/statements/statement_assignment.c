#include "statement_assignment.h"
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

static LIST(expression_kind_t) left_values;

void init_assignment_parsing() {
    list_alloc(left_values);
    list_push(left_values, expression_kind_element_access);
    list_push(left_values, expression_kind_indexing);
    list_push(left_values, expression_kind_name);
}

statement_parsing_result_t statement_assignment_get_data_from(tokens_t tokens, bool is_strict) {
    if (tokens.count < 4) // aboba = 0;
        return FAILED_TO_PARSE_STATEMENT;
    CHOP_SEMICOLON;

    token_t *equals = find_operator(tokens, operator_equals, chop_direction_front);
    if (!equals)
        return FAILED_TO_PARSE_STATEMENT;

    tokens_t left = split_by(equals, &tokens);
    statement_assignment_data_t data;

    data.left = parse_expression(left, is_strict);
    if (!data.left)
        return FAILED_TO_PARSE_STATEMENT;

    if (!list_contains(left_values, data.left->kind)) {
        if (is_strict)
            display_parsing_error(left, "Expression is not assignable");
        return FAILED_TO_PARSE_STATEMENT;
    }

    data.right = parse_expression(tokens, is_strict);
    if (!data.right) {
        free_expression(data.left);
        return FAILED_TO_PARSE_STATEMENT;
    }

    return STATEMENT_PARSED(.as_assignment, data);
}

void write_statement_assignment_data_from(statement_data_t data, char **buffer) {
    string_extend(buffer, "():");

    string_extend(buffer, "\n.left = ");
    write_expression(data.as_assignment.left, buffer);

    string_extend(buffer, "\n.right = ");
    write_expression(data.as_assignment.right, buffer);
}

void free_statement_assignment_data(statement_data_t data) {
    free_expression(data.as_assignment.left);
    free_expression(data.as_assignment.right);
}