#include "statements.h"
#include "stdio.h"
#include "statement_expression.c"
#include "statement_if.c"
#include "statement_scope.c"
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

statement_parsers_t statement_parsers;

#define statement_parsers_push(kind_to_set, parser_to_set) do {                                                        \
    typeof(*statement_parsers.data) element = { kind_to_set, parser_to_set };                                          \
    list_push(statement_parsers, element);                                                                             \
} while(0)

void statements_parsing_init(void) {
    list_alloc(statement_parsers);
    statement_parsers_push(statement_kind_expression, statement_expression_get_data_from);
    statement_parsers_push(statement_kind_if, statement_if_get_data_from);
    statement_parsers_push(statement_kind_scope, statement_scope_get_data_from);
}

statement_t *parse_statement(tokens_t tokens) {
    assert(tokens.capacity == 0);

    list_for(statement_parsers, parser) {
        statement_parsing_result_t result = parser.parse(tokens);
        if (result.status == statement_parsing_result_fail)
            continue;

        statement_t *statement = malloc(sizeof(statement_t));
        statement->tokens = tokens;
        statement->kind = parser.kind;
        statement->data = result.data;

        return statement;
    }

    return NULL;
}

statement_t *strictly_parse_statement(tokens_t tokens) {
    statement_t *statement = parse_statement(tokens);
    if (statement)
        return statement;

    printf("Cannot parse statement from:\n");
    print_tokens(tokens);
    assert(false);
}

PARSER_TOKENS_SEPARATOR(parse_statements_separated_by_operator, specifying_parse_statements_separated_by_operator,
                        statements_t, operator_t, find_operator, parse_statement)

PARSER_TOKENS_SEPARATOR(parse_statements_separated_by_keyword, specifying_parse_statements_separated_by_keyword,
                        statements_t, keyword_t, find_keyword, parse_statement)

static char *str_statement_name(statement_t *statement) {
    switch (statement->kind) {
        case statement_kind_expression:
            return STATEMENT_EXPRESSION_NAME;
        case statement_kind_if:
            return STATEMENT_IF_NAME;
        case statement_kind_scope:
            return STATEMENT_SCOPE_NAME;
        default:
            printf("Statement has no name\n");
            assert(false);
    }
}

static void write_statement_data(statement_t *statement, char **buffer) {
    switch (statement->kind) {
        case statement_kind_expression:
            return write_statement_expression_data_from(statement->data.as_expression, buffer);
        case statement_kind_if:
            return write_statement_if_data_from(statement->data.as_if, buffer);
        case statement_kind_scope:
            return write_statement_scope_data_from(statement->data.as_scope, buffer);
        default:
            printf("Statement cannot write data\n");
            assert(false);
    }
}

char statement_print_buffer[STATEMENT_PRINTING_MAX_LENGTH] = {};

void print_statement(statement_t *statement) {
    char *line_end = statement_print_buffer;
    write_statement(statement, &line_end);

    printf("%s\n", statement_print_buffer);
    memset(statement_print_buffer, 0, STATEMENT_PRINTING_MAX_LENGTH);
}

void write_statement(statement_t *statement, char **buffer) {
    char *line = malloc(STATEMENT_PRINTING_MAX_LENGTH);
    memset(line, 0, STATEMENT_PRINTING_MAX_LENGTH);
    char *line_end = line;

    string_extend(&line_end, str_statement_name(statement));
    write_statement_data(statement, &line_end);

    adjust_level(line, buffer);
    free(line);
}

void free_statement(statement_t *statement) {
    switch (statement->kind) {
        case statement_kind_expression:
            free_statement_expression_data(statement->data.as_expression);
            break;
        case statement_kind_if:
            free_statement_if_data(statement->data.as_if);
            break;
        case statement_kind_scope:
            free_statement_scope_data(statement->data.as_scope);
            break;
        default:
            printf("Cannot free statement\n");
            assert(false);
    }

    free(statement);
}

void free_statements(statements_t statements) {
    list_for(statements, statement)
        free_statement(statement);

    list_free(statements);
}
