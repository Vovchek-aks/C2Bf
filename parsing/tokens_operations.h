#ifndef TOKENS_OPERATIONS
#define TOKENS_OPERATIONS

#include "../tokenization/tokenization.h"

typedef enum {
    chop_direction_front,
    chop_direction_back
} chop_direction_t;

token_t *chop_front(tokens_t *tokens, token_kind_t kind);

token_t *chop_back(tokens_t *tokens, token_kind_t kind);

token_t *chop_operator(tokens_t *tokens, operator_t kind, chop_direction_t direction);

token_t *chop_keyword(tokens_t *tokens, keyword_t kind, chop_direction_t direction);

token_t *find_operator(tokens_t tokens,
                       operator_t target,
                       chop_direction_t direction);

token_t *find_keyword(tokens_t tokens,
                      keyword_t target,
                      chop_direction_t direction);

token_t *get_paired_bracket(tokens_t tokens,
                            operator_t target,
                            operator_t initial,
                            chop_direction_t direction);

tokens_t split_by(token_t *separator, tokens_t *right);

void combine(tokens_t *left, tokens_t right);

tokens_t absorb(tokens_t *tokens);

#endif
