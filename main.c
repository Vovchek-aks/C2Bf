#include <stdint.h>
#include <stdio.h>
#include "tokenization/tokenization.c"
#include "parsing/parsing.c"
#include "translation/translation.c"


int32_t main() {
    tokenization_init();
    char *code = "int32_t main() {\n    return 0;\n}\n";

    tokens_t tokens = tokenize(code);
    print_tokens(tokens);

//    program_t *program = parse(tokens);
//    char *bf = translate_to_bf(program);
//
//    printf("%s", bf);

    return 0;
}
