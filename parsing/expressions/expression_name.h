#include "../../tokenization/tokenization.h"
#include "expressions_datas.h"

#ifndef EXPRESSION_NAME
#define EXPRESSION_NAME

#define EXPRESSION_NAME_NAME "Name"

expression_parsing_result_t expression_name_get_data_from(tokens_t tokens);

void write_expression_name_data_from(expression_name_data_t data, char *buffer);

#endif