#ifndef TOKEN_DICT_MACRO
#define TOKEN_DICT_MACRO

#include <assert.h>
#include <string.h>
#include "../data_structures.h"
#include "../string_helper/string_helper.h"

#define TOKEN_DICT(data_t, TK, TV, dict_t, dict_name, get_status_name, get_data_name)                                  \
    typedef DICT(TK, TV) dict_t;                                                                                       \
                                                                                                                       \
    static dict_t dict_name;                                                                                           \
                                                                                                                       \
    tokenization_status_t get_status_name(char *line) {                                                                \
        dict_for(dict_name, item) {                                                                                    \
            size_t len_line = strlen(line);                                                                            \
                                                                                                                       \
            if (len_line > strlen(item.value))                                                                         \
                continue;                                                                                              \
                                                                                                                       \
            if (strcmp(line, item.value) == 0)                                                                         \
                return tokenization_status_correct;                                                                    \
                                                                                                                       \
            if (strncmp(line, item.value, len_line) == 0)                                                              \
                return tokenization_status_can_become_correct;                                                         \
        }                                                                                                              \
        return tokenization_status_incorrect;                                                                          \
    }                                                                                                                  \
                                                                                                                       \
    data_t get_data_name(char *line) {                                                                                 \
        TK name = dict_get_key_cmp(dict_name, line, strcmp);                                                           \
                                                                                                                       \
        return (data_t) {                                                                                              \
                .name = name                                                                                           \
        };                                                                                                             \
    }


#define TOKEN_DICT_WITH_WRITE(data_t, TK, TV, dict_t, dict_name, get_status_name, get_data_name, write_data_name)      \
    TOKEN_DICT(data_t, TK, TV, dict_t, dict_name, get_status_name, get_data_name)                                      \
                                                                                                                       \
    void write_data_name(data_t data, char **buffer) {                                                                 \
        char *line = dict_get(dict_name, data.name, NULL);                                                             \
        assert(line);                                                                                                  \
                                                                                                                       \
        string_extend(buffer, line);                                                                                   \
    }

#endif