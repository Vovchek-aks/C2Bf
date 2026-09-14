#ifndef PARSING
#define PARSING

#include "../tokenization/tokenization.h"
#include "expressions/expressions.h"
#include "statements/statements.h"
#include "types/types.h"

#define PROGRAM_PRINTING_MAX_LENGTH (1024 * 1024)

#define MAIN_FUNCTION_NAME "main"

#define FUNCTION_NAME "Function"

typedef struct {
    tokens_t tokens;
    token_name_data_t *name;
    type_t *type;
    statement_t *body;
} function_t;

typedef struct {
    function_t *main;
} program_t;

void init_parsing();

program_t *parse_program(tokens_t tokens);

function_t *parse_function(tokens_t tokens);

void print_program(program_t *program);

#endif
