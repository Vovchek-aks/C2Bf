#ifndef TOKENIZATION
#define TOKENIZATION

#include "token_type.h"
#include "token_name.h"
#include "token_operator.h"
#include "token_keyword.h"
#include "token_literal.h"
#include "tokenizer.h"
#include "../data_structures.h"

#define TOKEN_MAX_LENGTH 255

typedef enum {
    token_kind_type,
    token_kind_name,
    token_kind_operator,
    token_kind_keyword,
    token_kind_literal,
    token_kinds_count __attribute__((unused))
} token_kind_t;

typedef union {
    token_type_data_t as_type;
    token_name_data_t as_name;
    token_operator_data_t as_operator;
    token_keyword_data_t as_keyword;
    token_literal_data_t as_literal;
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

typedef LIST(token_t) tokens_t;

void tokenization_init(void);

tokens_t tokenize(char *code);

token_data_t get_data_from(char *line, token_kind_t kind);

void print_token(token_t token);

void print_tokens(tokens_t tokens);

#endif