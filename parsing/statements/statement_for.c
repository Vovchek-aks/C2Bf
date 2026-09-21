#include <stdint-gcc.h>
#include "statement_for.h"

#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

static bool parse_between_brackets(statement_for_data_t *data, tokens_t *between_brackets, bool is_strict) {
    token_t *semicolon = find_operator((*between_brackets), operator_semicolon, chop_direction_front);
    if (!semicolon)
        return false;

    tokens_t before_first = split_by(semicolon, between_brackets);
    combine(&before_first, list_view_on(semicolon, tokens_t));
    if (before_first.count > 1) {
        (*data).before_first = parse_statement(before_first, is_strict);
        if (!(*data).before_first)
            return false;
    }

    semicolon = find_operator((*between_brackets), operator_semicolon, chop_direction_front);
    if (!semicolon)
        return false;

    tokens_t condition = split_by(semicolon, between_brackets);
    (*data).condition = parse_expression(
            condition.count > 0
            ? condition
            : ({
                fake_tokens_new(1);
                fake_tokens_append_token_literal(token_literal_kind_int, "1");
                list_view(fake_tokens_current);
            }),
            is_strict
    );
    if (!(*data).condition) {
        if (data->before_first)
            free_statement((*data).before_first);
        return false;
    }

    if (between_brackets->count > 0) {
        fake_tokens_new((*between_brackets).count + 1);
        fake_tokens_extend((*between_brackets));
        fake_tokens_append_token_operator(operator_semicolon);
        (*data).after_each = parse_statement(list_view(fake_tokens_current), is_strict);
        if (!(*data).after_each) {
            fake_tokens_remove_last_list();
            free_expression((*data).condition);
            if (data->before_first)
                free_statement((*data).before_first);
            return false;
        }
    }

    return true;
}

statement_parsing_result_t statement_for_get_data_from(tokens_t tokens, bool is_strict) {
    if (tokens.count < 6)  // for (;;);
        return FAILED_TO_PARSE_STATEMENT;

    if (!chop_keyword(&tokens, keyword_for, chop_direction_front))
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
    statement_for_data_t data = {};

    tokens_t left = split_by(bracket, &tokens);

    if (!parse_between_brackets(&data, &left, is_strict))
        return FAILED_TO_PARSE_STATEMENT;

    if (tokens.count == 1 && chop_operator(&tokens, operator_semicolon, chop_direction_front))
        return STATEMENT_PARSED(.as_for, data);

    data.body = parse_statement(tokens, is_strict);
    if (!data.body) {
        free_expression(data.condition);
        return FAILED_TO_PARSE_STATEMENT;
    }

    return STATEMENT_PARSED(.as_for, data);
}

void write_statement_for_data_from(statement_for_data_t data, char **buffer) {
    string_extend(buffer, "():");

    if (data.before_first) {
        string_extend(buffer, "\n.before_first = ");
        write_statement(data.before_first, buffer);
    }

    string_extend(buffer, "\n.condition = ");
    write_expression(data.condition, buffer);

    if (data.body) {
        string_extend(buffer, "\n.body = ");
        write_statement(data.body, buffer);
    }

    if (data.after_each) {
        string_extend(buffer, "\n.after_each = ");
        write_statement(data.after_each, buffer);
    }
}

void free_statement_for_data(statement_for_data_t data) {
    free_expression(data.condition);
    if (data.before_first)
        free_statement(data.before_first);
    if (data.after_each)
        free_statement(data.after_each);
    if (data.body)
        free_statement(data.body);
}