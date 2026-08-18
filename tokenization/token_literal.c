#include "token_literal.h"
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define CANNOT_BE_ESCAPE_RESULT ' '

#define set_escape_character_of(key, value) dict_set_cmp(escape_character_of, key, value, strcmp)

DICT(char *, char) escape_character_of;

void token_literal_init(void) {
    dict_alloc(escape_character_of);
    set_escape_character_of("\\n", '\n');
    set_escape_character_of("\\r", '\n');
    set_escape_character_of("\\t", '\t');
    set_escape_character_of("\\0", '\0');
    set_escape_character_of("\\\'", '\'');
    set_escape_character_of("\\\"", '\"');
    set_escape_character_of("\\\\", '\\');
}

tokenization_status_t token_literal_number_get_status(char *line) {
    size_t dots_count = strcnt(line, '.');
    if (dots_count > 1)
        return tokenization_status_incorrect;

    for (char alpha = *line; alpha; alpha = *(++line))
        if (!(isdigit(alpha) || alpha == '.'))
            return tokenization_status_incorrect;

    return tokenization_status_correct;
}

token_literal_data_t token_literal_number_get_data_from(char *line) {
    size_t dots_count = strcnt(line, '.');
    assert(dots_count <= 1);

    size_t length = strlen(line);
    char *buffer = malloc(length + 1);
    buffer[length] = 0;
    strcpy(buffer, line);

    token_literal_data_t data = {
        .kind = dots_count == 0 ? token_literal_kind_int : token_literal_kind_float,
        .line = buffer
    };

    return data;
}

static void escape_str(char *line, char *buffer) {
    assert(line);
    if (!*line)
        return;

    uint8_t is_just_escaped = 0;
    size_t index = 0;
    buffer[index++] = *(line++);
    for (char alpha = *line; alpha; alpha = *(++line)) {
        buffer[index++] = alpha;
        if (buffer[index - 2] != '\\' || is_just_escaped) {
            is_just_escaped = 0;
            continue;
        }

        char escaped = CANNOT_BE_ESCAPE_RESULT;
        dict_get_cmp(escape_character_of, &buffer[index - 2], escaped, strcmp);
        assert(escaped != CANNOT_BE_ESCAPE_RESULT);
        buffer[--index - 1] = escaped;
        buffer[index] = 0;
        is_just_escaped = 1;
    }
}

static void unescape_str(char *line, char *buffer) {
    size_t index = 0;
    for (char alpha = *line; alpha; alpha = *(++line)) {
        uint8_t is_contains;
        dict_contains_value(escape_character_of, alpha, is_contains);
        if (!is_contains) {
            buffer[index++] = alpha;
            continue;
        }

        char *key;
        dict_get_key(escape_character_of, alpha, key);
        strcpy(&buffer[index], key);
        index += strlen(key);
    }
}

token_literal_data_t token_literal_str_or_char_try_get_data_from(char *line) {
    size_t length = strlen(line);
    assert(length > 1);
    assert(line[0] == line[length - 1]);
    assert(strcnt("'\"", line[0]) != 0);

    token_literal_kind_t kind = line[0] == '"' ? token_literal_kind_str : token_literal_kind_char;

    length -= 2;
    char buffer[length + 1] = {};
    strncpy(buffer, line + 1, length);

    char raw_escaped[length + 1] = {};
    escape_str(buffer, raw_escaped);

    length = strlen(raw_escaped);
    char *escaped = malloc(length + 1);
    strcpy(escaped, raw_escaped);

    assert(kind != token_literal_kind_char || length == 1);
    token_literal_data_t data = {
        .kind = kind,
        .line = escaped
    };
    return data;
}

void write_token_literal_data(token_literal_data_t data, char **buffer) {
    char *type_;
    switch (data.kind) {
        case token_literal_kind_int:
            type_ = "int";
            break;
        case token_literal_kind_float:
            type_ = "float";
            break;
        case token_literal_kind_char:
            type_ = "char";
            break;
        case token_literal_kind_str:
            type_ = "str";
            break;
        default:
            assert(0);
    }
    string_extend(buffer, type_);
    string_extend(buffer, ": ");

    if (data.kind == token_literal_kind_float || data.kind == token_literal_kind_int) {
        string_extend(buffer, data.line);
        return;
    }

    char sub_buffer[256] = {};
    unescape_str(data.line, sub_buffer);

    char *quote = data.kind == token_literal_kind_str ? "\"" : "'";

    string_extend(buffer, quote);
    string_extend(buffer, sub_buffer);
    string_extend(buffer, quote);
}
