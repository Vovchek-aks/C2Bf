#include <assert.h>
#include <string.h>
#include "../data_structures/data_structures.h"

#ifndef TOKEN_DICT_MACRO
#define TOKEN_DICT_MACRO

#define TOKEN_DICT(key_t, data_t, KV_t, dict_t, dict_name, get_status_name, get_data_name, write_data_name)            \
    typedef DICT(KV_t) dict_t;                                                                                         \
                                                                                                                       \
    static dict_t dict_name;                                                                                           \
                                                                                                                       \
    tokenization_status_t get_status_name(char *line) {                                                                \
        dict_for(dict_name, KV_t, item) {                                                                              \
            size_t len_line = strlen(line);                                                                            \
                                                                                                                       \
            if (len_line > strlen(item.value))                                                                         \
                continue;                                                                                              \
                                                                                                                       \
            if (strcmp(line, item.value) == 0)                                                                         \
                return correct;                                                                                        \
                                                                                                                       \
            if (strncmp(line, item.value, len_line) == 0)                                                              \
                return can_become_correct;                                                                             \
        }                                                                                                              \
        return incorrect;                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    data_t get_data_name(char *line) {                                                                                 \
        key_t name;                                                                                                    \
        dict_get_key_cmp(dict_name, KV_t, line, name, strcmp);                                                         \
                                                                                                                       \
        return (data_t) {                                                                                              \
                .name = name                                                                                           \
        };                                                                                                             \
    }                                                                                                                  \
                                                                                                                       \
    void write_data_name(data_t data, char *buffer) {                                                                  \
        char *line = NULL;                                                                                             \
        dict_get(dict_name, KV_t, data.name, line);                                                                    \
        assert(line != NULL);                                                                                          \
                                                                                                                       \
        strcpy(buffer, line);                                                                                          \
    }

#endif