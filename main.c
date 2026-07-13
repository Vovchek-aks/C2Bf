#include <stdint.h>
#include <stdio.h>
#include "tokenization/tokenization.c"
#include "parsing/parsing.c"
#include "translation/translation.c"

int32_t main() {
    char *code = "int32_t uint8_t int16_t";

    tokens_t tokens = tokenize(code);
    program_t *program = parse(tokens);
    char *bf = translate_to_bf(program);

    printf("%s", bf);

    return 0;
}
