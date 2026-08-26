#ifndef STRING_HELPER
#define STRING_HELPER

#include <string.h>

#define string_for(line, element) for (char element = *(line); element; element = *(++(line)))

#define string_append(buffer, alpha) do { *((*(buffer))++) = (alpha); } while (0)

void string_extend(char **buffer, char *source);

size_t strcnt(char *line, char target);

#endif
