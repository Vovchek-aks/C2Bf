#include "string_helper.h"

void string_extend(char **buffer, char *source) {
    string_for(source, alpha)
        string_append(buffer, alpha);
}
