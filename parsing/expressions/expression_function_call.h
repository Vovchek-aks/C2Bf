#include "../../tokenization/tokenization.h"
#include "expressions.h"

#ifndef EXPRESSION_FUNCTION_CALL
#define EXPRESSION_FUNCTION_CALL

#define EXPRESSION_FUNCTION_CALL_NAME "FunctionCall"

expression_parsing_result_t expression_function_call_get_data_from(tokens_t tokens);

void write_expression_function_call_data_from(expression_function_call_data_t data, char **buffer);

void free_expression_function_call_data(expression_function_call_data_t data);

#endif
