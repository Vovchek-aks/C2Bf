#include <stdint.h>
#include <stdio.h>
#include "tokenization/tokenization.c"
#include "parsing/parsing.c"
#include "translation/translation.c"

int32_t main() {
    tokenization_init();

    char *code = "uint8_t int8_t   uint16_t int16_t \n uint32_t int32_t \tuint64_t int64_t  ";

    tokens_t tokens = tokenize(code);
    print_tokens(tokens);

//    program_t *program = parse(tokens);
//    char *bf = translate_to_bf(program);
//
//    printf("%s", bf);

    return 0;
}
