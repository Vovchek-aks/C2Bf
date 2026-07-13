#include "tokenization.h"
#include "token_type.c"
#include <assert.h>

void tokenization_init(void) {
    token_type_init();
}

tokens_t tokenize(char *code)
{
    tokens_t tokens = {};
    list_alloc(tokens, token_t);

    //    tokenizers_t tokenizers = make_tokenizers();

    list_push(tokens, ((token_t){.kind = c_type,
                                 .data = {uint16}}));

    return tokens;
}

tokenizers_t make_tokenizers(void)
{
    tokenizers_t tokenizers = {};
    dict_alloc(tokenizers, tokenizers_item_t);

    dict_set(tokenizers, tokenizers_item_t, tokenizer_t, c_type, get_token_type_status);

    return tokenizers;
}

void print_tokens(tokens_t tokens)
{
    list_for(tokens, token_t, token)
    {
        print_token(token);
    }
}

static char *str_token_name(token_t token)
{
    switch (token.kind)
    {
    case c_type:
        return TOKEN_TYPE_NAME;
    default:
        assert(0);
    }
}

static char *str_token_data(token_t token)
{
    switch (token.kind)
    {
    case c_type:
        return str_token_type_data(token.data.type);
    default:
        assert(0);
    }
}

void print_token(token_t token)
{
    printf("[%s(%s)]\n", str_token_name(token), str_token_data(token));
}
