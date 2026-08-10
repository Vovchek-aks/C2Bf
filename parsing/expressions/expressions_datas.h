#include "../../tokenization/tokenization.h"

#ifndef EXPRESSIONS_DATAS
#define EXPRESSIONS_DATAS

typedef struct expression_t expression_t;

typedef struct {
    token_name_data_t *token;
} expression_name_data_t;

typedef struct {
    token_literal_data_t *token;
} expression_literal_data_t;

typedef struct {
    expression_t *source;
    token_name_data_t *element;
} expression_element_access_data_t;

typedef union {
    expression_name_data_t as_name;
    expression_literal_data_t as_literal;
    expression_element_access_data_t as_element_access;
} expression_data_t;

typedef enum {
    expression_parsing_result_fail,
    expression_parsing_result_success,
} expression_parsing_result_status_t;

#define FAILED_TO_PARSE_EXPRESSION (expression_parsing_result_t) {                                                     \
    .status = expression_parsing_result_fail                                                                           \
}

#define EXPRESSION_PARSED(field_name, field_data) (expression_parsing_result_t) {                                      \
    .status = expression_parsing_result_success,                                                                       \
    .data = {                                                                                                          \
        field_name = field_data                                                                                        \
    }                                                                                                                  \
}

typedef struct {
    expression_parsing_result_status_t status;
    expression_data_t data;
} expression_parsing_result_t;

typedef expression_parsing_result_t (*expression_parser_t)(tokens_t tokens);

#endif