#include "statement_return.h"
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

statement_parsing_result_t statement_return_get_data_from(tokens_t tokens, bool is_strict) {
    if (tokens.count < 2)
        return FAILED_TO_PARSE_STATEMENT;
    CHOP_SEMICOLON;

    if (!chop_keyword(&tokens, keyword_return, chop_direction_front))
        return FAILED_TO_PARSE_STATEMENT;

    if (tokens.count == 0)
        return STATEMENT_PARSED(.as_return, (statement_return_data_t) {.value = NULL});

    expression_t *value = parse_expression(tokens, is_strict);
    if (!value)
        return FAILED_TO_PARSE_STATEMENT;

    statement_return_data_t data = {value};
    return STATEMENT_PARSED(.as_return, data);
}

void write_statement_return_data_from(statement_return_data_t data, char **buffer) {
    string_extend(buffer, "()");
    string_append(buffer, data.value ? ':' : ';');

    if (data.value) {
        string_extend(buffer, "\n.value = ");
        write_expression(data.value, buffer);
    }
}

void free_statement_return_data(statement_return_data_t data) {
    free_expression(data.value);
}