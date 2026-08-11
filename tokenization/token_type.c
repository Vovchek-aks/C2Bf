#include "token_type.h"
#include "token_dict_macro.h"

TOKEN_DICT_WITH_WRITE(token_type_data_t, builtin_type_t, char *, type_name_to_str_t, type_name_to_str,
                      token_type_get_status, token_type_get_data_from, write_token_type_data)

void token_type_init(void) {
    dict_alloc(type_name_to_str);
    dict_set(type_name_to_str, builtin_type_void, "void");
    dict_set(type_name_to_str, builtin_type_uint8, "uint8_t");
    dict_set(type_name_to_str, builtin_type_int8, "int8_t");
    dict_set(type_name_to_str, builtin_type_uint16, "uint16_t");
    dict_set(type_name_to_str, builtin_type_int16, "int16_t");
    dict_set(type_name_to_str, builtin_type_uint32, "uint32_t");
    dict_set(type_name_to_str, builtin_type_int32, "int32_t");
    dict_set(type_name_to_str, builtin_type_uint64, "uint64_t");
    dict_set(type_name_to_str, builtin_type_int64, "int64_t");
}
