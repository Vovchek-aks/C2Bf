#include "token_keyword.h"
#include "token_dict_macro.h"

#define keyword_name_to_str_set(key, value) dict_set(keyword_to_str, keyword_KV_t, char *, key, value)

typedef key_value(keyword_t, char *) keyword_KV_t;

TOKEN_DICT_WITH_WRITE(keyword_t, token_keyword_data_t, keyword_KV_t, keyword_name_to_str_t, keyword_to_str,
                      token_keyword_get_status, token_keyword_get_data_from, write_token_keyword_data)

void token_keyword_init(void) {
    dict_alloc(keyword_to_str, keyword_KV_t);
    keyword_name_to_str_set(return_, "return");
    keyword_name_to_str_set(if_, "if");
    keyword_name_to_str_set(else_, "else");
    keyword_name_to_str_set(switch_, "switch");
    keyword_name_to_str_set(case_, "case");
    keyword_name_to_str_set(default_, "default");
    keyword_name_to_str_set(for_, "for");
    keyword_name_to_str_set(while_, "while");
    keyword_name_to_str_set(do_, "do");
    keyword_name_to_str_set(break_, "break");
    keyword_name_to_str_set(continue_, "continue");
    keyword_name_to_str_set(static_, "static");
    keyword_name_to_str_set(struct_, "struct");
    keyword_name_to_str_set(union_, "union");
    keyword_name_to_str_set(enum_, "enum");
    keyword_name_to_str_set(typedef_, "typedef");
    keyword_name_to_str_set(const_, "const");
    keyword_name_to_str_set(sizeof_, "sizeof");
}
