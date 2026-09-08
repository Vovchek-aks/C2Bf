#ifndef ERROR_DISPLAY
#define ERROR_DISPLAY

#include "../tokenization/tokenization.h"

void set_file(char *name, char *code);

void display_tokenization_error(size_t line, size_t symbol, char *message);

void display_bad_tokens(tokens_t tokens);

void display_parsing_error(tokens_t tokens, char *message);

#endif
