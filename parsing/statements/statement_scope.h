#ifndef STATEMENT_SCOPE
#define STATEMENT_SCOPE

#include "../../tokenization/tokenization.h"
#include "statements.h"

#define STATEMENT_SCOPE_NAME "Scope"

statement_parsing_result_t statement_scope_get_data_from(tokens_t tokens);

void write_statement_scope_data_from(statement_scope_data_t data, char **buffer);

void free_statement_scope_data(statement_scope_data_t data);

#endif
