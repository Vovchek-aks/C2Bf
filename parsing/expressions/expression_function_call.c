#include "expression_function_call.h"
#include "../tokens_operations.h"
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

static bool parse_arguments(tokens_t tokens, expressions_t *arguments) {
    tokens_t accumulator = {};
    while (tokens.count > 0) {
        token_t *comma = find_operator(tokens, operator_comma, chop_direction_front);
        tokens_t part = comma ? split_by(comma, &tokens) : move(&tokens);
        combine(&accumulator, part);

        expression_t *expression = parse_expression(accumulator);
        if (expression) {
            list_push(*arguments, expression);
            accumulator.count = 0;
            accumulator.data = NULL;
        }
    }

    return accumulator.count == 0;
}

expression_parsing_result_t expression_function_call_get_data_from(tokens_t tokens) {
    if (tokens.count < 3)
        return FAILED_TO_PARSE_EXPRESSION;

    if (!chop_operator(&tokens, operator_close_round, chop_direction_back))
        return FAILED_TO_PARSE_EXPRESSION;

    token_t *bracket = get_paired_bracket(tokens, operator_open_round, operator_close_round,
                                          chop_direction_back);
    if (!bracket)
        return FAILED_TO_PARSE_EXPRESSION;

    tokens_t left = split_by(bracket, &tokens);

    expression_t *function = parse_expression(left);
    if (!function)
        return FAILED_TO_PARSE_EXPRESSION;

    expressions_t arguments;
    list_alloc(arguments);
    if (!parse_arguments(tokens, &arguments)) {
        free_expression(function);
        free_expressions(arguments);
        return FAILED_TO_PARSE_EXPRESSION;
    }

    expression_function_call_data_t data = {
            .function = function,
            .arguments = arguments
    };
    return EXPRESSION_PARSED(.as_function_call, data);
}

void write_expression_function_call_data_from(expression_function_call_data_t data, char **buffer) {
    string_extend(buffer, "(");
    *buffer += snprintf(*buffer, 20, "args=%llu", data.arguments.count);
    string_extend(buffer, "):");
    string_extend(buffer, "\n.function = ");
    write_expression(data.function, buffer);

    size_t index = 0;
    list_for(data.arguments, argument) {
        *buffer += snprintf(*buffer, 20, "\n.argument%llu = ", index++);
        write_expression(argument, buffer);
    }
}

void free_expression_function_call_data(expression_function_call_data_t data) {
    free_expression(data.function);
    free_expressions(data.arguments);
}
