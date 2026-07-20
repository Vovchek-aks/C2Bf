#include <stdint.h>
#include <stdio.h>
#include "tokenization/tokenization.c"
#include "parsing/parsing.c"
#include "translation/translation.c"


int32_t main() {
    tokenization_init();
    char *code = "uint8_t _aboba ; ";

    int a = 0;

    tokens_t tokens = tokenize(code);
    print_tokens(tokens);

//    program_t *program = parse(tokens);
//    char *bf = translate_to_bf(program);
//
//    printf("%s", bf);

    return 0;
}
