#ifndef PARSING
#define PARSING

#include "../tokenization/tokenization.h"
#include "expressions/expressions.h"

typedef struct {

} program_t;

void parsing_init();

program_t *parse(tokens_t tokens);

#endif
