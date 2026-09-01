#ifndef STATEMENTS_DATAS
#define STATEMENTS_DATAS

#include "../../tokenization/tokenization.h"

typedef struct statement_t statement_t;

typedef LIST(statement_t *) statements_t;

typedef struct {
    expression_t *expression;
} statement_expression_data_t;

typedef struct {
    expression_t *condition;
    statement_t *true_branch;
    statement_t *false_branch;
} statement_if_data_t;

typedef union {
    statement_if_data_t as_if;
    statement_expression_data_t as_expression;
} statement_data_t;

typedef enum {
    statement_parsing_result_fail,
    statement_parsing_result_success,
} statement_parsing_result_status_t;

#define CHOP_SEMICOLON do {                                                                                            \
    if (!chop_operator(&tokens, operator_semicolon, chop_direction_back))                                              \
        return FAILED_TO_PARSE_STATEMENT;                                                                              \
} while (false)

#define FAILED_TO_PARSE_STATEMENT (statement_parsing_result_t) {                                                       \
    .status = statement_parsing_result_fail                                                                            \
}

#define STATEMENT_PARSED(field_name, field_data) (statement_parsing_result_t) {                                        \
    .status = statement_parsing_result_success,                                                                        \
    .data = {                                                                                                          \
        field_name = field_data                                                                                        \
    }                                                                                                                  \
}

typedef struct {
    statement_parsing_result_status_t status;
    statement_data_t data;
} statement_parsing_result_t;

typedef statement_parsing_result_t (*statement_parser_t)(tokens_t tokens);

#endif