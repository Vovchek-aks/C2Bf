#include "../tokenization/tokenization.h"

#ifndef TOKENS_OPERATIONS
#define TOKENS_OPERATIONS

typedef enum {
    chop_direction_front,
    chop_direction_back
} chop_direction_t;

token_t *chop_front(tokens_t *tokens, token_kind_t kind);

token_t *chop_back(tokens_t *tokens, token_kind_t kind);

token_t *chop_operator(tokens_t *tokens, operator_kind_t kind, chop_direction_t direction);

token_t *get_paired_bracket(tokens_t *tokens,
                            operator_kind_t target,
                            operator_kind_t initial,
                            chop_direction_t direction);

tokens_t split_by(token_t *separator, tokens_t *right);

#endif
