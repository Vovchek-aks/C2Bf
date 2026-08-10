#include "token_operator.h"
#include "token_dict_macro.h"
#include "../string_helper/string_helper.h"

#define operator_to_str_set(key, value) dict_set(operator_to_str, operator_KV_t, char *, key, value)
#define name_of_set(key, value) dict_set(name_of, operator_KV_t, char *, key, value)

typedef key_value(operator_kind_t, char *) operator_KV_t;

TOKEN_DICT(operator_kind_t, token_operator_data_t, operator_KV_t, operator_to_str_t, operator_to_str,
           token_operator_get_status, token_operator_get_data_from)

operator_to_str_t name_of;

void token_operator_init(void) {
    dict_alloc(operator_to_str, operator_KV_t);
    operator_to_str_set(operator_kind_semicolon, ";");
    operator_to_str_set(operator_kind_colon, ":");
    operator_to_str_set(operator_kind_comma, ",");
    operator_to_str_set(operator_kind_dot, ".");
    operator_to_str_set(operator_kind_exclamation, "!");
    operator_to_str_set(operator_kind_question, "?");
    operator_to_str_set(operator_kind_equals, "=");
    operator_to_str_set(operator_kind_double_equals, "==");
    operator_to_str_set(operator_kind_exclamation_equals, "!=");
    operator_to_str_set(operator_kind_plus, "+");
    operator_to_str_set(operator_kind_plus_equals, "+=");
    operator_to_str_set(operator_kind_double_plus, "++");
    operator_to_str_set(operator_kind_minus, "-");
    operator_to_str_set(operator_kind_minus_equals, "-=");
    operator_to_str_set(operator_kind_double_minus, "--");
    operator_to_str_set(operator_kind_star, "*");
    operator_to_str_set(operator_kind_star_equals, "*=");
    operator_to_str_set(operator_kind_slash, "/");
    operator_to_str_set(operator_kind_slash_equals, "/=");
    operator_to_str_set(operator_kind_percent, "%");
    operator_to_str_set(operator_kind_percent_equals, "%=");
    operator_to_str_set(operator_kind_ampersand, "&");
    operator_to_str_set(operator_kind_ampersand_equals, "&=");
    operator_to_str_set(operator_kind_double_ampersand, "&&");
    operator_to_str_set(operator_kind_vertical, "|");
    operator_to_str_set(operator_kind_vertical_equals, "|=");
    operator_to_str_set(operator_kind_double_vertical, "||");
    operator_to_str_set(operator_kind_hat, "^");
    operator_to_str_set(operator_kind_hat_equals, "^=");
    operator_to_str_set(operator_kind_greater, ">");
    operator_to_str_set(operator_kind_double_greater, ">>");
    operator_to_str_set(operator_kind_double_greater_equals, ">>=");
    operator_to_str_set(operator_kind_greater_equals, ">=");
    operator_to_str_set(operator_kind_smaller, "<");
    operator_to_str_set(operator_kind_double_smaller, "<<");
    operator_to_str_set(operator_kind_double_smaller_equals, "<<=");
    operator_to_str_set(operator_kind_smaller_equals, "<=");
    operator_to_str_set(operator_kind_open_bracket, "(");
    operator_to_str_set(operator_kind_close_bracket, ")");
    operator_to_str_set(operator_kind_open_curly, "{");
    operator_to_str_set(operator_kind_close_curly, "}");
    operator_to_str_set(operator_kind_open_square, "[");
    operator_to_str_set(operator_kind_close_square, "]");

    dict_alloc(name_of, operator_KV_t);
    name_of_set(operator_kind_semicolon, "semicolon");
    name_of_set(operator_kind_colon, "colon");
    name_of_set(operator_kind_comma, "comma");
    name_of_set(operator_kind_dot, "dot");
    name_of_set(operator_kind_exclamation, "exclamation");
    name_of_set(operator_kind_question, "question");
    name_of_set(operator_kind_equals, "equals");
    name_of_set(operator_kind_double_equals, "double_equals");
    name_of_set(operator_kind_exclamation_equals, "exclamation_equals");
    name_of_set(operator_kind_plus, "plus");
    name_of_set(operator_kind_plus_equals, "plus_equals");
    name_of_set(operator_kind_double_plus, "double_plus");
    name_of_set(operator_kind_minus, "minus");
    name_of_set(operator_kind_minus_equals, "minus_equals");
    name_of_set(operator_kind_double_minus, "double_minus");
    name_of_set(operator_kind_star, "star");
    name_of_set(operator_kind_star_equals, "star_equals");
    name_of_set(operator_kind_slash, "slash");
    name_of_set(operator_kind_slash_equals, "slash_equals");
    name_of_set(operator_kind_percent, "percent");
    name_of_set(operator_kind_percent_equals, "percent_equals");
    name_of_set(operator_kind_ampersand, "ampersand");
    name_of_set(operator_kind_ampersand_equals, "ampersand_equals");
    name_of_set(operator_kind_double_ampersand, "double_ampersand");
    name_of_set(operator_kind_vertical, "vertical");
    name_of_set(operator_kind_vertical_equals, "vertical_equals");
    name_of_set(operator_kind_double_vertical, "double_vertical");
    name_of_set(operator_kind_hat, "hat");
    name_of_set(operator_kind_hat_equals, "hat_equals");
    name_of_set(operator_kind_greater, "greater");
    name_of_set(operator_kind_double_greater, "double_greater");
    name_of_set(operator_kind_double_greater_equals, "double_greater_equals");
    name_of_set(operator_kind_greater_equals, "greater_equals");
    name_of_set(operator_kind_smaller, "smaller");
    name_of_set(operator_kind_double_smaller, "double_smaller");
    name_of_set(operator_kind_double_smaller_equals, "double_smaller_equals");
    name_of_set(operator_kind_smaller_equals, "smaller_equals");
    name_of_set(operator_kind_open_bracket, "open_bracket");
    name_of_set(operator_kind_close_bracket, "close_bracket");
    name_of_set(operator_kind_open_curly, "open_curly");
    name_of_set(operator_kind_close_curly, "close_curly");
    name_of_set(operator_kind_open_square, "open_square");
    name_of_set(operator_kind_close_square, "close_square");
}

void write_token_operator_data(token_operator_data_t data, char **buffer) {
    char *line = NULL;
    dict_get(name_of, operator_KV_t , data.name, line);
    assert(line != NULL);

    string_extend(buffer, line);
}