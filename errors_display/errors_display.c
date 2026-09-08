#include "errors_display.h"
#include "../parsing/tokens_operations.h"
#include <stdio.h>

#define ERROR_CHAR '^'

char *errors_display_filename;
char *errors_display_code;

void set_file(char *name, char *code) {
    errors_display_filename = name;
    errors_display_code = code;
}

static void display_one_bad_line(size_t line, size_t error_start_symbol, size_t error_end_symbol) {
    size_t seen_lines = 0;
    char *line_start = errors_display_code;
    while (seen_lines < line - 1) {
        if (*line_start != '\n') {
            line_start++;
            continue;
        }

        seen_lines++;
        line_start += 2;
    }
    if (line > 1)
        line_start--;
    char *line_end = line_start;
    while (*(++line_end) != '\n');

    size_t length = fprintf(stderr, "%s:%lld:%lld: ",
                           errors_display_filename, line, error_start_symbol);
    fprintf(stderr, "%.*s\n", (int32_t)(line_end - line_start), line_start);
    for (int i = 0; i < length + error_start_symbol - 1; ++i)
        fprintf(stderr, " ");

    for (int i = 0; i < error_end_symbol - error_start_symbol; ++i)
        fprintf(stderr, "%c", ERROR_CHAR);
    
    fprintf(stderr, "\n");
}

__MINGW_ATTRIB_NORETURN void display_tokenization_error(size_t line, size_t symbol, char *message) {
    display_one_bad_line(line, symbol, symbol + 1);
    fprintf(stderr, "%s\n", message);
    abort();
}

void display_bad_tokens(tokens_t tokens) {
    assert(is_list_view(tokens));
    assert(tokens.count > 0);

    tokens_t on_the_same_line = list_view_on(list_view_chop_first(tokens), tokens_t);
    while (tokens.count > 0) {
        if (tokens.data[0].info.line == on_the_same_line.data[0].info.line) {
            combine(&on_the_same_line, list_view_on(list_view_chop_first(tokens), tokens_t));
            continue;
        }

        display_one_bad_line(on_the_same_line.data[0].info.line,
                             on_the_same_line.data[0].info.symbol,
                             list_last(on_the_same_line).info.symbol
                             + list_last(on_the_same_line).info.count);
        on_the_same_line = list_view_on(list_view_chop_first(tokens), tokens_t);
    }
    display_one_bad_line(on_the_same_line.data[0].info.line,
                         on_the_same_line.data[0].info.symbol,
                         list_last(on_the_same_line).info.symbol
                         + list_last(on_the_same_line).info.count);
}

__MINGW_ATTRIB_NORETURN void display_parsing_error(tokens_t tokens, char *message) {
    display_bad_tokens(tokens);
    fprintf(stderr, "%s\n", message);
    abort();
}

