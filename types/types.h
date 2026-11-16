#ifndef TYPES
#define TYPES

#include "stdint.h"
#include "type_datas.h"

typedef enum {
    type_kind_void,
    type_kind_int,
    type_kind_array,
    type_kinds_count  __attribute__((unused)),
} type_kind_t;

struct type {
    type_kind_t kind;
    type_data_t data;
    size_t bytes;
};

void init_types();

type_t *get_type_named(char *name);

type_t *get_type_from_parsed(parsed_type_t *parsed_type);

type_t *get_type_of(expression_t *expression);

bool is_able_to_assign(type_t *left, type_t *right);

#endif
