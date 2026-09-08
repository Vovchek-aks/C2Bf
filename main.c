#include <stdint.h>
#include "string_helper/string_helper.c"
#include "files.c"
#include "tokenization/tokenization.c"
#include "parsing/parsing.c"
#include "translation/translation.c"

int32_t main(int32_t argc, char **argv) {
    tokenization_init();
    parsing_init();

    if (argc < 2) {
        printf("Correct usage: c2bf filename.c\n");
        return -1;
    }
    char *filename = argv[1];
    char *code = read_entire_file(filename);

    printf("%s\n=====================================================================\n", code);

    tokens_t tokens = tokenize(code);
    print_tokens(tokens);

//    statement_t *statement = strictly_parse_statement(list_view(tokens));
//    print_statement(statement);

//    program_t *program = parse(tokens);
//    char *bf = translate_to_bf(program);
//
//    printf("%s", bf);

    return 0;
}
