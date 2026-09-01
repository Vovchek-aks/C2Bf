#ifndef STATEMENT_EXPRESSION
#define STATEMENT_EXPRESSION

#include "../../tokenization/tokenization.h"
#include "statements.h"

#define STATEMENT_EXPRESSION_NAME "Expression"

statement_parsing_result_t statement_expression_get_data_from(tokens_t tokens);

void write_statement_expression_data_from(statement_expression_data_t data, char **buffer);

void free_statement_expression_data(statement_expression_data_t data);

#endif
