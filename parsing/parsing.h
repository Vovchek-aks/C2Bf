#include "../tokenization/tokenization.h"
#include "expressions/expressions.h"

#ifndef PARSING
#define PARSING

typedef struct {

} program_t;

void parsing_init();

program_t *parse(tokens_t tokens);

#endif
