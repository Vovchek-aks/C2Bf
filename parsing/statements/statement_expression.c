#include "statement_expression.h"
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "bugprone-sizeof-statement"
#pragma ide diagnostic ignored "modernize-use-nullptr"

statement_parsing_result_t statement_expression_get_data_from(tokens_t tokens) {
    assert(tokens.count >= 2);
    CHOP_SEMICOLON;

    expression_t *expression = parse_expression(tokens);
    if (!expression)
        return FAILED_TO_PARSE_STATEMENT;

    statement_expression_data_t data = {expression};
    return STATEMENT_PARSED(.as_expression, data);
}

void write_statement_expression_data_from(statement_expression_data_t data, char **buffer) {
    string_extend(buffer, "():\n");
    string_extend(buffer, ".expression = ");
    write_expression(data.expression, buffer);
}

void free_statement_expression_data(statement_expression_data_t data) {
    free_expression(data.expression);
}