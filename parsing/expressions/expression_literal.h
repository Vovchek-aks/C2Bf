#include "../../tokenization/tokenization.h"
#include "expressions.h"

#ifndef EXPRESSION_LITERAL
#define EXPRESSION_LITERAL

#define EXPRESSION_LITERAL_NAME "Literal"

expression_parsing_result_t expression_literal_get_data_from(tokens_t tokens);

void write_expression_literal_data_from(expression_literal_data_t data, char *buffer);

#endif