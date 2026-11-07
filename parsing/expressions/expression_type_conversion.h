#include "../../tokenization/tokenization.h"
#include "expressions.h"

#ifndef EXPRESSION_TYPE_CONVERSION
#define EXPRESSION_TYPE_CONVERSION

#define EXPRESSION_TYPE_CONVERSION_NAME "TypeConversion"

expression_parsing_result_t expression_type_conversion_get_data_from(tokens_t tokens, bool is_strict);

void write_expression_type_conversion_data_from(expression_type_conversion_data_t data, char **buffer);

void free_expression_type_conversion_data(expression_type_conversion_data_t data);

#endif
