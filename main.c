#include <stdint.h>
#include "tokenization/tokenization.c"
#include "parsing/parsing.c"
#include "translation/translation.c"

int32_t main(void) {
    tokenization_init();
    parsing_init();

//    char *code = "int32_t main(void) { printf(\"Hello, World!\"); return 0; } ";
    char *code = "aboba ";

    tokens_t tokens = tokenize(code);
//    print_tokens(tokens);

    expression_t *expression = parse_expression(tokens);
    print_expression(expression);

//    program_t *program = parse(tokens);
//    char *bf = translate_to_bf(program);
//
//    printf("%s", bf);

    return 0;
}
