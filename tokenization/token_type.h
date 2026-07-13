#include "tokenizer.h"

#ifndef TOKEN_TYPE
#define TOKEN_TYPE

typedef enum {
    int32,
    uint8,
} type_name;

typedef struct {
    type_name name;
} token_type_data_t;

tokenization_status_t get_token_type_status(char *line);

#endif