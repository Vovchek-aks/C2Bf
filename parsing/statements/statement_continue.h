#ifndef STATEMENT_CONTINUE
#define STATEMENT_CONTINUE

#include "../../tokenization/tokenization.h"
#include "statements.h"

#define STATEMENT_continue_NAME "Continue"

statement_parsing_result_t statement_continue_get_data_from(tokens_t tokens, bool is_strict);

void write_statement_continue_data_from(statement_data_t data, char **buffer);

void free_statement_continue_data(statement_data_t data);

#endif
