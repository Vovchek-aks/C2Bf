#ifndef STATEMENT_WHILE
#define STATEMENT_WHILE

#include "../../tokenization/tokenization.h"
#include "statements.h"

#define STATEMENT_while_NAME "While"

statement_parsing_result_t statement_while_get_data_from(tokens_t tokens, bool is_strict);

void write_statement_while_data_from(statement_data_t data, char **buffer);

void free_statement_while_data(statement_data_t data);

#endif
