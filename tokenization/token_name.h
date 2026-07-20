#include "tokenizer.h"

#ifndef TOKEN_NAME
#define TOKEN_NAME

#define TOKEN_NAME_NAME "TOKEN_NAME"

typedef struct {
    char *line;
} token_name_data_t;

tokenization_status_t token_name_get_status(char *line);

token_name_data_t token_name_get_data_from(char *line);

void write_token_name_data(token_name_data_t data, char *buffer);

#endif