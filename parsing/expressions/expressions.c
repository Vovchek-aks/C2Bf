#include "expressions.h"
#include "expression_name.h"
#include "stdio.h"
#include "expression_name.c"
#include "expression_literal.c"
#include "expression_element_access.c"
#include "expression_indexing.c"
#include "expression_function_call.c"
#include "expression_unary_operation.c"
#include "expression_binary_operation.c"
#include "../tokens_operations.c"
#include "../../string_helper/string_helper.h"

#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

static expression_parsers_t expression_parsers;

#define expression_parsers_set(kind_to_set, parser_to_set) do {                                                        \
    typeof(*expression_parsers.data) element = { kind_to_set, parser_to_set };                                         \
    list_push(expression_parsers, element);                                                                            \
} while(0)

void expressions_parsing_init(void) {
    list_alloc(expression_parsers);
    expression_parsers_set(expression_kind_name, expression_name_get_data_from);
    expression_parsers_set(expression_kind_literal, expression_literal_get_data_from);
    expression_parsers_set(expression_kind_element_access, expression_element_access_get_data_from);
    expression_parsers_set(expression_kind_indexing, expression_indexing_get_data_from);
    expression_parsers_set(expression_kind_function_call, expression_function_call_get_data_from);
    expression_parsers_set(expression_kind_function_call, expression_binary_operation_get_data_from);
    expression_parsers_set(expression_kind_function_call, expression_unary_prefix_operation_get_data_from);
    expression_parsers_set(expression_kind_function_call, expression_unary_postfix_operation_get_data_from);

    expression_unary_operation_init();
    expression_binary_operation_init();
}

static void strip_brackets(tokens_t *tokens) {
    tokens_t stripped = *tokens;
    while (stripped.count > 1) {
        if (!chop_operator(&stripped, operator_open_round, chop_direction_front))
            break;

        if (!chop_operator(&stripped, operator_close_round, chop_direction_back))
            break;

        *tokens = stripped;
    }
}

expression_t *parse_expression(tokens_t tokens) {
    assert(tokens.capacity == 0);

    strip_brackets(&tokens);
    list_for(expression_parsers, parser) {
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

bool parse_expressions_separated_by(operator_t target, tokens_t tokens, expressions_t *result) {
    return specifying_parse_expressions_separated_by(target, tokens, result, false);
}

bool specifying_parse_expressions_separated_by(operator_t target,
                                               tokens_t tokens,
                                               expressions_t *result,
                                               bool require_at_least_one_split) {
    tokens_t original = tokens;
    tokens_t accumulator = {};
    while (tokens.count > 0) {
        token_t *separator = find_operator(tokens, target, chop_direction_front);
        tokens_t part = separator ? split_by(separator, &tokens) : absorb(&tokens);
        combine(&accumulator, part);

        if (accumulator.count == original.count && require_at_least_one_split)
            return false;

        expression_t *expression = parse_expression(accumulator);
        if (expression) {
            list_push(*result, expression);
            accumulator.count = 0;
            accumulator.data = NULL;
        }
    }

    return accumulator.count == 0;
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
        case expression_kind_function_call:
            return EXPRESSION_FUNCTION_CALL_NAME;
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
        case expression_kind_function_call:
            return write_expression_function_call_data_from(expression->data.as_function_call, buffer);
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

static char print_buffer[EXPRESSION_PRINTING_MAX_LENGTH] = {};

void print_expression(expression_t *expression) {
    char *line_end = print_buffer;
    write_expression(expression, &line_end);

    printf("%s\n", print_buffer);
    memset(print_buffer, 0, EXPRESSION_PRINTING_MAX_LENGTH);
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

void free_expression(expression_t *expression) {
    switch (expression->kind) {
        case expression_kind_name:
            free_expression_name_data(expression->data.as_name);
            break;
        case expression_kind_literal:
            free_expression_literal_data(expression->data.as_literal);
            break;
        case expression_kind_element_access:
            free_expression_element_access_data(expression->data.as_element_access);
            break;
        case expression_kind_indexing:
            free_expression_indexing_data(expression->data.as_indexing);
            break;
        case expression_kind_function_call:
            free_expression_function_call_data(expression->data.as_function_call);
            break;
        default:
            assert(0);
    }

    free(expression);
}

void free_expressions(expressions_t expressions) {
    list_for(expressions, expression)
        free_expression(expression);

    list_free(expressions);
}
