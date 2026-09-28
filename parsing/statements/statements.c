#include "statements.h"
#include "stdio.h"
#include "statement_expression.c"
#include "statement_if.c"
#include "statement_scope.c"
#include "statement_return.c"
#include "statement_variable_declaration.c"
#include "statement_while.c"
#include "statement_do_while.c"
#include "statement_for.c"
#include "statement_break.c"
#include "statement_continue.c"
#include "statement_assignment.c"
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

statement_parsers_t statement_parsers;

DICT(statement_kind_t, char *) statement_names;

typedef void (*statement_writer)(statement_data_t, char **);
DICT(statement_kind_t, statement_writer) statement_writers;

typedef void (*statement_freer)(statement_data_t);
DICT(statement_kind_t, statement_freer) statement_freers;

#define register_statement(_statement) do {                                                                            \
    statement_kind_t kind = CONCAT(statement_kind, _statement);                                                        \
    typeof(*statement_parsers.data) element = {                                                                        \
        kind,                                                                                                          \
        CONCAT(CONCAT(statement, _statement), _get_data_from)                                                          \
    };                                                                                                                 \
    list_push(statement_parsers, element);                                                                             \
    dict_set(statement_names, kind, CONCAT(CONCAT(STATEMENT, _statement), _NAME));                                     \
    dict_set(statement_writers, kind, CONCAT(CONCAT(write_statement, _statement), _data_from));                        \
    dict_set(statement_freers, kind, CONCAT(CONCAT(free_statement, _statement), _data));                               \
} while(0)

void init_statements_parsing(void) {
    list_alloc(statement_parsers);
    list_alloc(statement_names);
    list_alloc(statement_writers);
    list_alloc(statement_freers);

    register_statement(_expression);
    register_statement(_if);
    register_statement(_scope);
    register_statement(_return);
    register_statement(_variable_declaration);
    register_statement(_while);
    register_statement(_do_while);
    register_statement(_for);
    register_statement(_break);
    register_statement(_continue);
    register_statement(_assignment);

    init_assignment_parsing();
}

statement_t *parse_statement(tokens_t tokens, bool is_strict) {
    assert(tokens.capacity == 0);
    assert(tokens.count > 0);

    list_for(statement_parsers, parser) {
        statement_parsing_result_t result = parser.parse(tokens, is_strict);
        if (result.status == statement_parsing_result_fail)
            continue;

        statement_t *statement = malloc(sizeof(statement_t));
        statement->tokens = tokens;
        statement->kind = parser.kind;
        statement->data = result.data;

        return statement;
    }

    if (!is_strict)
        return NULL;

    display_parsing_error(tokens, "Cannot identify statement.");
}

PARSER_TOKENS_SEPARATOR(parse_statements_separated_by_operator, statements_t, operator_t, find_operator,
                        parse_statement, "Cannot divide by statements.")

PARSER_TOKENS_SEPARATOR(parse_statements_separated_by_keyword, statements_t, keyword_t, find_keyword,
                        parse_statement, "Cannot divide by statements.")

static char *str_statement_name(statement_t *statement) {
    char *name = dict_get(statement_names, statement->kind, NULL);
    if (name)
        return name;

    printf("Statement has no name\n");
    assert(false);
}

static void write_statement_data(statement_t *statement, char **buffer) {
    statement_writer writer = dict_get(statement_writers, statement->kind, NULL);
    if (!writer) {
        printf("Statement cannot write data\n");
        assert(false);
    }
    writer(statement->data, buffer);
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
    statement_freer freer = dict_get(statement_freers, statement->kind, NULL);
    if (!freer) {
        printf("Cannot free statement\n");
        assert(false);
    }
    freer(statement->data);
    free(statement);
}

void free_statements(statements_t statements) {
    list_for(statements, statement)
        free_statement(statement);

    list_free(statements);
}
