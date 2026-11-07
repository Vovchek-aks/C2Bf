#ifndef PARSED_TYPES
#define PARSED_TYPES

#include "../../tokenization/tokenization.h"
#include "types_datas.h"

#define TYPE_PRINTING_MAX_LENGTH (1024 * 1024)

typedef enum {
    parsed_type_kind_name,
    parsed_type_kinds_count __attribute__((unused))
} parsed_type_kind_t;

struct parsed_type_t {
    tokens_t tokens;
    parsed_type_kind_t kind;
    parsed_type_data_t data;
};

typedef LIST(struct {
     parsed_type_kind_t kind;
     type_parser_t parse;
}) type_parsers_t;

void init_types_parsing(void);

parsed_type_t *parse_type(tokens_t tokens, bool is_strict);

void write_type(parsed_type_t *type, char **buffer);

void print_type(parsed_type_t *type);

void free_type(parsed_type_t *type);

void free_types(types_t types);


#endif