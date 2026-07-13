#include <malloc.h>
#include <assert.h>

#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES

#define LIST_INITIAL_SIZE 64

#define LIST(type) struct {                                                                                           \
    type *data;                                                                                                       \
    size_t count;                                                                                                     \
    size_t capacity;                                                                                                  \
}

#define list_alloc(list, type) do {                                                                                   \
    type *data = malloc(sizeof(type) * LIST_INITIAL_SIZE);                                                            \
    list.data = data;                                                                                                 \
    list.count = 0;                                                                                                   \
    list.capacity = LIST_INITIAL_SIZE;                                                                                \
} while(0)

#define list_push(list, element) do {                                                                                 \
    if (list.count == list.capacity) {                                                                                \
        list.capacity *= 2;                                                                                           \
        list.data = realloc(list.data, list.capacity);                                                                \
    }                                                                                                                 \
                                                                                                                      \
    *(list.data + list.count) = element;                                                                              \
    list.count++;                                                                                                     \
} while (0)

#define list_for(list, type, name)                                                                                    \
    size_t FOR_IDX = 0;                                                                                               \
    for(type name = list.data[FOR_IDX]; FOR_IDX < list.count; name = list.data[++FOR_IDX])

#define list_index(list, type, value, result) do {                                                                    \
    for (size_t index = 0; index < list.count; index++)                                                               \
        if (list.data[index] == value) {                                                                              \
            result = index;                                                                                           \
            break;                                                                                                    \
        }                                                                                                             \
} while (0)

#define key_value(TK, TV) struct {TK key; TV value;}

#define DICT(type) LIST(type)

#define dict_alloc(dict, type) list_alloc(dict, type)

#define dict_for(dict, type, name) list_for(dict, type, name)

#define dict_get(dict, type, key_to_check, result) do {                                                               \
    {dict_for(dict, type, item) {                                                                                     \
        if (item.key == key_to_check) {                                                                               \
            result = item.value;                                                                                      \
            break;                                                                                                    \
        }                                                                                                             \
    }}                                                                                                                \
} while (0)

#define dict_get_key(dict, type, value_to_check, result) do {                                                         \
    {dict_for(dict, type, item) {                                                                                     \
        if (item.value == value_to_check) {                                                                           \
            result = item.key;                                                                                        \
            break;                                                                                                    \
        }                                                                                                             \
    }                                                                                                                 \
    assert(FOR_IDX < dict.count);                                                                                                        \
    }                                                                                                                 \
} while (0)

#define dict_get_key_cmp(dict, type, value_to_check, result, cmp) do {                                                         \
    {dict_for(dict, type, item) {                                                                                     \
        if (cmp(item.value, value_to_check) == 0) {                                                                           \
            result = item.key;                                                                                        \
            break;                                                                                                    \
        }                                                                                                             \
    }                                                                                                                 \
    assert(FOR_IDX < dict.count);                                                                                                        \
    }                                                                                                                 \
} while (0)

#define dict_contains(dict, type, key_to_check, result) do {                                                          \
    result = 0;                                                                                                       \
    {dict_for(dict, type, item) {                                                                                     \
        if (item.key == key_to_check) {                                                                               \
            result = 1;                                                                                               \
            break;                                                                                                    \
        }                                                                                                             \
    }}                                                                                                                \
} while (0)

#define dict_contains_value(dict, type, value_to_check, result) do {                                                          \
    result = 0;                                                                                                       \
    {dict_for(dict, type, item) {                                                                                     \
        if (item.value == value_to_check) {                                                                               \
            result = 1;                                                                                               \
            break;                                                                                                    \
        }                                                                                                             \
    }}                                                                                                                \
} while (0)

#define dict_set(dict, type, TV, key, value_to_set) do {                                                              \
    uint8_t is_contains;                                                                                                  \
    dict_contains(dict, type, key, is_contains);                                                                      \
    if (!is_contains) {                                                                                               \
        type item = {key, value_to_set};                                                                              \
        list_push(dict, item);                                                                                        \
        break;                                                                                                        \
    }                                                                                                                 \
                                                                                                                      \
    size_t index;                                                                                                     \
    TV old_value;                                                                                                     \
    dict_get(dict, type, key, old_value);                                                                             \
    type item = {key, old_value};                                                                                     \
    _dict_index(dict, type, item, index);                                                                             \
    dict.data[index].value = value_to_set;                                                                            \
} while (0)

#define _dict_index(dict, type, item, result) do {                                                                    \
    for (size_t idx = 0; idx < dict.count; idx++)                                                                     \
        if (dict.data[idx].key == item.key && dict.data[idx].value == item.value) {                                   \
            result = idx;                                                                                             \
            break;                                                                                                    \
        }                                                                                                             \
} while (0)

#endif