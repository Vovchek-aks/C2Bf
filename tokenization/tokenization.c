#include "tokenization.h"
#include "token_type.c"
#include "token_name.c"
#include "token_operator.c"
#include "token_keyword.c"
#include "token_literal.c"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>

static DICT(token_kind_t, tokenizer_t) tokenizers;

void init_tokenization(void) {
    dict_alloc(tokenizers);
    dict_set(tokenizers, token_kind_type, token_type_get_status);
    dict_set(tokenizers, token_kind_keyword, token_keyword_get_status);
    dict_set(tokenizers, token_kind_name, token_name_get_status);
    dict_set(tokenizers, token_kind_operator, token_operator_get_status);
    dict_set(tokenizers, token_kind_literal, token_literal_number_get_status);

    init_type_tokenization();
    init_operator_tokenization();
    init_keyword_tokenization();
    init_literal_tokenization();
}

static tokenization_status_t get_best_status(char *line, token_kind_t *kind) {
    tokenization_status_t min = tokenization_statuses_count;
    dict_for(tokenizers, item) {
        tokenization_status_t status = item.value(line);
        if (status < min) {
            min = status;
            *kind = item.key;
        }
    }
    return min;
}

static token_t try_get_token(char *buffer, char *rest_code, size_t line, size_t symbol) {
    token_kind_t kind;
    tokenization_status_t status = get_best_status(buffer, &kind);

    assert(status == tokenization_status_correct);
    size_t length = strlen(buffer);
    return (token_t) {
            .info = {
                .line = line,
                .symbol = symbol - length + 1,
                .count = length,
                .symbols = rest_code - length + 1
            },
            .kind = kind,
            .data = get_data_from(buffer, kind)
    };
}

tokens_t tokenize(char *code) {
    assert(isspace(code[strlen(code) - 1]));

    tokens_t tokens = {};
    list_alloc(tokens);
    size_t line = 1;
    size_t symbol = 0;
    char buffer[TOKEN_MAX_LENGTH + 1] = {};
    size_t index = 0;
    bool is_line_literal = false;
    string_for(code, alpha) {
        symbol++;
        if (alpha == '\n') {
            line++;
            symbol = 0;
        }

        if (strcnt("'\"", alpha) != 0 && !is_line_literal) {
            is_line_literal = true;
            if (index > 0) {
                list_push(tokens, try_get_token(buffer, code - 1, line, symbol - 1));
                memset(buffer, 0, index);
                index = 0;
            }
        }

        if (isspace(alpha) && !is_line_literal) {
            if (index == 0)
                continue;

            list_push(tokens, try_get_token(buffer, code - 1, line, symbol - 1));
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
                    .info = {
                            .line = line,
                            .symbol = symbol - index + 1,
                            .count = index,
                            .symbols = code - index + 1
                    },
                    .kind = token_kind_literal,
                    .data = (token_data_t) token_literal_str_or_char_try_get_data_from(buffer)
            };
            list_push(tokens, token);
            memset(buffer, 0, index);
            index = 0;
            continue;
        }

        token_kind_t kind;
        if (get_best_status(buffer, &kind) != tokenization_status_incorrect)
            continue;

        if (index <= 1)
            display_tokenization_error(line, symbol, "This symbol cannot be placed here.");

        code--;
        buffer[--index] = 0;
        symbol--;
        list_push(tokens, try_get_token(buffer, code, line, symbol));
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
    list_for(tokens, token) {
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
