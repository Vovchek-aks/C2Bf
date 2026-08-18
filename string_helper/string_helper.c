#include "string_helper.h"

void string_extend(char **buffer, char *source) {
    strcpy(*buffer, source);
    *buffer += strlen(source);
}

size_t strcnt(char *line, char target) {
    size_t count = 0;
    for (char alpha = *line; alpha; alpha = *(++line))
        if (alpha == target)
            count++;

    return count;
}
