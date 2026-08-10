#include "../../tokenization/tokenization.h"
#include "expressions.h"

#ifndef EXPRESSION_INDEXING
#define EXPRESSION_INDEXING

#define EXPRESSION_INDEXING_NAME "Indexing"

expression_parsing_result_t expression_indexing_get_data_from(tokens_t tokens);

void write_expression_indexing_data_from(expression_indexing_data_t data, char **buffer);

#endif