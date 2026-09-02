#include "statement_if.h"

#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

static bool try_parse_branches(tokens_t *tokens, statement_t **true_branch, statement_t **false_branch) {
    statements_t branches;
    list_sized_alloc(branches, 2);
    if ((!parse_statements_separated_by_keyword(keyword_else, (*tokens), &branches))
        || branches.count == 0) {
        free_statements(branches);
        return false;
    }

    *true_branch = branches.data[0];
    *false_branch = branches.count > 1 ? branches.data[1] : NULL;

    if (branches.count < 2) {
        list_free(branches);
        return true;
    }

    statements_t slice = list_slice(branches, 1, -1);
    list_for(slice, statement) {
        if (statement->kind != statement_kind_if) {
            free_statements(branches);
            return false;
        }
        statement->data.as_if.false_branch = slice.data[FOR_IDX + 1];
    }
    list_free(branches);
    return true;
}

statement_parsing_result_t statement_if_get_data_from(tokens_t tokens) {
    if (tokens.count < 6) // if (a) {}
        return FAILED_TO_PARSE_STATEMENT;

    if (!chop_keyword(&tokens, keyword_if, chop_direction_front))
        return FAILED_TO_PARSE_STATEMENT;

    if (!chop_operator(&tokens, operator_open_round, chop_direction_front))
        return FAILED_TO_PARSE_STATEMENT;

    token_t *bracket = get_paired_bracket(tokens, operator_close_round, operator_open_round,
                                          chop_direction_front);
    if (!bracket)
        return FAILED_TO_PARSE_STATEMENT;

    tokens_t left = split_by(bracket, &tokens);
    expression_t *condition = parse_expression(left);
    if (!condition)
        return FAILED_TO_PARSE_STATEMENT;

    statement_if_data_t data = {condition};
    if (!try_parse_branches(&tokens, &data.true_branch, &data.false_branch)) {
        free_expression(condition);
        return FAILED_TO_PARSE_STATEMENT;
    }

    return STATEMENT_PARSED(.as_if, data);
}

void write_statement_if_data_from(statement_if_data_t data, char **buffer) {
    string_extend(buffer, "():");

    string_extend(buffer, "\n.condition = ");
    write_expression(data.condition, buffer);

    string_extend(buffer, "\n.true_branch = ");
    write_statement(data.true_branch, buffer);

    if (data.false_branch) {
        string_extend(buffer, "\n.false_branch = ");
        write_statement(data.false_branch, buffer);
    }
}

void free_statement_if_data(statement_if_data_t data) {
    free_expression(data.condition);
    free_statement(data.true_branch);
    if (data.false_branch)
        free_statement(data.false_branch);
}