#include "tokenizer.h"

#ifndef TOKEN_TYPE
#define TOKEN_TYPE

#define TOKEN_TYPE_NAME "TOKEN_TYPE"

typedef enum {
    uint8,
    int8,
    uint16,
    int16,
    uint32,
    int32,
    uint64,
    int64,
} type_name_t;

typedef struct {
    type_name_t name;
} token_type_data_t;

void token_type_init(void);

tokenization_status_t get_token_type_status(char *line);

char *str_token_type_data(token_type_data_t data);

#endif