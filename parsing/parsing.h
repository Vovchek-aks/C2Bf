#ifndef PARSING
#define PARSING

#include "../tokenization/tokenization.h"
#include "expressions/expressions.h"

typedef struct {

} program_t;

void init_parsing();

program_t *parse(tokens_t tokens);

#endif
