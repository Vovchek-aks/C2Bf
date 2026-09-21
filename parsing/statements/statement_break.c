#include "statement_break.h"
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

statement_parsing_result_t statement_break_get_data_from(tokens_t tokens, bool is_strict) {
    if (tokens.count < 2)
        return FAILED_TO_PARSE_STATEMENT;
    CHOP_SEMICOLON;

    if (!chop_keyword(&tokens, keyword_break, chop_direction_front))
        return FAILED_TO_PARSE_STATEMENT;

    if (tokens.count > 0)
        return FAILED_TO_PARSE_STATEMENT;

    statement_break_data_t data = {};
    return STATEMENT_PARSED(.as_break, data);
}

void write_statement_break_data_from(statement_data_t data, char **buffer) {
    string_extend(buffer, "();");
}

void free_statement_break_data(statement_data_t data) {
}