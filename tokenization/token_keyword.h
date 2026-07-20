#include "tokenizer.h"

#ifndef TOKEN_KEYWORD
#define TOKEN_KEYWORD

#define TOKEN_KEYWORD_NAME "TOKEN_KEYWORD"

typedef enum {
    return_,
    if_,
    else_,
    switch_,
    case_,
    default_,
    for_,
    while_,
    do_,
    break_,
    continue_,
    static_,
    struct_,
    union_,
    enum_,
    typedef_,
    const_,
    sizeof_,
    keywords_count
} keyword_t;

typedef struct {
    keyword_t name;
} token_keyword_data_t;

void token_keyword_init(void);

tokenization_status_t token_keyword_get_status(char *line);

token_keyword_data_t token_keyword_get_data_from(char *line);

void write_token_keyword_data(token_keyword_data_t data, char *buffer);

#endif