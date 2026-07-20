#include "tokenizer.h"

#ifndef TOKEN_OPERATOR
#define TOKEN_OPERATOR

#define TOKEN_OPERATOR_NAME "TOKEN_OPERATOR"

typedef enum {
    semicolon,
    colon,
    comma,
    dot,
    exclamation,
    question,
    equals,
    double_equals,
    exclamation_equals,
    plus,
    plus_equals,
    double_plus,
    minus,
    minus_equals,
    double_minus,
    star,
    star_equals,
    slash,
    slash_equals,
    percent,
    percent_equals,
    ampersand,
    ampersand_equals,
    double_ampersand,
    vertical,
    vertical_equals,
    double_vertical,
    hat,
    hat_equals,
    bigger,
    double_bigger,
    double_bigger_equals,
    bigger_equals,
    smaller,
    double_smaller,
    double_smaller_equals,
    smaller_equals,
    open_bracket,
    close_bracket,
    open_curly,
    close_curly,
    open_square,
    close_square,
    operators_count
} operator_name_t;

typedef struct {
    operator_name_t name;
} token_operator_data_t;

void token_operator_init(void);

tokenization_status_t token_operator_get_status(char *line);

token_operator_data_t token_operator_get_data_from(char *line);

void write_token_operator_data(token_operator_data_t data, char *buffer);

#endif