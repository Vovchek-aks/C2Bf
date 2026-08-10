#include "tokenizer.h"

#ifndef TOKEN_OPERATOR
#define TOKEN_OPERATOR

#define TOKEN_OPERATOR_NAME "TOKEN_OPERATOR"

typedef enum {
    operator_kind_semicolon,
    operator_kind_colon,
    operator_kind_comma,
    operator_kind_dot,
    operator_kind_exclamation,
    operator_kind_question,
    operator_kind_equals,
    operator_kind_double_equals,
    operator_kind_exclamation_equals,
    operator_kind_plus,
    operator_kind_plus_equals,
    operator_kind_double_plus,
    operator_kind_minus,
    operator_kind_minus_equals,
    operator_kind_double_minus,
    operator_kind_star,
    operator_kind_star_equals,
    operator_kind_slash,
    operator_kind_slash_equals,
    operator_kind_percent,
    operator_kind_percent_equals,
    operator_kind_ampersand,
    operator_kind_ampersand_equals,
    operator_kind_double_ampersand,
    operator_kind_vertical,
    operator_kind_vertical_equals,
    operator_kind_double_vertical,
    operator_kind_hat,
    operator_kind_hat_equals,
    operator_kind_greater,
    operator_kind_double_greater,
    operator_kind_double_greater_equals,
    operator_kind_greater_equals,
    operator_kind_smaller,
    operator_kind_double_smaller,
    operator_kind_double_smaller_equals,
    operator_kind_smaller_equals,
    operator_kind_open_bracket,
    operator_kind_close_bracket,
    operator_kind_open_curly,
    operator_kind_close_curly,
    operator_kind_open_square,
    operator_kind_close_square,
    operator_kinds_count
} operator_kind_t;

typedef struct {
    operator_kind_t name;
} token_operator_data_t;

void token_operator_init(void);

tokenization_status_t token_operator_get_status(char *line);

token_operator_data_t token_operator_get_data_from(char *line);

void write_token_operator_data(token_operator_data_t data, char **buffer);

#endif