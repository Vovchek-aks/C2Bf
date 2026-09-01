#ifndef STATEMENT_IF
#define STATEMENT_IF

#include "../../tokenization/tokenization.h"
#include "statements.h"

#define STATEMENT_IF_NAME "If"

statement_parsing_result_t statement_if_get_data_from(tokens_t tokens);

void write_statement_if_data_from(statement_if_data_t data, char **buffer);

void free_statement_if_data(statement_if_data_t data);

#endif
