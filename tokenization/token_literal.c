#include "token_literal.h"
#include <string.h>
#include <ctype.h>
#include <assert.h>

static size_t strcnt(char *line, char target) {
    size_t count = 0;
    for (char c = *line; c; c = *(++line))
        if (c == target)
            count++;

    return count;
}

tokenization_status_t token_literal_get_status(char *line) {
    size_t dots_count = strcnt(line, '.');
    if (dots_count > 1)
        return incorrect;

    for (char c = *line; c; c = *(++line))
        if (!(isdigit(c) || c == '.'))
            return incorrect;

    return correct;
}

token_literal_data_t token_literal_get_data_from(char *line) {
    size_t dots_count = strcnt(line, '.');
    assert(dots_count <= 1);

    char *buffer = malloc(strlen(line));
    strcpy(buffer, line);

    token_literal_data_t data = {
            .kind = dots_count == 0 ? int_ : float_,
            .line = buffer
    };

    return data;
}

void write_token_literal_data(token_literal_data_t data, char *buffer) {
    char *type_;
    switch (data.kind) {
        case int_:
            type_ = "int";
            break;
        case float_:
            type_ = "float";
            break;
        case str:
            type_ = "str";
            break;
        default:
            assert(0);
    }
    strcpy(buffer, type_);
    strcpy(buffer + strlen(buffer), ": ");
    strcpy(buffer + strlen(buffer), data.line);
}
