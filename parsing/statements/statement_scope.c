#include "statement_scope.h"
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

statement_parsing_result_t statement_scope_get_data_from(tokens_t tokens) {
    if (tokens.count < 2)
        return FAILED_TO_PARSE_STATEMENT;

    if (!chop_operator(&tokens, operator_open_curly, chop_direction_front))
        return FAILED_TO_PARSE_STATEMENT;
    if (!chop_operator(&tokens, operator_close_curly, chop_direction_back))
        return FAILED_TO_PARSE_STATEMENT;

    tokens_t window = tokens;
    statements_t statements;
    list_sized_alloc(statements, 8);
    while (window.count > 0 && window.data < tokens.data + tokens.count) {
        statement_t *statement = parse_statement(window);
        if (statement) {
            list_push(statements, statement);
            window.data += window.count;
            window.count = tokens.data + tokens.count - window.data;
            continue;
        }

        window.count--;
    }
    if (window.data < tokens.data + tokens.count) {
        free_statements(statements);
        return FAILED_TO_PARSE_STATEMENT;
    }

    statement_scope_data_t data = {statements};
    return STATEMENT_PARSED(.as_scope, data);
}

void write_statement_scope_data_from(statement_scope_data_t data, char **buffer) {
    *buffer += snprintf(*buffer, 20, "(stmts=%llu):", data.statements.count);

    size_t index = 0;
    list_for(data.statements, statement) {
        *buffer += snprintf(*buffer, 20, "\n.statement_%llu = ", index++);
        write_statement(statement, buffer);
    }
}

void free_statement_scope_data(statement_scope_data_t data) {
    free_statements(data.statements);
}