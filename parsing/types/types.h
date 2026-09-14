#ifndef TYPES
#define TYPES

#include "../../tokenization/tokenization.h"
#include "types_datas.h"

#define TYPE_PRINTING_MAX_LENGTH (1024 * 1024)

typedef enum {
    type_kind_builtin,
    type_kinds_count __attribute__((unused))
} type_kind_t;

struct type_t {
    tokens_t tokens;
    type_kind_t kind;
    type_data_t data;
};

typedef LIST(struct {
     type_kind_t kind;
     type_parser_t parse;
}) type_parsers_t;

void init_types_parsing(void);

type_t *parse_type(tokens_t tokens, bool is_strict);

void write_type(type_t *type, char **buffer);

void print_type(type_t *type);

void free_type(type_t *type);

void free_types(types_t types);


#endif