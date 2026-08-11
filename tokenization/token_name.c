#include "token_name.h"
#include "../string_helper/string_helper.h"
#include <string.h>
#include <ctype.h>

tokenization_status_t token_name_get_status(char *line) {
    if (isdigit(*line))
        return tokenization_status_incorrect;

    for (char alpha = *line; alpha; alpha = *(++line))
        if (!(isalnum(alpha) || alpha == '_'))
            return tokenization_status_incorrect;

    return tokenization_status_correct;
}

token_name_data_t token_name_get_data_from(char *line) {
    char *buffer = malloc(strlen(line));
    strcpy(buffer, line);
    token_name_data_t data = {buffer};
    return data;
}

void write_token_name_data(token_name_data_t data, char **buffer) {
    string_extend(buffer, "\"");
    string_extend(buffer, data.name);
    string_extend(buffer, "\"");
}
