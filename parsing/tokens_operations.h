#include "../tokenization/tokenization.h"

#ifndef TOKENS_OPERATIONS
#define TOKENS_OPERATIONS

token_t *chop_front(tokens_t *tokens, token_kind_t kind);

token_t *chop_back(tokens_t *tokens, token_kind_t kind);

#endif
