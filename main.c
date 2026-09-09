#include "shut_windows_yapping_up.c"
#include <stdint.h>
#include "errors_display/errors_display.h"
#include "string_helper/string_helper.c"
#include "files.c"
#include "tokenization/tokenization.c"
#include "parsing/parsing.c"
#include "translation/translation.c"
#include "errors_display/errors_display.c"

int32_t main(int32_t argc, char **argv) {
    init_tokenization();
    init_parsing();

    if (argc < 2) {
        printf("Correct usage: c2bf filename.c\n");
        return -1;
    }
    char *filename = argv[1];
    char *code = read_entire_file(filename);
    set_file(filename, code);

    tokens_t tokens = tokenize(code);
    statement_t *statement = parse_statement(list_view(tokens), true);

    printf("%s\n=====================================================================\n", code);
    print_statement(statement);
//    print_tokens(tokens);

//    program_t *program = parse(tokens);
//    char *bf = translate_to_bf(program);
//
//    printf("%s", bf);

    return 0;
}
