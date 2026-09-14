#ifndef STATEMENT_VARIABLE_DECLARATION
#define STATEMENT_VARIABLE_DECLARATION

#include "../../tokenization/tokenization.h"
#include "statements.h"

#define STATEMENT_VARIABLE_DECLARATION_NAME "VariableDeclaration"

statement_parsing_result_t statement_variable_declaration_get_data_from(tokens_t tokens, bool is_strict);

void write_statement_variable_declaration_data_from(statement_variable_declaration_data_t data, char **buffer);

void free_statement_variable_declaration_data(statement_variable_declaration_data_t data);

#endif
