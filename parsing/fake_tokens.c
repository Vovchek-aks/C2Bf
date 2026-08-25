#include "fake_tokens.h"

void fake_tokens_init() {
    list_alloc(fake_tokens);
}

void fake_tokens_start_new_list(size_t size) {
    tokens_t tokens;
    list_sized_alloc(tokens, size);
    list_push(fake_tokens, tokens);
}

void fake_tokens_remove_last_list() {
    assert(fake_tokens.count > 0);
    free(list_last(fake_tokens).data);
    fake_tokens.count--;
}

void fake_tokens_append_token(token_t token) {
    list_push(list_last(fake_tokens), token);
}

void fake_tokens_extend(tokens_t tokens) {
    list_for(tokens, token)
        fake_tokens_append_token(token);
}

void fake_tokens_append_token_name(char *name) {
    token_t token = {
            .kind = token_kind_name,
            .data.as_name = {name}
    };
    fake_tokens_append_token(token);
}

void fake_tokens_append_token_literal(token_literal_kind_t kind, char *line) {
    token_t token = {
            .kind = token_kind_literal,
            .data.as_literal = {kind, line}
    };
    fake_tokens_append_token(token);
}

void fake_tokens_append_token_operator(operator_t kind) {
    token_t token = {
            .kind = token_kind_operator,
            .data.as_operator = {kind}
    };
    fake_tokens_append_token(token);
}
