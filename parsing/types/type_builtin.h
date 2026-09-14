#ifndef TYPE_BUILTIN
#define TYPE_BUILTIN

#include "../../tokenization/tokenization.h"
#include "types.h"

#define TYPE_BUILTIN_NAME "BuiltinType"

type_parsing_result_t type_builtin_get_data_from(tokens_t tokens, bool is_strict);

void write_type_builtin_data_from(type_builtin_data_t data, char **buffer);

void free_type_builtin_data(type_builtin_data_t data);

#endif
