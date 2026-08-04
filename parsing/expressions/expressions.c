#include "expressions.h"
#include "expression_name.h"
#include "../../data_structures/data_structures.h"
#include "stdio.h"
#include "expression_name.c"
#include "expression_literal.c"

expression_parsers_t expression_parsers;

#define expression_parsers_set(kind_to_set, parser_to_set) do {                                                        \
    typed_expression_parser_t element = {                                                                              \
        .kind = kind_to_set,                                                                                           \
        .parse = parser_to_set                                                                                        \
    };                                                                                                                 \
    list_push(expression_parsers, element);                                                                            \
} while(0)

void expressions_parsing_init() {
    list_alloc(expression_parsers, typed_expression_parser_t);
    expression_parsers_set(expression_kind_name, expression_name_get_data_from);
    expression_parsers_set(expression_kind_literal, expression_literal_get_data_from);
}

expression_t *parse_expression(tokens_t tokens) {
    expression_t *expression = malloc(sizeof(expression_t));
    expression->tokens = tokens;

    list_for(expression_parsers, typed_expression_parser_t , parser) {
        expression_parsing_result_t result = parser.parse(tokens);
        if (result.status == expression_parsing_result_fail)
            continue;

        expression->kind = parser.kind;
        expression->data = result.data;
        return expression;
    }
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
        default:
            assert(0);
    }
}

static void write_expression_data(expression_t *expression, char *buffer) {
    switch (expression->kind) {
        case expression_kind_name:
            write_expression_name_data_from(expression->data.as_name, buffer);
            break;
        case expression_kind_literal:
            write_expression_literal_data_from(expression->data.as_literal, buffer);
            break;
        default:
            assert(0);
    }
}

void print_expression(expression_t *expression) {
    char buffer[256] = {};
    write_expression_data(expression, buffer);
    printf("%s(%s)\n", str_expression_name(expression), buffer);
}
