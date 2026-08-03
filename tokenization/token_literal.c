#include "token_literal.h"
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define escape_character_of_set(key, value) dict_set(escape_character_of, escape_KV_t, char, key, value)

#define CANNOT_BE_ESCAPE_RESULT ' '

typedef key_value(char *, char) escape_KV_t;
typedef DICT(escape_KV_t) escape_character_of_t;

escape_character_of_t escape_character_of;

void token_literal_init(void) {
    dict_alloc(escape_character_of, escape_KV_t);
    escape_character_of_set("\\n", '\n');
    escape_character_of_set("\\r", '\n');
    escape_character_of_set("\\t", '\t');
    escape_character_of_set("\\0", '\0');
    escape_character_of_set("\\\'", '\'');
    escape_character_of_set("\\\"", '\"');
    escape_character_of_set("\\\\", '\\');
}

static size_t strcnt(char *line, char target) {
    size_t count = 0;
    for (char alpha = *line; alpha; alpha = *(++line))
        if (alpha == target)
            count++;

    return count;
}

tokenization_status_t token_literal_number_get_status(char *line) {
    size_t dots_count = strcnt(line, '.');
    if (dots_count > 1)
        return incorrect;

    for (char alpha = *line; alpha; alpha = *(++line))
        if (!(isdigit(alpha) || alpha == '.'))
            return incorrect;

    return correct;
}

token_literal_data_t token_literal_number_get_data_from(char *line) {
    size_t dots_count = strcnt(line, '.');
    assert(dots_count <= 1);

    char *buffer = malloc(strlen(line));
    strcpy(buffer, line);

    token_literal_data_t data = {
        .kind = dots_count == 0 ? int_ : float_,
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
        dict_get_cmp(escape_character_of, escape_KV_t , &buffer[index - 2], escaped, strcmp);
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
        dict_contains_value(escape_character_of, escape_KV_t, alpha, is_contains);
        if (!is_contains) {
            buffer[index++] = alpha;
            continue;
        }

        char *key;
        dict_get_key(escape_character_of, escape_KV_t, alpha, key);
        strcpy(&buffer[index], key);
        index += strlen(key);
    }
}

token_literal_data_t token_literal_str_or_char_try_get_data_from(char *line) {
    size_t length = strlen(line);
    assert(length > 1);
    assert(line[0] == line[length - 1]);
    assert(strcnt("'\"", line[0]) != 0);

    token_literal_kind_t kind = line[0] == '"' ? str : char_;

    length -= 2;
    char buffer[length + 1] = {};
    strncpy(buffer, line + 1, length);

    char raw_escaped[length + 1] = {};
    escape_str(buffer, raw_escaped);

    length = strlen(raw_escaped);
    char *escaped = malloc(length + 1);
    strcpy(escaped, raw_escaped);

    assert(kind != char_ || length == 1);
    token_literal_data_t data = {
        .kind = kind,
        .line = escaped
    };
    return data;
}

void write_token_literal_data(token_literal_data_t data, char *buffer) {
    char *type_;
    switch (data.kind) {
        case int_:
            type_ = "int";
            break;
        case float_:
            type_ = "float";
            break;
        case char_:
            type_ = "char";
            break;
        case str:
            type_ = "str";
            break;
        default:
            assert(0);
    }
    strcpy(buffer, type_);
    strcpy(buffer + strlen(buffer), ": ");

    if (data.kind == float_ || data.kind == int_) {
        strcpy(buffer + strlen(buffer), data.line);
        return;
    }

    char quote = data.kind == str ? '"' : '\'';
    buffer[strlen(buffer)] = quote;
    unescape_str(data.line, buffer + strlen(buffer));
    buffer[strlen(buffer)] = quote;
}
