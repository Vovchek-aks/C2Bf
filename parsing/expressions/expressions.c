#include "expressions.h"
#include "expression_name.h"
#include "../../data_structures/data_structures.h"
#include "stdio.h"
#include "expression_name.c"
#include "expression_literal.c"
#include "expression_element_access.c"
#include "expression_indexing.c"
#include "../tokens_operations.c"

expression_parsers_t expression_parsers;

#define expression_parsers_set(kind_to_set, parser_to_set) do {                                                        \
    typed_expression_parser_t element = { kind_to_set, parser_to_set };                                                \
    list_push(expression_parsers, element);                                                                            \
} while(0)

void expressions_parsing_init(void) {
    list_alloc(expression_parsers, typed_expression_parser_t);
    expression_parsers_set(expression_kind_name, expression_name_get_data_from);
    expression_parsers_set(expression_kind_literal, expression_literal_get_data_from);
    expression_parsers_set(expression_kind_element_access, expression_element_access_get_data_from);
    expression_parsers_set(expression_kind_indexing, expression_indexing_get_data_from);
}

expression_t *parse_expression(tokens_t tokens) {
    assert(tokens.capacity == 0);
    list_for(expression_parsers, typed_expression_parser_t , parser) {
        expression_parsing_result_t result = parser.parse(tokens);
        if (result.status == expression_parsing_result_fail)
            continue;

        expression_t *expression = malloc(sizeof(expression_t));
        expression->tokens = tokens;
        expression->kind = parser.kind;
        expression->data = result.data;

        return expression;
    }

    return NULL;
}

expression_t *strictly_parse_expression(tokens_t tokens) {
    expression_t *expression = parse_expression(tokens);
    if (expression)
        return expression;

    printf("Cannot parse expression from:\n");
    print_tokens(tokens);
    assert(0);
}

static char *str_expression_name(expression_t *expression) {
    switch (expression->kind) {
        case expression_kind_name:
            return EXPRESSION_NAME_NAME;
        case expression_kind_literal:
            return EXPRESSION_LITERAL_NAME;
        case expression_kind_element_access:
            return EXPRESSION_ELEMENT_ACCESS_NAME;
        case expression_kind_indexing:
            return EXPRESSION_INDEXING_NAME;
        default:
            assert(0);
    }
}

static void write_expression_data(expression_t *expression, char **buffer) {
    switch (expression->kind) {
        case expression_kind_name:
            return write_expression_name_data_from(expression->data.as_name, buffer);
        case expression_kind_literal:
            return write_expression_literal_data_from(expression->data.as_literal, buffer);
        case expression_kind_element_access:
            return write_expression_element_access_data_from(expression->data.as_element_access, buffer);
        case expression_kind_indexing:
            return write_expression_indexing_data_from(expression->data.as_indexing, buffer);
        default:
            assert(0);
    }
}

static void adjust_level(char *line, char **buffer) {
    string_for(line, alpha) {
        string_append(buffer, alpha);
        if (alpha == '\n')
            string_extend(buffer, ".   ");
    }
}

void print_expression(expression_t *expression) {
    char *line = malloc(EXPRESSION_PRINTING_MAX_LENGTH);
    memset(line, 0, EXPRESSION_PRINTING_MAX_LENGTH);
    char *line_end = line;

    write_expression(expression, &line_end);

    printf("%s", line);
    free(line);
}

void write_expression(expression_t *expression, char **buffer) {
    char *line = malloc(EXPRESSION_PRINTING_MAX_LENGTH);
    memset(line, 0, EXPRESSION_PRINTING_MAX_LENGTH);
    char *line_end = line;

    string_extend(&line_end, str_expression_name(expression));
    write_expression_data(expression, &line_end);

    adjust_level(line, buffer);
    free(line);
}
