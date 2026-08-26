#ifndef TOKEN_TYPE
#define TOKEN_TYPE

#include "tokenizer.h"

#define TOKEN_TYPE_NAME "TOKEN_TYPE"

typedef enum {
    builtin_type_void,
    builtin_type_uint8,
    builtin_type_int8,
    builtin_type_uint16,
    builtin_type_int16,
    builtin_type_uint32,
    builtin_type_int32,
    builtin_type_uint64,
    builtin_type_int64,
    type_names_count __attribute__((unused))
} builtin_type_t;

typedef struct {
    builtin_type_t name;
} token_type_data_t;

void token_type_init(void);

tokenization_status_t token_type_get_status(char *line);

token_type_data_t token_type_get_data_from(char *line);

void write_token_type_data(token_type_data_t data, char **buffer);

#endif