#include "statement_if.h"

#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "bugprone-sizeof-statement"
#pragma ide diagnostic ignored "modernize-use-nullptr"

statement_parsing_result_t statement_if_get_data_from(tokens_t tokens) {
    assert(tokens.count >= 6); // if (a) {}

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

    statements_t branches;
    list_sized_alloc(branches, 2);
    if ((!parse_statements_separated_by_keyword(keyword_else, tokens, &branches))
        || branches.count < 1) {
        free_expression(condition);
        free_statements(branches);
        return FAILED_TO_PARSE_STATEMENT;
    }

    statement_t *false_branch = branches.count == 2 ? branches.data[1] : NULL;
    if (branches.count > 2) {
        statements_t slice = {branches.data + 1, branches.count - 2}; // [1:-1]
        list_for(slice, statement) {
            if (statement->kind != statement_kind_if) {
                free_expression(condition);
                free_statements(branches);
                return FAILED_TO_PARSE_STATEMENT;
            }
        }
        for (int idx = 1; idx < branches.count - 1; ++idx)
            branches.data[idx]->data.as_if.false_branch = branches.data[idx + 1];

        false_branch = branches.data[1];
    }

    statement_if_data_t data = {condition, branches.data[0], false_branch};
    list_free(branches);
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