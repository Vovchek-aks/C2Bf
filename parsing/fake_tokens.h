#ifndef FAKE_TOKENS
#define FAKE_TOKENS

#include "../data_structures/data_structures.h"
#include "../tokenization/tokenization.h"

typedef LIST(tokens_t) fake_tokens_t;

static fake_tokens_t fake_tokens;

void fake_tokens_init();

void fake_tokens_start_new_list(size_t size);

#define fake_tokens_last_list list_last(fake_tokens)

void fake_tokens_remove_last_list();

void fake_tokens_append_token(token_t token);

void fake_tokens_extend(tokens_t tokens);

void fake_tokens_append_token_name(char *name);

void fake_tokens_append_token_literal(token_literal_kind_t kind, char *line);

void fake_tokens_append_token_operator(operator_t kind);

#endif