#ifndef STRING_HELPER
#define STRING_HELPER

#define string_for(line, element) for (char element = *(line); element; element = *(++(line)))

#define string_append(buffer, alpha) *((*(buffer))++) = (alpha)

void string_extend(char **buffer, char *source);

#endif