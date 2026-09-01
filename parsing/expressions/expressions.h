#ifndef EXPRESSIONS
#define EXPRESSIONS

#include "../../tokenization/tokenization.h"
#include "expressions_datas.h"

#define EXPRESSION_PRINTING_MAX_LENGTH (1024 * 1024)

typedef enum {
    expression_kind_indexing,
    expression_kind_name,
    expression_kind_struct_creation,
    expression_kind_ternary_if,
    expression_kind_literal,
    expression_kind_function_call,
    expression_kind_element_access,
    expression_kinds_count __attribute__((unused))
} expression_kind_t;

struct expression_t {
    tokens_t tokens;
    expression_kind_t kind;
    expression_data_t data;
};

typedef LIST(struct {
    expression_kind_t kind;
    expression_parser_t parse;
}) expression_parsers_t;

void expressions_parsing_init(void);

expression_t *parse_expression(tokens_t tokens);

bool parse_expressions_separated_by(operator_t separator, tokens_t tokens, expressions_t *parts);

bool specifying_parse_expressions_separated_by(operator_t target,
                                               tokens_t tokens,
                                               expressions_t *parts,
                                               bool require_at_least_one_split);

expression_t *strictly_parse_expression(tokens_t tokens);

void write_expression(expression_t *expression, char **buffer);

void print_expression(expression_t *expression);

void free_expression(expression_t *expression);

void free_expressions(expressions_t expressions);

#endif