#ifndef STATEMENTS
#define STATEMENTS

#include "../../tokenization/tokenization.h"
#include "statements_datas.h"

#define STATEMENT_PRINTING_MAX_LENGTH (1024 * 1024)

typedef enum {
    statement_kind_expression,
    statement_kind_if,
    statement_kind_while,
    statement_kind_do_while,
    statement_kind_scope,
    statement_kind_variable_definition,
    statement_kind_assignment,
    statement_kind_return,
    statement_kind_break,
    statement_kind_continue,
    statement_kinds_count __attribute__((unused))
} statement_kind_t;

struct statement_t {
    tokens_t tokens;
    statement_kind_t kind;
    statement_data_t data;
};

typedef LIST(struct {
    statement_kind_t kind;
    statement_parser_t parse;
}) statement_parsers_t;

void statements_parsing_init(void);

statement_t *parse_statement(tokens_t tokens);

statement_t *strictly_parse_statement(tokens_t tokens);

bool parse_statements_separated_by_operator(operator_t separator, tokens_t tokens, statements_t *parts);

bool specifying_parse_statements_separated_by_operator(operator_t target,
                                                       tokens_t tokens,
                                                       statements_t *parts,
                                                       bool require_at_least_one_split);

bool parse_statements_separated_by_keyword(keyword_t separator, tokens_t tokens, statements_t *parts);

bool specifying_parse_statements_separated_by_keyword(keyword_t target,
                                                      tokens_t tokens,
                                                      statements_t *parts,
                                                      bool require_at_least_one_split);

void write_statement(statement_t *statement, char **buffer);

void print_statement(statement_t *statement);

void free_statement(statement_t *statement);

void free_statements(statements_t statements);


#endif