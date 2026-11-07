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

#endif
