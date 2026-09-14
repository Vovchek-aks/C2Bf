#include "parsing.h"
#include "fake_tokens.c"
#include "expressions/expressions.c"
#include "statements/statements.c"
#include "types/types.c"
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

void init_parsing() {
    init_expressions_parsing();
    init_statements_parsing();
    init_types_parsing();

    init_fake_tokens();
}

program_t *parse(tokens_t tokens) {
    return NULL;
}