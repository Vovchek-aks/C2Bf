#ifndef STATEMENT_RETURN
#define STATEMENT_RETURN

#include "../../tokenization/tokenization.h"
#include "statements.h"

#define STATEMENT_RETURN_NAME "Return"

statement_parsing_result_t statement_return_get_data_from(tokens_t tokens, bool is_strict);

void write_statement_return_data_from(statement_return_data_t data, char **buffer);

void free_statement_return_data(statement_return_data_t data);

#endif
