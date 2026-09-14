#include "type_builtin.h"
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

type_parsing_result_t type_builtin_get_data_from(tokens_t tokens, bool is_strict) {
    if (tokens.count != 1)
        return FAILED_TO_PARSE_TYPE;

    token_t *token = chop_front(&tokens, token_kind_type);
    if (!token)
        return FAILED_TO_PARSE_TYPE;

    type_builtin_data_t data = {&token->data.as_type};
    return TYPE_PARSED(.as_builtin, data);
}

void write_type_builtin_data_from(type_builtin_data_t data, char **buffer) {
    string_extend(buffer, "(");
    write_token_type_data(*data.token, buffer);
    string_extend(buffer, ");");
}

void free_type_builtin_data(type_builtin_data_t data) {
}
