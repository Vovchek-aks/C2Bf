#include "token_keyword.h"
#include "token_dict_macro.h"

TOKEN_DICT_WITH_WRITE(token_keyword_data_t, keyword_t, char *, keyword_name_to_str_t, keyword_to_str,
                      token_keyword_get_status, token_keyword_get_data_from, write_token_keyword_data)


void token_keyword_init(void) {
    dict_alloc(keyword_to_str);
    dict_set(keyword_to_str, keyword_return, "return");
    dict_set(keyword_to_str, keyword_if, "if");
    dict_set(keyword_to_str, keyword_else, "else");
    dict_set(keyword_to_str, keyword_switch, "switch");
    dict_set(keyword_to_str, keyword_case, "case");
    dict_set(keyword_to_str, keyword_default, "default");
    dict_set(keyword_to_str, keyword_for, "for");
    dict_set(keyword_to_str, keyword_while, "while");
    dict_set(keyword_to_str, keyword_do, "do");
    dict_set(keyword_to_str, keyword_break, "break");
    dict_set(keyword_to_str, keyword_continue, "continue");
    dict_set(keyword_to_str, keyword_static, "static");
    dict_set(keyword_to_str, keyword_struct, "struct");
    dict_set(keyword_to_str, keyword_union, "union");
    dict_set(keyword_to_str, keyword_enum, "enum");
    dict_set(keyword_to_str, keyword_typedef, "typedef");
    dict_set(keyword_to_str, keyword_const, "const");
    dict_set(keyword_to_str, keyword_sizeof, "sizeof");
    dict_set(keyword_to_str, keyword_typeof, "typeof");
}
