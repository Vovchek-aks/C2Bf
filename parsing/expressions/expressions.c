#include "expressions.h"
#include "expression_name.h"
#include "../../data_structures/data_structures.h"
#include "stdio.h"
#include "expression_name.c"

expression_parsers_t expression_parsers;

#define expression_parsers_set(key, value) dict_set(expression_parsers, expression_parsers_KV_t, expression_parser_t, key, value);

void expressions_parsing_init() {
    dict_alloc(expression_parsers, expression_parsers_KV_t);
    expression_parsers_set(expression_kind_name, expression_name_get_data_from);
}

expression_t *parse_expression(tokens_t tokens) {
    expression_t *expression = malloc(sizeof(expression_t));
    expression->tokens = tokens;

    dict_for(expression_parsers, expression_parsers_KV_t, item) {
        expression_parsing_result_t result = item.value(tokens);
        if (result.status == expression_parsing_result_fail)
            continue;

        expression->kind = item.key;
        expression->data = result.data;
        return expression;
    }
    printf("Tokens below cannot be parsed as an expression:\n");
    print_tokens(tokens);
    assert(0);
}

static char *str_expression_name(expression_t expression) {
    switch (expression.kind) {
        case expression_kind_name:
            return EXPRESSION_NAME_NAME;
        default:
            assert(0);
    }
}

static void write_expression_data(expression_t expression, char *buffer) {
    switch (expression.kind) {
        case expression_kind_name:
            write_expression_name_data_from(expression.data.as_name, buffer);
            break;
        default:
            assert(0);
    }
}

void print_expression(expression_t expression) {
    char buffer[256] = {};
    write_expression_data(expression, buffer);
    printf("%s(%s)\n", str_expression_name(expression), buffer);
}
