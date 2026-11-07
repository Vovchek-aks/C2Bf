#ifndef TYPES
#define TYPES

#include "stdint.h"
#include "type_int.h"
#include "type_void.h"

typedef enum {
    type_kind_void,
    type_kind_int,
    type_kinds_count  __attribute__((unused)),
} type_kind_t;

typedef union {
    type_int_data_t as_int;
    type_void_data_t as_void;
} type_data_t;

typedef struct {
    type_kind_t kind;
    type_data_t data;
    size_t bytes;
} type_t;

void init_types();

type_t *get_type_named(char *name);

type_t *get_type_from_parsed(parsed_type_t *parsed_type);

type_t *get_type_of(expression_t *expression);

bool is_able_to_assign(type_t *left, type_t *right);


#endif
