#include "expression_element_access.h"
#include "../tokens_operations.h"

expression_parsing_result_t expression_element_access_get_data_from(tokens_t tokens) {
    if (tokens.count < 3)
        return FAILED_TO_PARSE_EXPRESSION;

    token_t *element = chop_back(&tokens, token_kind_name);
    if (!element)
        return FAILED_TO_PARSE_EXPRESSION;

    if (!chop_operator(&tokens, operator_dot, chop_direction_back))
        return FAILED_TO_PARSE_EXPRESSION;

    expression_t *source = parse_expression(tokens);
    if (!source)
        return FAILED_TO_PARSE_EXPRESSION;

    expression_element_access_data_t data = {
            .source = source,
            .element = &element->data.as_name
    };
    return EXPRESSION_PARSED(.as_element_access, data);
}

void write_expression_element_access_data_from(expression_element_access_data_t data, char **buffer) {
    string_extend(buffer, "(\".");
    string_extend(buffer, data.element->name);
    string_extend(buffer, "\"):\n");
    string_extend(buffer, ".source = ");
    write_expression(data.source, buffer);
}
