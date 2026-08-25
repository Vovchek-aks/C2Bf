#include "expression_function_call.h"
#include "../tokens_operations.h"

#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

#define EXPRESSION_UNARY_OPERATION_PARSER_BODY(chop, dict) {                                                           \
    if (tokens.count < 2)                                                                                              \
        return FAILED_TO_PARSE_EXPRESSION;                                                                             \
                                                                                                                       \
    token_t *operator = chop(&tokens, token_kind_operator);                                                            \
    if (!operator)                                                                                                     \
        return FAILED_TO_PARSE_EXPRESSION;                                                                             \
                                                                                                                       \
    char *function_name = NULL;                                                                                        \
    dict_get(dict, operator->data.as_operator.name, function_name);                                                    \
    if (!function_name)                                                                                                \
        return FAILED_TO_PARSE_EXPRESSION;                                                                             \
                                                                                                                       \
    fake_tokens_new(tokens.count + 2);                                                                                 \
    fake_tokens_append_token_name(function_name);                                                                      \
    fake_tokens_append_token_operator(operator_open_round);                                                            \
    fake_tokens_extend(tokens);                                                                                        \
    fake_tokens_append_token_operator(operator_close_round);                                                           \
                                                                                                                       \
    expression_parsing_result_t result = expression_function_call_get_data_from(list_view(fake_tokens_current));       \
    if (result.status == expression_parsing_result_fail) {                                                             \
        fake_tokens_remove_last_list();                                                                                \
        return FAILED_TO_PARSE_EXPRESSION;                                                                             \
    }                                                                                                                  \
                                                                                                                       \
    return result;                                                                                                     \
}

static DICT(operator_t, char *) function_of_unary_prefix;
static DICT(operator_t, char *) function_of_unary_postfix;

void expression_unary_operation_init() {
    dict_alloc(function_of_unary_prefix);
    dict_set(function_of_unary_prefix, operator_minus, "BUILTIN_negative");
    dict_set(function_of_unary_prefix, operator_double_minus, "BUILTIN_prefix_decrement");
    dict_set(function_of_unary_prefix, operator_plus, "BUILTIN_positive");
    dict_set(function_of_unary_prefix, operator_double_plus, "BUILTIN_prefix_increment");
    dict_set(function_of_unary_prefix, operator_exclamation, "BUILTIN_not");
    dict_set(function_of_unary_prefix, operator_tilda, "BUILTIN_bitwise_not");

    dict_alloc(function_of_unary_postfix);
    dict_set(function_of_unary_postfix, operator_double_minus, "BUILTIN_postfix_decrement");
    dict_set(function_of_unary_postfix, operator_double_plus, "BUILTIN_postfix_increment");
}

expression_parsing_result_t expression_unary_prefix_operation_get_data_from(tokens_t tokens)
    EXPRESSION_UNARY_OPERATION_PARSER_BODY(chop_front, function_of_unary_prefix)

expression_parsing_result_t expression_unary_postfix_operation_get_data_from(tokens_t tokens)
    EXPRESSION_UNARY_OPERATION_PARSER_BODY(chop_back, function_of_unary_postfix)

