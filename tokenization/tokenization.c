#include "tokenization.h"
#include "token_type.c"
#include <malloc.h>

tokens_t tokenize(char *code) {
    tokens_t tokens = {};
    list_alloc(tokens, token_t);

    tokenizers_t tokenizers = make_tokenizers();

    return tokens;
}

tokenizers_t make_tokenizers() {
    tokenizers_t tokenizers = {};
    dict_alloc(tokenizers, tokenizers_item_t);

    dict_set(tokenizers, tokenizers_item_t, tokenizer_t, type, get_token_type_status);

    return tokenizers;
}
