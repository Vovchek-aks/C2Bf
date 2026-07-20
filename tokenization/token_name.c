#include "token_name.h"
#include <string.h>
#include <ctype.h>

tokenization_status_t token_name_get_status(char *line) {
    if (isdigit(*line))
        return incorrect;

    for (char c = *line; c; c = *(++line))
        if (!(isalnum(c) || c == '_'))
            return incorrect;

    return correct;
}

token_name_data_t token_name_get_data_from(char *line) {
    char *buffer = malloc(strlen(line));
    strcpy(buffer, line);
    token_name_data_t data = {buffer};
    return data;
}

void write_token_name_data(token_name_data_t data, char *buffer) {
    buffer[0] = '"';
    strcpy(buffer + 1, data.line);
    buffer[strlen(buffer)] = '"';
}
