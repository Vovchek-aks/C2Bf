#include "tokens_operations.h"
#include <assert.h>

token_t *chop_front(tokens_t *tokens, token_kind_t kind) {
    assert(tokens->count > 0);

    if (tokens->data[0].kind != kind)
        return NULL;

    token_t *token = &tokens->data[0];
    tokens->data++;
    tokens->count--;
    return token;
}

token_t *chop_back(tokens_t *tokens, token_kind_t kind) {
    assert(tokens->count > 0);

    if (tokens->data[tokens->count - 1].kind != kind)
        return NULL;

    token_t *token = &tokens->data[tokens->count - 1];
    tokens->count--;
    return token;
}
