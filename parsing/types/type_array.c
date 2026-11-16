#include "type_array.h"

#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

parsed_type_t *make_parsed_type_array(parsed_type_t *element, expression_t *size) {
    parsed_type_t *type = malloc(sizeof(parsed_type_t));
    type->tokens = element->tokens;
    type->kind = parsed_type_kind_array;
    type->data = (parsed_type_data_t) {
            .as_array = {
                    .element = element,
                    .size = size
            }
    };

    return type;
}

void write_type_array_data_from(parsed_type_array_data_t data, char **buffer) {
    string_extend(buffer, "():");

    string_extend(buffer, "\n.element = ");
    write_type(data.element, buffer);

    if (!data.size)
        return;

    string_extend(buffer, "\n.size = ");
    write_expression(data.size, buffer);
}

void free_type_array_data(parsed_type_array_data_t data) {
    free_type(data.element);
}
