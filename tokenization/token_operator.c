#include "token_operator.h"
#include "token_dict_macro.h"

#define operator_name_to_str_set(key, value) dict_set(operator_name_to_str, operator_KV_t, char *, key, value)
#define name_of_set(key, value) dict_set(name_of, operator_KV_t, char *, key, value)

typedef key_value(operator_name_t, char *) operator_KV_t;

TOKEN_DICT(operator_name_t, token_operator_data_t, operator_KV_t, operator_name_to_str_t, operator_name_to_str,
           token_operator_get_status, token_operator_get_data_from)

operator_name_to_str_t name_of;

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

    dict_alloc(name_of, operator_KV_t);
    name_of_set(semicolon, "semicolon");
    name_of_set(colon, "colon");
    name_of_set(comma, "comma");
    name_of_set(dot, "dot");
    name_of_set(exclamation, "exclamation");
    name_of_set(question, "question");
    name_of_set(equals, "equals");
    name_of_set(double_equals, "double_equals");
    name_of_set(exclamation_equals, "exclamation_equals");
    name_of_set(plus, "plus");
    name_of_set(plus_equals, "plus_equals");
    name_of_set(double_plus, "double_plus");
    name_of_set(minus, "minus");
    name_of_set(minus_equals, "minus_equals");
    name_of_set(double_minus, "double_minus");
    name_of_set(star, "star");
    name_of_set(star_equals, "star_equals");
    name_of_set(slash, "slash");
    name_of_set(slash_equals, "slash_equals");
    name_of_set(percent, "percent");
    name_of_set(percent_equals, "percent_equals");
    name_of_set(ampersand, "ampersand");
    name_of_set(ampersand_equals, "ampersand_equals");
    name_of_set(double_ampersand, "double_ampersand");
    name_of_set(vertical, "vertical");
    name_of_set(vertical_equals, "vertical_equals");
    name_of_set(double_vertical, "double_vertical");
    name_of_set(hat, "hat");
    name_of_set(hat_equals, "hat_equals");
    name_of_set(bigger, "bigger");
    name_of_set(double_bigger, "double_bigger");
    name_of_set(double_bigger_equals, "double_bigger_equals");
    name_of_set(bigger_equals, "bigger_equals");
    name_of_set(smaller, "smaller");
    name_of_set(double_smaller, "double_smaller");
    name_of_set(double_smaller_equals, "double_smaller_equals");
    name_of_set(smaller_equals, "smaller_equals");
    name_of_set(open_bracket, "open_bracket");
    name_of_set(close_bracket, "close_bracket");
    name_of_set(open_curly, "open_curly");
    name_of_set(close_curly, "close_curly");
    name_of_set(open_square, "open_square");
    name_of_set(close_square, "close_square");
}

void write_token_operator_data(token_operator_data_t data, char *buffer) {                                                                  \
    char *line = NULL;                                                                                             \
    dict_get(name_of, operator_KV_t , data.name, line);                                                                    \
    assert(line != NULL);                                                                                          \
                                                                                                                   \
    strcpy(buffer, line);                                                                                          \
}