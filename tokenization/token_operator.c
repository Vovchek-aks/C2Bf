#include "token_operator.h"
#include "token_dict_macro.h"

#define operator_name_to_str_set(key, value) dict_set(operator_name_to_str, operator_KV_t, char *, key, value)

typedef key_value(operator_name_t, char *) operator_KV_t;

TOKEN_DICT(operator_name_t, token_operator_data_t, operator_KV_t, operator_name_to_str_t, operator_name_to_str,
           token_operator_get_status, token_operator_get_data_from, write_token_operator_data)

void token_operator_init(void) {
    dict_alloc(operator_name_to_str, operator_KV_t);
    operator_name_to_str_set(semicolon, ";");
    operator_name_to_str_set(colon, ":");
    operator_name_to_str_set(comma, ",");
    operator_name_to_str_set(dot, ".");
    operator_name_to_str_set(exclamation, "!");
    operator_name_to_str_set(question, "?");
    operator_name_to_str_set(equals, "=");
    operator_name_to_str_set(double_equals, "==");
    operator_name_to_str_set(exclamation_equals, "!=");
    operator_name_to_str_set(plus, "+");
    operator_name_to_str_set(plus_equals, "+=");
    operator_name_to_str_set(double_plus, "++");
    operator_name_to_str_set(minus, "-");
    operator_name_to_str_set(minus_equals, "-=");
    operator_name_to_str_set(double_minus, "--");
    operator_name_to_str_set(star, "*");
    operator_name_to_str_set(star_equals, "*=");
    operator_name_to_str_set(slash, "/");
    operator_name_to_str_set(slash_equals, "/=");
    operator_name_to_str_set(percent, "%");
    operator_name_to_str_set(percent_equals, "%=");
    operator_name_to_str_set(ampersand, "&");
    operator_name_to_str_set(ampersand_equals, "&=");
    operator_name_to_str_set(double_ampersand, "&&");
    operator_name_to_str_set(vertical, "|");
    operator_name_to_str_set(vertical_equals, "|=");
    operator_name_to_str_set(double_vertical, "||");
    operator_name_to_str_set(hat, "^");
    operator_name_to_str_set(hat_equals, "^=");
    operator_name_to_str_set(bigger, ">");
    operator_name_to_str_set(double_bigger, ">>");
    operator_name_to_str_set(double_bigger_equals, ">>=");
    operator_name_to_str_set(bigger_equals, ">=");
    operator_name_to_str_set(smaller, "<");
    operator_name_to_str_set(double_smaller, "<<");
    operator_name_to_str_set(double_smaller_equals, "<<=");
    operator_name_to_str_set(smaller_equals, "<=");
    operator_name_to_str_set(open_bracket, "(");
    operator_name_to_str_set(close_bracket, ")");
    operator_name_to_str_set(open_curly, "{");
    operator_name_to_str_set(close_curly, "}");
    operator_name_to_str_set(open_square, "[");
    operator_name_to_str_set(close_square, "]");
}
