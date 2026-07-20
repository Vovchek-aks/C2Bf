#include "token_type.h"
#include "token_dict_macro.h"

#define type_name_to_str_set(key, value) dict_set(type_name_to_str, type_and_name_t, char *, key, value)

typedef key_value(type_name_t, char *) type_and_name_t;

TOKEN_DICT(type_name_t, token_type_data_t, type_and_name_t, type_name_to_str_t, type_name_to_str,
           token_type_get_status, token_type_get_data_from, write_token_type_data)

void token_type_init(void) {
    dict_alloc(type_name_to_str, type_and_name_t);
    type_name_to_str_set(uint8, "uint8_t");
    type_name_to_str_set(int8, "int8_t");
    type_name_to_str_set(uint16, "uint16_t");
    type_name_to_str_set(int16, "int16_t");
    type_name_to_str_set(uint32, "uint32_t");
    type_name_to_str_set(int32, "int32_t");
    type_name_to_str_set(uint64, "uint64_t");
    type_name_to_str_set(int64, "int64_t");
}
