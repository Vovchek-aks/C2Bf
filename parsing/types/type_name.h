#ifndef TYPE_NAME
#define TYPE_NAME

#include "../../tokenization/tokenization.h"
#include "parsed_types.h"

#define TYPE_NAME_NAME "NameType"

type_parsing_result_t type_name_get_data_from(tokens_t tokens, bool is_strict);

void write_type_name_data_from(type_name_data_t data, char **buffer);

void free_type_name_data(type_name_data_t data);

#endif
