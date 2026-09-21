#ifndef STATEMENT_DO_WHILE
#define STATEMENT_DO_WHILE

#include "../../tokenization/tokenization.h"
#include "statements.h"

#define STATEMENT_DO_WHILE_NAME "DoWhile"

statement_parsing_result_t statement_do_while_get_data_from(tokens_t tokens, bool is_strict);

void write_statement_do_while_data_from(statement_while_data_t data, char **buffer);

void free_statement_do_while_data(statement_while_data_t data);

#endif
