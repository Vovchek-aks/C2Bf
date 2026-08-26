#ifndef TOKEN_LITERAL
#define TOKEN_LITERAL

#include "tokenizer.h"

#define TOKEN_LITERAL_NAME "TOKEN_LITERAL"

typedef enum {
    token_literal_kind_int,
    token_literal_kind_float,
    token_literal_kind_char,
    token_literal_kind_str,
    token_literal_kinds_count __attribute__((unused)),
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