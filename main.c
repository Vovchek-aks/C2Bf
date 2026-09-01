#include <stdint.h>
#include "string_helper/string_helper.c"
#include "tokenization/tokenization.c"
#include "parsing/parsing.c"
#include "translation/translation.c"

int32_t main(void) {
    tokenization_init();
    parsing_init();

//    char *code = "int32_t main(void) { printf(\"Hello, World!\"); return 0; } ";
    char *code = "desvor99(2 + 2); ";

    printf("%s\n=====================================================================\n", code);

    tokens_t tokens = tokenize(code);
//    print_tokens(tokens);

    statement_t *statement = strictly_parse_statement(list_view(tokens), true);
    print_statement(statement);

//    program_t *program = parse(tokens);
//    char *bf = translate_to_bf(program);
//
//    printf("%s", bf);

    return 0;
}
