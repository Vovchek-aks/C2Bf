#ifndef TYPES_DATAS
#define TYPES_DATAS

#include "../../tokenization/tokenization.h"

typedef struct parsed_type_t parsed_type_t;

typedef LIST(parsed_type_t *) parsed_types_t;

typedef struct {
    char *name;
} type_name_data_t;

typedef union {
    type_name_data_t as_name;
} parsed_type_data_t;

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
    parsed_type_data_t data;
} type_parsing_result_t;

typedef type_parsing_result_t (*type_parser_t)(tokens_t tokens, bool is_strict);

#endif