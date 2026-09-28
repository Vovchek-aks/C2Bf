#ifndef STATEMENT_ASSIGNMENT
#define STATEMENT_ASSIGNMENT

#include "../../tokenization/tokenization.h"
#include "statements.h"

#define STATEMENT_assignment_NAME "Assignment"

void init_assignment_parsing();

statement_parsing_result_t statement_assignment_get_data_from(tokens_t tokens, bool is_strict);

void write_statement_assignment_data_from(statement_data_t data, char **buffer);

void free_statement_assignment_data(statement_data_t data);

#endif
