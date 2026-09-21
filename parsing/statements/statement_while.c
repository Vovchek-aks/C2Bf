#include "statement_while.h"

#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

statement_parsing_result_t statement_while_get_data_from(tokens_t tokens, bool is_strict) {
    if (tokens.count < 5)  // while (c);
        return FAILED_TO_PARSE_STATEMENT;

    if (!chop_keyword(&tokens, keyword_while, chop_direction_front))
        return FAILED_TO_PARSE_STATEMENT;

    if (!chop_operator(&tokens, operator_open_round, chop_direction_front))
        return FAILED_TO_PARSE_STATEMENT;

    token_t *bracket = get_paired_bracket(tokens,
                                          operator_close_round,
                                          operator_open_round,
                                          chop_direction_front);
    if (!bracket) {
        if (is_strict)
            display_parsing_error(list_view_on(tokens.data - 1, tokens_t),
                                  "Bracket was newer closed.");
        return FAILED_TO_PARSE_STATEMENT;
    }

    tokens_t left = split_by(bracket, &tokens);

    statement_while_data_t data = {};
    data.condition = parse_expression(left, is_strict);
    if (!data.condition)
        return FAILED_TO_PARSE_STATEMENT;

    if (tokens.count == 1 && chop_operator(&tokens, operator_semicolon, chop_direction_front))
        return STATEMENT_PARSED(.as_while, data);

    data.body = parse_statement(tokens, is_strict);
    if (!data.body) {
        free_expression(data.condition);
        return FAILED_TO_PARSE_STATEMENT;
    }

    return STATEMENT_PARSED(.as_while, data);
}

void write_statement_while_data_from(statement_data_t data, char **buffer) {
    string_extend(buffer, "():");

    string_extend(buffer, "\n.condition = ");
    write_expression(data.as_while.condition, buffer);

    if (!data.as_while.body)
        return;

    string_extend(buffer, "\n.body = ");
    write_statement(data.as_while.body, buffer);
}

void free_statement_while_data(statement_data_t data) {
    free_expression(data.as_while.condition);
    if (data.as_while.body)
        free_statement(data.as_while.body);
}