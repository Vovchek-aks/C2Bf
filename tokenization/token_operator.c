#include "token_operator.h"
#include "token_dict_macro.h"
#include "../string_helper/string_helper.h"

typedef key_value(operator_t, char *) operator_KV_t;

TOKEN_DICT(operator_t, token_operator_data_t, operator_KV_t, operator_to_str_t, operator_to_str,
           token_operator_get_status, token_operator_get_data_from)

operator_to_str_t name_of;

void token_operator_init(void) {
    dict_alloc(operator_to_str);
    dict_set(operator_to_str, operator_semicolon, ";");
    dict_set(operator_to_str, operator_colon, ":");
    dict_set(operator_to_str, operator_comma, ",");
    dict_set(operator_to_str, operator_dot, ".");
    dict_set(operator_to_str, operator_exclamation, "!");
    dict_set(operator_to_str, operator_question, "?");
    dict_set(operator_to_str, operator_equals, "=");
    dict_set(operator_to_str, operator_double_equals, "==");
    dict_set(operator_to_str, operator_exclamation_equals, "!=");
    dict_set(operator_to_str, operator_plus, "+");
    dict_set(operator_to_str, operator_plus_equals, "+=");
    dict_set(operator_to_str, operator_double_plus, "++");
    dict_set(operator_to_str, operator_minus, "-");
    dict_set(operator_to_str, operator_minus_equals, "-=");
    dict_set(operator_to_str, operator_double_minus, "--");
    dict_set(operator_to_str, operator_star, "*");
    dict_set(operator_to_str, operator_star_equals, "*=");
    dict_set(operator_to_str, operator_slash, "/");
    dict_set(operator_to_str, operator_slash_equals, "/=");
    dict_set(operator_to_str, operator_percent, "%");
    dict_set(operator_to_str, operator_percent_equals, "%=");
    dict_set(operator_to_str, operator_ampersand, "&");
    dict_set(operator_to_str, operator_ampersand_equals, "&=");
    dict_set(operator_to_str, operator_double_ampersand, "&&");
    dict_set(operator_to_str, operator_vertical, "|");
    dict_set(operator_to_str, operator_vertical_equals, "|=");
    dict_set(operator_to_str, operator_double_vertical, "||");
    dict_set(operator_to_str, operator_hat, "^");
    dict_set(operator_to_str, operator_hat_equals, "^=");
    dict_set(operator_to_str, operator_greater, ">");
    dict_set(operator_to_str, operator_double_greater, ">>");
    dict_set(operator_to_str, operator_double_greater_equals, ">>=");
    dict_set(operator_to_str, operator_greater_equals, ">=");
    dict_set(operator_to_str, operator_smaller, "<");
    dict_set(operator_to_str, operator_double_smaller, "<<");
    dict_set(operator_to_str, operator_double_smaller_equals, "<<=");
    dict_set(operator_to_str, operator_smaller_equals, "<=");
    dict_set(operator_to_str, operator_open_bracket, "(");
    dict_set(operator_to_str, operator_close_bracket, ")");
    dict_set(operator_to_str, operator_open_curly, "{");
    dict_set(operator_to_str, operator_close_curly, "}");
    dict_set(operator_to_str, operator_open_square, "[");
    dict_set(operator_to_str, operator_close_square, "]");

    dict_alloc(name_of);
    dict_set(name_of, operator_semicolon, "semicolon");
    dict_set(name_of, operator_colon, "colon");
    dict_set(name_of, operator_comma, "comma");
    dict_set(name_of, operator_dot, "dot");
    dict_set(name_of, operator_exclamation, "exclamation");
    dict_set(name_of, operator_question, "question");
    dict_set(name_of, operator_equals, "equals");
    dict_set(name_of, operator_double_equals, "double_equals");
    dict_set(name_of, operator_exclamation_equals, "exclamation_equals");
    dict_set(name_of, operator_plus, "plus");
    dict_set(name_of, operator_plus_equals, "plus_equals");
    dict_set(name_of, operator_double_plus, "double_plus");
    dict_set(name_of, operator_minus, "minus");
    dict_set(name_of, operator_minus_equals, "minus_equals");
    dict_set(name_of, operator_double_minus, "double_minus");
    dict_set(name_of, operator_star, "star");
    dict_set(name_of, operator_star_equals, "star_equals");
    dict_set(name_of, operator_slash, "slash");
    dict_set(name_of, operator_slash_equals, "slash_equals");
    dict_set(name_of, operator_percent, "percent");
    dict_set(name_of, operator_percent_equals, "percent_equals");
    dict_set(name_of, operator_ampersand, "ampersand");
    dict_set(name_of, operator_ampersand_equals, "ampersand_equals");
    dict_set(name_of, operator_double_ampersand, "double_ampersand");
    dict_set(name_of, operator_vertical, "vertical");
    dict_set(name_of, operator_vertical_equals, "vertical_equals");
    dict_set(name_of, operator_double_vertical, "double_vertical");
    dict_set(name_of, operator_hat, "hat");
    dict_set(name_of, operator_hat_equals, "hat_equals");
    dict_set(name_of, operator_greater, "greater");
    dict_set(name_of, operator_double_greater, "double_greater");
    dict_set(name_of, operator_double_greater_equals, "double_greater_equals");
    dict_set(name_of, operator_greater_equals, "greater_equals");
    dict_set(name_of, operator_smaller, "smaller");
    dict_set(name_of, operator_double_smaller, "double_smaller");
    dict_set(name_of, operator_double_smaller_equals, "double_smaller_equals");
    dict_set(name_of, operator_smaller_equals, "smaller_equals");
    dict_set(name_of, operator_open_bracket, "open_bracket");
    dict_set(name_of, operator_close_bracket, "close_bracket");
    dict_set(name_of, operator_open_curly, "open_curly");
    dict_set(name_of, operator_close_curly, "close_curly");
    dict_set(name_of, operator_open_square, "open_square");
    dict_set(name_of, operator_close_square, "close_square");
}

void write_token_operator_data(token_operator_data_t data, char **buffer) {
    char *line = NULL;
    dict_get(name_of, data.name, line);
    assert(line != NULL);

    string_extend(buffer, line);
}