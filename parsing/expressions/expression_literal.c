#include "expression_literal.h"

expression_parsing_result_t expression_literal_get_data_from(tokens_t tokens) {
    if (tokens.count != 1)
        return FAILED_TO_PARSE_EXPRESSION;

    token_t *token = &tokens.data[0];
    if (token->kind != token_kind_literal)
        return FAILED_TO_PARSE_EXPRESSION;

    return EXPRESSION_PARSED(.as_literal, {.token = &token->data.as_literal});
}

void write_expression_literal_data_from(expression_literal_data_t data, char *buffer) {
    write_token_literal_data(*(data.token), buffer);
}
