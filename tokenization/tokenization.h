#include "token_type.h"
#include "token_name.h"
#include "tokenizer.h"
#include "../data_structures/data_structures.h"

#ifndef TOKENIZATION
#define TOKENIZATION

#define TOKEN_MAX_LENGTH 255

typedef enum {
    type_,
    name,
    operator_,
    keyword,
    literal,
    token_kinds_count
} token_kind_t;

typedef union {
    token_type_data_t type;
    token_name_data_t name;
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

void tokenization_init(void);

tokens_t tokenize(char *code);

token_data_t get_data_from(char *line, token_kind_t kind);

void print_token(token_t token);

void print_tokens(tokens_t tokens);

#endif