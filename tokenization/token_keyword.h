#include "tokenizer.h"

#ifndef TOKEN_KEYWORD
#define TOKEN_KEYWORD

#define TOKEN_KEYWORD_NAME "TOKEN_KEYWORD"

typedef enum {
    keyword_return,
    keyword_if,
    keyword_else,
    keyword_switch,
    keyword_case,
    keyword_default,
    keyword_for,
    keyword_while,
    keyword_do,
    keyword_break,
    keyword_continue,
    keyword_static,
    keyword_struct,
    keyword_union,
    keyword_enum,
    keyword_typedef,
    keyword_const,
    keyword_sizeof,
    keyword_typeof,
    keywords_count __attribute__((unused))
} keyword_t;

typedef struct {
    keyword_t name;
} token_keyword_data_t;

void token_keyword_init(void);

tokenization_status_t token_keyword_get_status(char *line);

token_keyword_data_t token_keyword_get_data_from(char *line);

void write_token_keyword_data(token_keyword_data_t data, char **buffer);

#endif