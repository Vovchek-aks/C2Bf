#include "expression_name.h"

expression_parsing_result_t expression_name_get_data_from(tokens_t tokens) {
    if (tokens.count != 1)
        return FAILED_TO_PARSE_EXPRESSION;

    token_t token = tokens.data[0];
    if (token.kind != token_kind_name)
        return FAILED_TO_PARSE_EXPRESSION;

    return EXPRESSION_PARSED(.as_name, {.token = token.data.as_name});
}


void write_expression_name_data_from(expression_name_data_t data, char *buffer) {
    write_token_name_data(data.token, buffer);
}
