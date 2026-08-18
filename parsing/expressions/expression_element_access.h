#include "../../tokenization/tokenization.h"
#include "expressions.h"

#ifndef EXPRESSION_ELEMENT_ACCESS
#define EXPRESSION_ELEMENT_ACCESS

#define EXPRESSION_ELEMENT_ACCESS_NAME "ElementAccess"

expression_parsing_result_t expression_element_access_get_data_from(tokens_t tokens);

void write_expression_element_access_data_from(expression_element_access_data_t data, char **buffer);

void free_expression_element_access_data(expression_element_access_data_t data);

#endif
