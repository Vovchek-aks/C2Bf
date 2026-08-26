#include "parsing.h"
#include "fake_tokens.c"
#include "expressions/expressions.c"
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "modernize-use-nullptr"

void parsing_init() {
    expressions_parsing_init();
    fake_tokens_init();
}

program_t *parse(tokens_t tokens) {
    return NULL;
}