#include "tokenizer.h"

#ifndef TOKEN_LITERAL
#define TOKEN_LITERAL

#define TOKEN_LITERAL_NAME "TOKEN_LITERAL"

typedef enum {
    int_,
    float_,
    char_,
    str,
    token_literal_kinds __attribute__((unused)),
} token_literal_kind_t;


typedef struct {
    token_literal_kind_t kind;
    char *line;
} token_literal_data_t;

tokenization_status_t token_literal_number_get_status(char *line);

token_literal_data_t token_literal_number_get_data_from(char *line);

token_literal_data_t token_literal_str_or_char_try_get_data_from(char *line);

void write_token_literal_data(token_literal_data_t data, char **buffer);

#endif