#include "expression_function_call.h"

#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

static DICT(operator_t, char *) function_of_binary_operation = {};

void expression_binary_operation_init() {
    assert(function_of_binary_operation.count == 0);

    dict_alloc(function_of_binary_operation);
    dict_set(function_of_binary_operation, operator_double_vertical, "BUILTIN_or");
    dict_set(function_of_binary_operation, operator_double_ampersand, "BUILTIN_and");
    dict_set(function_of_binary_operation, operator_double_equals, "BUILTIN_equals");
    dict_set(function_of_binary_operation, operator_exclamation_equals, "BUILTIN_not_equals");
    dict_set(function_of_binary_operation, operator_greater, "BUILTIN_greater");
    dict_set(function_of_binary_operation, operator_greater_equals, "BUILTIN_greater_equals");
    dict_set(function_of_binary_operation, operator_smaller, "BUILTIN_smaller");
    dict_set(function_of_binary_operation, operator_smaller_equals, "BUILTIN_smaller_equals");
    dict_set(function_of_binary_operation, operator_plus, "BUILTIN_add");
    dict_set(function_of_binary_operation, operator_minus, "BUILTIN_subtract");
    dict_set(function_of_binary_operation, operator_star, "BUILTIN_multiply");
    dict_set(function_of_binary_operation, operator_slash, "BUILTIN_divide");
    dict_set(function_of_binary_operation, operator_percent, "BUILTIN_mod");
    dict_set(function_of_binary_operation, operator_double_greater, "BUILTIN_shift_right");
    dict_set(function_of_binary_operation, operator_double_smaller, "BUILTIN_shift_left");
    dict_set(function_of_binary_operation, operator_vertical, "BUILTIN_bitwise_or");
    dict_set(function_of_binary_operation, operator_ampersand, "BUILTIN_bitwise_and");
    dict_set(function_of_binary_operation, operator_hat, "BUILTIN_bitwise_xor");
}

expression_parsing_result_t expression_binary_operation_get_data_from(tokens_t tokens) {
    if (tokens.count < 3)
        return FAILED_TO_PARSE_EXPRESSION;

    expressions_t parts;
    char *function_name = NULL;
    list_for(function_of_binary_operation, item) {
        list_sized_alloc(parts, 2);
        if (specifying_parse_expressions_separated_by(item.key, tokens, &parts, true)) {
            function_name = item.value;
            break;
        }
        free_expressions(parts);
    }

    if (!function_name)
        return FAILED_TO_PARSE_EXPRESSION;

    fake_tokens_new(1);
    fake_tokens_append_token_name(function_name);

    expression_t *function = parse_expression(list_view(fake_tokens_current));
    if (!function)
        return FAILED_TO_PARSE_EXPRESSION;

    expression_function_call_data_t data = {
            .function = function,
            .arguments = parts
    };

    return EXPRESSION_PARSED(.as_function_call, data);
}

