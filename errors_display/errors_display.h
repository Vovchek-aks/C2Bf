#ifndef ERROR_DISPLAY
#define ERROR_DISPLAY

#include "../parsing/parsing.h"

void set_file(char *name, char *code);

void display_tokenization_error(size_t line, size_t symbol, char *message);

void display_bad_tokens(tokens_t tokens);

__MINGW_ATTRIB_NORETURN void display_parsing_error(tokens_t tokens, char *message);

__MINGW_ATTRIB_NORETURN void display_validation_error(statement_t *statement, char *message);

#endif
