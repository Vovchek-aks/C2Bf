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

program_t *parse_program(tokens_t tokens) {
    assert(is_list_view(tokens));

    function_t *main = parse_function(tokens);
    if (!main || strcmp(main->name->name, MAIN_FUNCTION_NAME) != 0)
        display_parsing_error(tokens,
                              main ?
                              "Main function must be named main." :
                              "Cannot parse main function");

    program_t *program = malloc(sizeof(program));
    program->main = main;
    return program;
}

function_t *parse_function(tokens_t tokens) {
    tokens_t original_tokens = tokens;

    if (!chop_operator(&tokens, operator_close_curly, chop_direction_back))
        return NULL;

    token_t *open_curly = get_paired_bracket(tokens,
                                             operator_open_curly,
                                             operator_close_curly,
                                             chop_direction_back);
    if (!open_curly)
        return NULL;

    tokens_t left = split_by(open_curly, &tokens);

    if (!chop_operator(&left, operator_close_round, chop_direction_back))
        return NULL;

    if (!chop_type(&left, builtin_type_void, chop_direction_back)) // todo
        return NULL;

    if (!chop_operator(&left, operator_open_round, chop_direction_back))
        return NULL;

    token_t *name = chop_back(&left, token_kind_name);
    if (!name)
        return NULL;

    type_t *type = parse_type(left, true);
    if (!type)
        return NULL;

    tokens.data--;
    tokens.count += 2;
    statement_t *body = parse_statement(tokens, true);
    if (!body || body->kind != statement_kind_scope)
        return NULL;

    function_t *function = malloc(sizeof(function_t));
    function->tokens = original_tokens;
    function->name = &name->data.as_name;
    function->type = type;
    function->body = body;

    return function;
}

char function_printing_buffer[PROGRAM_PRINTING_MAX_LENGTH];

void write_function(function_t *function, char **buffer) {
    memset(function_printing_buffer, 0, sizeof(function_printing_buffer));
    char *line = function_printing_buffer;
    
    line += sprintf(line, "%s(\"%s\"):", FUNCTION_NAME, function->name->name);

    string_extend(&line, "\n.type = ");
    write_type(function->type, &line);

    string_extend(&line, "\n.body = ");
    write_statement(function->body, &line);

    adjust_level(function_printing_buffer, buffer);
}

char program_printing_buffer[PROGRAM_PRINTING_MAX_LENGTH];

void print_program(program_t *program) {
    memset(program_printing_buffer, 0, sizeof(program_printing_buffer));
    char *buffer = program_printing_buffer;

    write_function(program->main, &buffer);
    printf("%s\n", program_printing_buffer);
}
