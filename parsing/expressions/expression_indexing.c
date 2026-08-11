#include "expression_indexing.h"
#include "../tokens_operations.h"

expression_parsing_result_t expression_indexing_get_data_from(tokens_t tokens) {
    if (tokens.count < 4)
        return FAILED_TO_PARSE_EXPRESSION;

    if (!chop_operator(&tokens, operator_close_square, chop_direction_back))
        return FAILED_TO_PARSE_EXPRESSION;

    token_t *bracket = get_paired_bracket(&tokens, operator_open_square, operator_close_square,
                                          chop_direction_back);
    if (!bracket)
        return FAILED_TO_PARSE_EXPRESSION;

    tokens_t left = split_by(bracket, &tokens);

    expression_t *array = parse_expression(left);
    if (!array)
        return FAILED_TO_PARSE_EXPRESSION;

    expression_t *index = parse_expression(tokens);
    if (!index)
        return FAILED_TO_PARSE_EXPRESSION;

    expression_indexing_data_t data = {
            .array = array,
            .index = index
    };

    return EXPRESSION_PARSED(.as_indexing, data);
}

void write_expression_indexing_data_from(expression_indexing_data_t data, char **buffer) {
    string_extend(buffer, "():");
    string_extend(buffer, "\n.array = ");
    write_expression(data.array, buffer);
    string_extend(buffer, "\n.index = ");
    write_expression(data.index, buffer);
}
