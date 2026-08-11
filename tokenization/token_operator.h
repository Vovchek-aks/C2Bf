#include "tokenizer.h"

#ifndef TOKEN_OPERATOR
#define TOKEN_OPERATOR

#define TOKEN_OPERATOR_NAME "TOKEN_OPERATOR"

typedef enum {
    operator_semicolon,
    operator_colon,
    operator_comma,
    operator_dot,
    operator_exclamation,
    operator_question,
    operator_equals,
    operator_double_equals,
    operator_exclamation_equals,
    operator_plus,
    operator_plus_equals,
    operator_double_plus,
    operator_minus,
    operator_minus_equals,
    operator_double_minus,
    operator_star,
    operator_star_equals,
    operator_slash,
    operator_slash_equals,
    operator_percent,
    operator_percent_equals,
    operator_ampersand,
    operator_ampersand_equals,
    operator_double_ampersand,
    operator_vertical,
    operator_vertical_equals,
    operator_double_vertical,
    operator_hat,
    operator_hat_equals,
    operator_greater,
    operator_double_greater,
    operator_double_greater_equals,
    operator_greater_equals,
    operator_smaller,
    operator_double_smaller,
    operator_double_smaller_equals,
    operator_smaller_equals,
    operator_open_bracket,
    operator_close_bracket,
    operator_open_curly,
    operator_close_curly,
    operator_open_square,
    operator_close_square,
    operator_count __attribute__((unused))
} operator_t;

typedef struct {
    operator_t name;
} token_operator_data_t;

void token_operator_init(void);

tokenization_status_t token_operator_get_status(char *line);

token_operator_data_t token_operator_get_data_from(char *line);

void write_token_operator_data(token_operator_data_t data, char **buffer);

#endif