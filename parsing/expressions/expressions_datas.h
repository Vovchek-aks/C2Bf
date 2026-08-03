#include "../../tokenization/tokenization.h"

#ifndef EXPRESSIONS_DATAS
#define EXPRESSIONS_DATAS

typedef struct {
    token_name_data_t token;
} expression_name_data_t;

typedef union {
    expression_name_data_t as_name;
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