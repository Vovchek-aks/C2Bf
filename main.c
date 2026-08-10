#include <stdint.h>
#include "string_helper/string_helper.c"
#include "tokenization/tokenization.c"
#include "parsing/parsing.c"
#include "translation/translation.c"

int32_t main(void) {
    tokenization_init();
    parsing_init();

//    char *code = "int32_t main(void) { printf(\"Hello, World!\"); return 0; } ";
    char *code = "aboba.biba[bar[69].baz[420]].fiz[555] ";

    printf("%s\n=====================================================================\n", code);

    tokens_t tokens = tokenize(code);
//    print_tokens(tokens);

    expression_t *expression = strictly_parse_expression(list_get_view(tokens, tokens_t));
    print_expression(expression);

//    program_t *program = parse(tokens);
//    char *bf = translate_to_bf(program);
//
//    printf("%s", bf);

    return 0;
}
