#ifndef TYPE_ARRAY
#define TYPE_ARRAY

#include "../../tokenization/tokenization.h"
#include "parsed_types.h"

#define TYPE_ARRAY_NAME "ArrayType"

parsed_type_t *make_parsed_type_array(parsed_type_t *element, expression_t *size);

void write_type_array_data_from(parsed_type_array_data_t data, char **buffer);

void free_type_array_data(parsed_type_array_data_t data);

#endif
