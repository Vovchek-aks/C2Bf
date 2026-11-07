#include "parsed_types.h"
#include "stdio.h"
#include "type_name.c"
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

type_parsers_t type_parsers;

#define type_parsers_push(kind_to_set, parser_to_set) do {                                                             \
    typeof(*type_parsers.data) element = { kind_to_set, parser_to_set };                                               \
    list_push(type_parsers, element);                                                                                  \
} while(0)

void init_types_parsing(void) {
    list_alloc(type_parsers);
    type_parsers_push(parsed_type_kind_name, type_name_get_data_from);
}

parsed_type_t *parse_type(tokens_t tokens, bool is_strict) {
    assert(tokens.capacity == 0);
    assert(tokens.count > 0);

    list_for(type_parsers, parser) {
        type_parsing_result_t result = parser.parse(tokens, is_strict);
        if (result.status == type_parsing_result_fail)
            continue;

        parsed_type_t *type = malloc(sizeof(parsed_type_t));
        type->tokens = tokens;
        type->kind = parser.kind;
        type->data = result.data;

        return type;
    }

    if (!is_strict)
        return NULL;

    display_parsing_error(tokens, "Cannot identify type.");
}

static char *str_type_name(parsed_type_t *type) {
    switch (type->kind) {
        case parsed_type_kind_name:
            return TYPE_NAME_NAME;
        default:
            printf("Type has no name\n");
            assert(false);
    }
}

static void write_type_data(parsed_type_t *type, char **buffer) {
    switch (type->kind) {
        case parsed_type_kind_name:
            return write_type_name_data_from(type->data.as_name, buffer);
        default:
            printf("Type cannot write data\n");
            assert(false);
    }
}

char type_print_buffer[TYPE_PRINTING_MAX_LENGTH] = {};

void print_type(parsed_type_t *type) {
    char *line_end = type_print_buffer;
    write_type(type, &line_end);

    printf("%s\n", type_print_buffer);
    memset(type_print_buffer, 0, TYPE_PRINTING_MAX_LENGTH);
}

void write_type(parsed_type_t *type, char **buffer) {
    char *line = malloc(TYPE_PRINTING_MAX_LENGTH);
    memset(line, 0, TYPE_PRINTING_MAX_LENGTH);
    char *line_end = line;

    string_extend(&line_end, str_type_name(type));
    write_type_data(type, &line_end);

    adjust_level(line, buffer);
    free(line);
}

void free_type(parsed_type_t *type) {
    switch (type->kind) {
        case parsed_type_kind_name:
            free_type_name_data(type->data.as_name);
            break;
        default:
            printf("Cannot free type\n");
            assert(false);
    }

    free(type);
}

void free_types(parsed_types_t types) {
    list_for(types, type)
    free_type(type);

    list_free(types);
}
