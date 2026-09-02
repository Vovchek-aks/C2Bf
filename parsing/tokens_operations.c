#include "tokens_operations.h"
#include <assert.h>
#pragma ide diagnostic ignored "modernize-use-nullptr"

token_t *chop_front(tokens_t *tokens, token_kind_t kind) {
    assert(tokens->count > 0);

    if (tokens->data[0].kind != kind && kind != TOKEN_ANY_KIND)
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

#define CHOP_TOKEN_KIND(function_name, kind_t, token_kind, path_from_data)                                             \
    token_t *function_name(tokens_t *tokens, kind_t kind, chop_direction_t direction) {                                \
        tokens_t changed_tokens = *tokens;                                                                             \
        token_t *op = (direction == chop_direction_front ? chop_front : chop_back)(&changed_tokens, token_kind);       \
        if (!op || op->data path_from_data != kind)                                                                    \
            return NULL;                                                                                               \
        *tokens = changed_tokens;                                                                                      \
        return op;                                                                                                     \
    }

CHOP_TOKEN_KIND(chop_operator, operator_t, token_kind_operator, .as_operator.name)

CHOP_TOKEN_KIND(chop_keyword, keyword_t , token_kind_keyword, .as_keyword.name)

#define FIND_TOKEN_KIND(function_name, target_t, chop)                                                                 \
    token_t *function_name(tokens_t tokens,                                                                            \
                           target_t target,                                                                            \
                           chop_direction_t direction) {                                                               \
        while (tokens.count > 0) {                                                                                     \
            token_t *op = chop(&tokens, target, direction);                                                            \
            if (op)                                                                                                    \
                return op;                                                                                             \
                                                                                                                       \
            tokens.count--;                                                                                            \
            if (direction == chop_direction_front)                                                                     \
                tokens.data++;                                                                                         \
        }                                                                                                              \
                                                                                                                       \
        return NULL;                                                                                                   \
    }

FIND_TOKEN_KIND(find_operator, operator_t , chop_operator)

FIND_TOKEN_KIND(find_keyword, keyword_t , chop_keyword)


token_t *get_paired_bracket(tokens_t tokens,
                            operator_t target,
                            operator_t initial,
                            chop_direction_t direction) {
    size_t level = 1;
    token_t *op;
    while (tokens.count > 0) {
        op = chop_operator(&tokens, target, direction);
        if (op && --level == 0)
            break;

        op = chop_operator(&tokens, initial, direction);
        if (op) {
            level++;
            continue;
        }

        tokens.count--;
        if (direction == chop_direction_front)
            tokens.data++;
    }

    if (level > 0)
        return NULL;

    return op;
}

tokens_t split_by(token_t *separator, tokens_t *right) {
    assert(right->data <= separator && separator < right->data + right->count);

    size_t index = separator - right->data;

    tokens_t left = {
        .data = right->data,
        .count = index
    };

    right->data = &right->data[index + 1];
    right->count -= index + 1;

    return left;
}

void combine(tokens_t *left, tokens_t right) {
    assert(left->data + left->count <= right.data || !left->data);

    if (!left->data) {
        *left = right;
        return;
    }

    left->count = right.data + right.count - left->data;
}

tokens_t absorb(tokens_t *tokens) {
    tokens_t new_tokens = *tokens;
    tokens->count = 0;
    tokens->data = 0;
    return new_tokens;
}
