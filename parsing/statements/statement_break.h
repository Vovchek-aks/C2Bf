#ifndef STATEMENT_BREAK
#define STATEMENT_BREAK

#include "../../tokenization/tokenization.h"
#include "statements.h"

#define STATEMENT_break_NAME "Break"

statement_parsing_result_t statement_break_get_data_from(tokens_t tokens, bool is_strict);

void write_statement_break_data_from(statement_data_t data, char **buffer);

void free_statement_break_data(statement_data_t data);

#endif
