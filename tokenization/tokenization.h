#include "token_type.h"
#include "tokenizer.h"
#include "data_structures/data_structures.h"

#ifndef TOKENIZATION
#define TOKENIZATION

typedef enum {
    type,
    name,
    operator,
    keyword,
    literal,
} token_kind_t;


typedef union {
    token_type_data_t type;
} token_data_t;


typedef struct {
    size_t line;
    size_t symbol;
    char *symbols;
} token_info_t;


typedef struct {
    token_kind_t kind;
    token_data_t data;
    token_info_t info;
} token_t;


typedef key_value(token_kind_t, tokenizer_t) tokenizers_item_t;
typedef DICT(tokenizers_item_t) tokenizers_t;

typedef LIST(token_t) tokens_t;

tokens_t tokenize(char *code);

tokenizers_t make_tokenizers();

#endif