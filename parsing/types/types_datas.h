#ifndef TYPES_DATAS
#define TYPES_DATAS

#include "../../tokenization/tokenization.h"

typedef struct type_t type_t;

typedef LIST(type_t *) types_t;

typedef struct {
    token_type_data_t *token;
} type_builtin_data_t;

typedef union {
    type_builtin_data_t as_builtin;
} type_data_t;

typedef enum {
    type_parsing_result_fail,
    type_parsing_result_success,
} type_parsing_result_status_t;

#define FAILED_TO_PARSE_TYPE (type_parsing_result_t) {                                                                 \
    .status = type_parsing_result_fail                                                                                 \
}

#define TYPE_PARSED(field_name, field_data) (type_parsing_result_t) {                                                  \
    .status = type_parsing_result_success,                                                                             \
    .data = {                                                                                                          \
        field_name = field_data                                                                                        \
    }                                                                                                                  \
}

typedef struct {
    type_parsing_result_status_t status;
    type_data_t data;
} type_parsing_result_t;

typedef type_parsing_result_t (*type_parser_t)(tokens_t tokens, bool is_strict);

#endif