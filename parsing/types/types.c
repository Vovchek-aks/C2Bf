#include "types.h"
#include "stdio.h"
#include "type_builtin.c"
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

type_parsers_t type_parsers;

#define type_parsers_push(kind_to_set, parser_to_set) do {                                                             \
    typeof(*type_parsers.data) element = { kind_to_set, parser_to_set };                                               \
    list_push(type_parsers, element);                                                                                  \
} while(0)

void init_types_parsing(void) {
    list_alloc(type_parsers);
    type_parsers_push(type_kind_builtin, type_builtin_get_data_from);
}

type_t *parse_type(tokens_t tokens, bool is_strict) {
    assert(tokens.capacity == 0);

    list_for(type_parsers, parser) {
        type_parsing_result_t result = parser.parse(tokens, is_strict);
        if (result.status == type_parsing_result_fail)
            continue;

        type_t *type = malloc(sizeof(type_t));
        type->tokens = tokens;
        type->kind = parser.kind;
        type->data = result.data;

        return type;
    }

    if (!is_strict)
        return NULL;

    display_parsing_error(tokens, "Cannot parse type.");
}

static char *str_type_name(type_t *type) {
    switch (type->kind) {
        case type_kind_builtin:
            return TYPE_BUILTIN_NAME;
        default:
            printf("Type has no name\n");
            assert(false);
    }
}

static void write_type_data(type_t *type, char **buffer) {
    switch (type->kind) {
        case type_kind_builtin:
            return write_type_builtin_data_from(type->data.as_builtin, buffer);
        default:
            printf("Type cannot write data\n");
            assert(false);
    }
}

char type_print_buffer[TYPE_PRINTING_MAX_LENGTH] = {};

void print_type(type_t *type) {
    char *line_end = type_print_buffer;
    write_type(type, &line_end);

    printf("%s\n", type_print_buffer);
    memset(type_print_buffer, 0, TYPE_PRINTING_MAX_LENGTH);
}

void write_type(type_t *type, char **buffer) {
    char *line = malloc(TYPE_PRINTING_MAX_LENGTH);
    memset(line, 0, TYPE_PRINTING_MAX_LENGTH);
    char *line_end = line;

    string_extend(&line_end, str_type_name(type));
    write_type_data(type, &line_end);

    adjust_level(line, buffer);
    free(line);
}

void free_type(type_t *type) {
    switch (type->kind) {
        case type_kind_builtin:
            free_type_builtin_data(type->data.as_builtin);
            break;
        default:
            printf("Cannot free type\n");
            assert(false);
    }

    free(type);
}

void free_types(types_t types) {
    list_for(types, type)
    free_type(type);

    list_free(types);
}
