#include "tokens_operations.h"
#include "../data_structures/data_structures.h"
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

token_t *chop_operator(tokens_t *tokens, operator_kind_t kind, chop_direction_t direction) {
    tokens_t changed_tokens = *tokens;
    token_t *op = (direction == chop_direction_front ? chop_front : chop_back)(&changed_tokens, token_kind_operator);
    if (!op || op->data.as_operator.name != kind)
        return NULL;

    *tokens = changed_tokens;
    return op;
}

token_t *get_paired_bracket(tokens_t *tokens,
                            operator_kind_t target,
                            operator_kind_t initial,
                            chop_direction_t direction) {
    tokens_t changed_tokens = *tokens;
    size_t level = 1;
    token_t *op;
    while (changed_tokens.count > 0) {
        op = chop_operator(&changed_tokens, target, direction);
        if (op && --level == 0)
            break;

        op = chop_operator(&changed_tokens, initial, direction);
        if (op) {
            level++;
            continue;
        }

        changed_tokens.count--;
        if (direction == chop_direction_front)
            changed_tokens.data++;
    }

    if (level > 0)
        return NULL;

    return op;
}

tokens_t split_by(token_t *separator, tokens_t *right) {
    size_t index = separator - right->data;

    tokens_t left = {
        .data = right->data,
        .count = index
    };

    right->data = &right->data[index + 1];
    right->count -= index + 1;

    return left;
}
