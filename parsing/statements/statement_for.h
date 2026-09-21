#ifndef STATEMENT_FOR
#define STATEMENT_FOR

#include "../../tokenization/tokenization.h"
#include "statements.h"

#define STATEMENT_for_NAME "For"

statement_parsing_result_t statement_for_get_data_from(tokens_t tokens, bool is_strict);

void write_statement_for_data_from(statement_data_t data, char **buffer);

void free_statement_for_data(statement_data_t data);

#endif
