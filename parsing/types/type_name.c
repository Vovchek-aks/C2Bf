#include "type_name.h"
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

type_parsing_result_t type_name_get_data_from(tokens_t tokens, bool is_strict) {
    if (tokens.count != 1)
        return FAILED_TO_PARSE_TYPE;

    token_t *token = chop_front(&tokens, token_kind_name);
    if (!token)
        return FAILED_TO_PARSE_TYPE;

    parsed_type_name_data_t data = {token->data.as_name.name};
    return TYPE_PARSED(.as_name, data);
}

void write_type_name_data_from(parsed_type_name_data_t data, char **buffer) {
    string_extend(buffer, "(\"");
    string_extend(buffer, data.name);
    string_extend(buffer, "\");");
}

void free_type_name_data(parsed_type_name_data_t data) {
}
