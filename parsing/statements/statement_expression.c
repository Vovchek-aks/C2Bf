#include "statement_expression.h"
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

statement_parsing_result_t statement_expression_get_data_from(tokens_t tokens, bool is_strict) {
    if (tokens.count < 2)
        return FAILED_TO_PARSE_STATEMENT;
    CHOP_SEMICOLON;

    expression_t *expression = parse_expression(tokens, false);
    if (!expression)
        return FAILED_TO_PARSE_STATEMENT;

    statement_expression_data_t data = {expression};
    return STATEMENT_PARSED(.as_expression, data);
}

void write_statement_expression_data_from(statement_expression_data_t data, char **buffer) {
    char *line = malloc(EXPRESSION_PRINTING_MAX_LENGTH);
    memset(line, 0, EXPRESSION_PRINTING_MAX_LENGTH);
    char *line_end = line;

    string_extend(&line_end, str_expression_name(data.expression));
    write_expression_data(data.expression, &line_end);

    char *line_copy = line;
    string_for(line_copy, alpha)
        string_append(buffer, alpha);

    free(line);
}

void free_statement_expression_data(statement_expression_data_t data) {
    free_expression(data.expression);
}