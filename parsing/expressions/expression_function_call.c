#include "expression_function_call.h"
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

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
    list_sized_alloc(arguments, 4);
    if (!parse_expressions_separated_by(operator_comma, tokens, &arguments)) {
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

static void write_function_name(expression_function_call_data_t data, char **buffer) {
    if (data.function->kind == expression_kind_name) {
        *buffer += snprintf(*buffer, TOKEN_MAX_LENGTH,
                            "(\"%s\"):", data.function->data.as_name.token->name);
        return;
    }

    *buffer += snprintf(*buffer, 20, "(args=%llu):", data.arguments.count);
    string_extend(buffer, "\n.function = ");
    write_expression(data.function, buffer);
}

void write_expression_function_call_data_from(expression_function_call_data_t data, char **buffer) {
    write_function_name(data, buffer);

    size_t index = 0;
    list_for(data.arguments, argument) {
        *buffer += snprintf(*buffer, 20, "\n.argument_%llu = ", index++);
        write_expression(argument, buffer);
    }
}

void free_expression_function_call_data(expression_function_call_data_t data) {
    free_expression(data.function);
    free_expressions(data.arguments);
}
