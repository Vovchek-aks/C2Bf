#include "tokenization.h"
#include "token_type.c"
#include "token_name.c"
#include "token_operator.c"
#include "token_keyword.c"
#include "token_literal.c"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>

static tokenizers_t tokenizers;

void tokenization_init(void) {
    dict_alloc(tokenizers, tokenizers_item_t);
    dict_set(tokenizers, tokenizers_item_t, tokenizer_t, token_kind_type, token_type_get_status);
    dict_set(tokenizers, tokenizers_item_t, tokenizer_t, token_kind_keyword, token_keyword_get_status);
    dict_set(tokenizers, tokenizers_item_t, tokenizer_t, token_kind_name, token_name_get_status);
    dict_set(tokenizers, tokenizers_item_t, tokenizer_t, token_kind_operator, token_operator_get_status);
    dict_set(tokenizers, tokenizers_item_t, tokenizer_t, token_kind_literal, token_literal_number_get_status);

    token_type_init();
    token_operator_init();
    token_keyword_init();
    token_literal_init();
}

static tokenization_status_t get_best_status(char *line, token_kind_t *kind) {
    tokenization_status_t min = tokenization_statuses_count;
    dict_for(tokenizers, tokenizers_item_t, item) {
        tokenization_status_t status = item.value(line);
        if (status < min) {
            min = status;
            *kind = item.key;
        }
    }
    return min;
}

static token_t try_get_token(char *line) {
    token_kind_t kind;
    tokenization_status_t status = get_best_status(line, &kind);

    assert(status == correct);
    return (token_t) {
            .kind = kind,
            .data = get_data_from(line, kind)
    };
}

tokens_t tokenize(char *code) {
    assert(isspace(code[strlen(code) - 1]));

    tokens_t tokens = {};
    list_alloc(tokens, token_t);

    char buffer[TOKEN_MAX_LENGTH + 1] = {};
    size_t index = 0;
    uint8_t is_line_literal = 0;
    for (char alpha = *code; alpha; alpha = *(++code)) {
        if (strcnt("'\"", alpha) != 0 && !is_line_literal) {
            is_line_literal = 1;
            if (index > 0) {
                list_push(tokens, try_get_token(buffer));
                memset(buffer, 0, index);
                index = 0;
            }
        }

        if (isspace(alpha) && !is_line_literal) {
            if (index == 0)
                continue;

            list_push(tokens, try_get_token(buffer));
            memset(buffer, 0, index);
            index = 0;
            continue;
        }

        buffer[index++] = alpha;
        assert(index < sizeof(buffer));

        if (is_line_literal) {
            if (index >= 2 && buffer[index - 2] == '\\' && !(index >= 3 && buffer[index - 3] == '\\') ||
                index == 1 || buffer[0] != alpha)
                continue;

            is_line_literal = 0;
            token_t token = {
                    .kind = token_kind_literal,
                    .data = (token_data_t) token_literal_str_or_char_try_get_data_from(buffer)
            };
            list_push(tokens, token);
            memset(buffer, 0, index);
            index = 0;
            continue;
        }

        token_kind_t kind;
        tokenization_status_t status = get_best_status(buffer, &kind);

        if (status != incorrect)
            continue;

        if (index <= 1) {
            printf("No token can start with '%alpha'.", alpha);
            assert(0);
        }

        code--;
        buffer[--index] = 0;
        list_push(tokens, try_get_token(buffer));
        memset(buffer, 0, index);
        index = 0;
    }
    assert(!is_line_literal);

    return tokens;
}

token_data_t get_data_from(char *line, token_kind_t kind) {
    switch (kind) {
        case token_kind_type:
            return (token_data_t) {.as_type = token_type_get_data_from(line)};
        case token_kind_name:
            return (token_data_t) {.as_name = token_name_get_data_from(line)};
        case token_kind_operator:
            return (token_data_t) {.as_operator = token_operator_get_data_from(line)};
        case token_kind_keyword:
            return (token_data_t) {.as_keyword = token_keyword_get_data_from(line)};
        case token_kind_literal:
            return (token_data_t) {.as_literal = token_literal_number_get_data_from(line)};
        default:
            assert(0);
    }
}

void print_tokens(tokens_t tokens) {
    list_for(tokens, token_t, token) {
        print_token(token);
    }
}

static char *str_token_name(token_t token) {
    switch (token.kind) {
        case token_kind_type:
            return TOKEN_TYPE_NAME;
        case token_kind_name:
            return TOKEN_NAME_NAME;
        case token_kind_operator:
            return TOKEN_OPERATOR_NAME;
        case token_kind_keyword:
            return TOKEN_KEYWORD_NAME;
        case token_kind_literal:
            return TOKEN_LITERAL_NAME;
        default:
            assert(0);
    }
}

static void write_token_data(token_t token, char **buffer) {
    switch (token.kind) {
        case token_kind_type:
            write_token_type_data(token.data.as_type, buffer);
            return;
        case token_kind_name:
            write_token_name_data(token.data.as_name, buffer);
            return;
        case token_kind_operator:
            write_token_operator_data(token.data.as_operator, buffer);
            return;
        case token_kind_keyword:
            write_token_keyword_data(token.data.as_keyword, buffer);
            return;
        case token_kind_literal:
            write_token_literal_data(token.data.as_literal, buffer);
            return;
        default:
            assert(0);
    }
}

void print_token(token_t token) {
    char buffer[256] = {};
    char *line = buffer;
    char *initial_line = line;
    write_token_data(token, &line);
    printf("[%s(%s)]\n", str_token_name(token), initial_line);
}
