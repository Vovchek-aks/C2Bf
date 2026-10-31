#ifndef ERROR_DISPLAY
#define ERROR_DISPLAY

#include "../parsing/parsing.h"

void set_file(char *name, char *code);

void display_tokenization_error(size_t line, size_t symbol, char *message);

void display_bad_tokens(tokens_t tokens);

__MINGW_ATTRIB_NORETURN void display_parsing_error(tokens_t tokens, char *message);

#define display_validation_error(statement_or_expression, message) ({                                                  \
    display_bad_tokens((statement_or_expression)->tokens);                                                             \
    fprintf (stderr, "%s\n", (message));                                                                               \
    abort();                                                                                                           \
})

#endif
