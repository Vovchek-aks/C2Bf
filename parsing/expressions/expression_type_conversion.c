#include "expression_type_conversion.h"

expression_parsing_result_t expression_type_conversion_get_data_from(tokens_t tokens, bool is_strict) {
    if (tokens.count < 4)  // (a) b
        return FAILED_TO_PARSE_EXPRESSION;

    if (!chop_operator(&tokens, operator_open_round, chop_direction_front))
        return FAILED_TO_PARSE_EXPRESSION;

    token_t *bracket = get_paired_bracket(tokens, operator_close_round, operator_open_round, chop_direction_front);
    if (!bracket)
        return FAILED_TO_PARSE_EXPRESSION;

    tokens_t left = split_by(bracket, &tokens);

    expression_type_conversion_data_t data;
    data.type = parse_type(left, is_strict);
    if (!data.type)
        return FAILED_TO_PARSE_EXPRESSION;

    data.expression = parse_expression(tokens, is_strict);
    if (!data.expression){
        free_type(data.type);
        return FAILED_TO_PARSE_EXPRESSION;
    }

    return EXPRESSION_PARSED(.as_type_conversion, data);
}

void write_expression_type_conversion_data_from(expression_type_conversion_data_t data, char **buffer) {
    string_extend(buffer, "():");
    string_extend(buffer, "\n.type = ");
    write_type(data.type, buffer);
    string_extend(buffer, "\n.expression = ");
    write_expression(data.expression, buffer);
}

void free_expression_type_conversion_data(expression_type_conversion_data_t data) {
    free_type(data.type);
    free_expression(data.expression);
}
