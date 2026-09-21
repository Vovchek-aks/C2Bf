#include "statement_do_while.h"

#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

statement_parsing_result_t statement_do_while_get_data_from(tokens_t tokens, bool is_strict) {
    if (tokens.count < 8)  // do {} while (c);
        return FAILED_TO_PARSE_STATEMENT;
    CHOP_SEMICOLON;

    if (!chop_keyword(&tokens, keyword_do, chop_direction_front))
        return FAILED_TO_PARSE_STATEMENT;

    if (!chop_operator(&tokens, operator_close_round, chop_direction_back))
        return FAILED_TO_PARSE_STATEMENT;

    token_t *bracket = get_paired_bracket(tokens,
                                          operator_open_round,
                                          operator_close_round,
                                          chop_direction_back);
    if (!bracket)
        return FAILED_TO_PARSE_STATEMENT;

    tokens_t left = split_by(bracket, &tokens);
    statement_while_data_t data;
    data.condition = parse_expression(tokens, is_strict);
    if (!data.condition)
        return FAILED_TO_PARSE_STATEMENT;

    if (!chop_keyword(&left, keyword_while, chop_direction_back))
        return FAILED_TO_PARSE_STATEMENT;

    data.body = parse_statement(left, is_strict);
    if (!data.body) {
        free_expression(data.condition);
        return FAILED_TO_PARSE_STATEMENT;
    }

    return STATEMENT_PARSED(.as_do_while, data);
}

void write_statement_do_while_data_from(statement_while_data_t data, char **buffer) {
    write_statement_while_data_from(data, buffer);
}

void free_statement_do_while_data(statement_while_data_t data) {
    free_statement_while_data(data);
}