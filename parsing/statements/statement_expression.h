#ifndef STATEMENT_EXPRESSION
#define STATEMENT_EXPRESSION

#include "../../tokenization/tokenization.h"
#include "statements.h"

#define STATEMENT_expression_NAME ""

statement_parsing_result_t statement_expression_get_data_from(tokens_t tokens, bool is_strict);

void write_statement_expression_data_from(statement_data_t data, char **buffer);

void free_statement_expression_data(statement_data_t data);

#endif
