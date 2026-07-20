#include "tokenization.h"
#include "token_type.c"
#include "token_name.c"
#include <assert.h>
#include <ctype.h>


static tokenizers_t tokenizers;

void tokenization_init(void) {
    dict_alloc(tokenizers, tokenizers_item_t);
    dict_set(tokenizers, tokenizers_item_t, tokenizer_t, type_, token_type_get_status);
    dict_set(tokenizers, tokenizers_item_t, tokenizer_t, name, token_name_get_status);

    token_type_init();
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

    if (status != correct) {
        printf("Incorrect token '%s'.", line);
        abort();
    }

    return (token_t){
            .kind = kind,
            .data = get_data_from(line, kind)
    };
}

tokens_t tokenize(char *code)
{
    assert(isspace(code[strlen(code) - 1]));

    tokens_t tokens = {};
    list_alloc(tokens, token_t);

    char buffer[TOKEN_MAX_LENGTH + 1] = {};
    size_t index = 0;
    for (char c = *code; c; c = *(++code)) {
        if (isspace(c)) {
            if (index == 0)
                continue;

            list_push(tokens, try_get_token(buffer));
            memset(buffer, 0, index);
            index = 0;
            continue;
        }

        buffer[index++] = c;
        assert(index < sizeof(buffer));

        token_kind_t kind;
        tokenization_status_t status = get_best_status(buffer, &kind);

        if (status != incorrect)
            continue;

        if (index <= 1) {
            printf("No token can start with '%c'.", c);
            abort();
        }

        code--;
        buffer[--index] = 0;
        list_push(tokens, try_get_token(buffer));
        memset(buffer, 0, index);
        index = 0;
    }

    return tokens;
}

token_data_t get_data_from(char *line, token_kind_t kind) {
    switch (kind) {
        case type_:
            return (token_data_t){.type = token_type_get_data_from(line)};
        case name:
            return (token_data_t){.name = token_name_get_data_from(line)};
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
    case type_:
        return TOKEN_TYPE_NAME;
    case name:
        return TOKEN_NAME_NAME;
    default:
        assert(0);
    }
}

static void write_token_data(token_t token, char *buffer) {
    switch (token.kind) {
    case type_:
        write_token_type_data(token.data.type, buffer);
        return;
    case name:
        write_token_name_data(token.data.name, buffer);
        return;
    default:
        assert(0);
    }
}

void print_token(token_t token) {
    char buffer[256] = {};
    write_token_data(token, buffer);
    printf("[%s(%s)]\n", str_token_name(token), buffer);
}
