#include <malloc.h>
#include <assert.h>
#include <stdint.h>

#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES

#define LIST_INITIAL_SIZE 64

#define LIST(type) struct {                                                                                            \
    type *data;                                                                                                        \
    size_t count;                                                                                                      \
    size_t capacity;                                                                                                   \
}

#define list_get_view(list) (typeof(list)) { .data = (list).data, .count = (list).count, .capacity = 0}

#define list_alloc(list) do {                                                                                          \
    typeof(*(list).data) *data = malloc(sizeof(typeof(*(list).data)) * LIST_INITIAL_SIZE);                             \
    assert(data != NULL);                                                                                              \
    (list).data = data;                                                                                                \
    (list).count = 0;                                                                                                  \
    (list).capacity = LIST_INITIAL_SIZE;                                                                               \
} while(0)

#define list_push(list, element) do {                                                                                  \
    assert((list).capacity > 0);                                                                                       \
    if ((list).count == (list).capacity) {                                                                             \
        (list).capacity *= 2;                                                                                          \
        typeof((list).data) new_data = realloc((list).data, sizeof(element) * (list).capacity);\
        assert(new_data != NULL);                                                                                      \
        (list).data = new_data;                                                                                        \
    }                                                                                                                  \
                                                                                                                       \
    (list).data[(list).count++] = element;                                                                             \
} while (0)

#define list_for(list, name)                                                                                           \
    size_t FOR_IDX = 0;                                                                                                \
    for(typeof(*(list).data) name = (list).data[FOR_IDX]; FOR_IDX < (list).count; name = (list).data[++FOR_IDX])

#define list_index(list, value, result) do {                                                                           \
    for (size_t index = 0; index < (list).count; index++)                                                              \
        if ((list).data[index] == value) {                                                                             \
            result = index;                                                                                            \
            break;                                                                                                     \
        }                                                                                                              \
} while (0)

#define DICT(TK, TV) LIST(struct {TK key; TV value;})

#define dict_alloc(dict) list_alloc(dict)

#define dict_for(dict, name) list_for(dict, name)

#define dict_get(dict, key_to_check, result) do {                                                                      \
    {dict_for((dict), item) {                                                                                          \
        if ((item).key == (key_to_check)) {                                                                            \
            (result) = item.value;                                                                                     \
            break;                                                                                                     \
        }                                                                                                              \
    }}                                                                                                                 \
} while (0)

#define dict_get_cmp(dict, key_to_check, result, cmp) do {                                                             \
    {dict_for((dict), item) {                                                                                          \
        if (cmp((item).key, (key_to_check)) == 0) {                                                                    \
            (result) = item.value;                                                                                     \
            break;                                                                                                     \
        }                                                                                                              \
    }}                                                                                                                 \
} while (0)

#define dict_get_key(dict, value_to_check, result) do {                                                                \
    {dict_for((dict), item) {                                                                                          \
        if ((item).value == (value_to_check)) {                                                                        \
            (result) = item.key;                                                                                       \
            break;                                                                                                     \
        }                                                                                                              \
    }                                                                                                                  \
    assert(FOR_IDX < (dict).count);                                                                                    \
    }                                                                                                                  \
} while (0)

#define dict_get_key_cmp(dict, value_to_check, result, cmp) do {                                                       \
    {dict_for((dict), item) {                                                                                          \
        if ((cmp)(item.value, (value_to_check)) == 0) {                                                                \
            (result) = item.key;                                                                                       \
            break;                                                                                                     \
        }                                                                                                              \
    }                                                                                                                  \
    assert(FOR_IDX < (dict).count);                                                                                    \
    }                                                                                                                  \
} while (0)

#define dict_contains(dict, key_to_check, result) do {                                                                 \
    (result) = 0;                                                                                                      \
    {dict_for((dict), item) {                                                                                          \
        if (item.key == (key_to_check)) {                                                                              \
            (result) = 1;                                                                                              \
            break;                                                                                                     \
        }                                                                                                              \
    }}                                                                                                                 \
} while (0)

#define dict_contains_cmp(dict, key_to_check, result, cmp) do {                                                        \
    (result) = 0;                                                                                                      \
    {dict_for((dict), item) {                                                                                          \
        if ((cmp)(item.key, (key_to_check)) == 0) {                                                                    \
            (result) = 1;                                                                                              \
            break;                                                                                                     \
        }                                                                                                              \
    }}                                                                                                                 \
} while (0)

#define dict_contains_value(dict, value_to_check, result) do {                                                         \
    (result) = 0;                                                                                                      \
    {dict_for((dict), item) {                                                                                          \
        if (item.value == (value_to_check)) {                                                                          \
            (result) = 1;                                                                                              \
            break;                                                                                                     \
        }                                                                                                              \
    }}                                                                                                                 \
} while (0)

#define dict_set(dict, key, value_to_set) do {                                                                         \
    uint8_t is_contains;                                                                                               \
    dict_contains((dict), (key), is_contains);                                                                         \
    if (!is_contains) {                                                                                                \
        typeof(*(dict).data) item = {(key), (value_to_set)};                                                           \
        list_push((dict), item);                                                                                       \
        break;                                                                                                         \
    }                                                                                                                  \
                                                                                                                       \
    size_t index = 0;                                                                                                  \
    typeof(&(dict).data->value) old_value = NULL;                                                                      \
    dict_get((dict), (key), *old_value);                                                                               \
    typeof(*(dict).data) item = {(key), *old_value};                                                                   \
    _dict_index((dict), item, index);                                                                                  \
    (dict).data[index].value = (value_to_set);                                                                         \
} while (0)

#define _dict_index(dict, item, result) do {                                                                           \
    for (size_t idx = 0; idx < (dict).count; idx++)                                                                    \
        if ((dict).data[idx].key == (item).key && (dict).data[idx].value == (item).value) {                            \
            (result) = idx;                                                                                            \
            break;                                                                                                     \
        }                                                                                                              \
} while (0)

#define dict_set_cmp(dict, key, value_to_set, keycmp, valcmp) do {                                                     \
    uint8_t is_contains;                                                                                               \
    dict_contains_cmp((dict), (key), is_contains, (keycmp));                                                           \
    if (!is_contains) {                                                                                                \
        typeof(*(dict).data) item = {(key), (value_to_set)};                                                           \
        list_push((dict), item);                                                                                       \
        break;                                                                                                         \
    }                                                                                                                  \
                                                                                                                       \
    size_t index = 0;                                                                                                  \
    typeof(&(dict).data->value) old_value = NULL;                                                                      \
    dict_get_cmp((dict), (key), *old_value, valcmp);                                                                   \
    typeof(*(dict).data) item = {(key), *old_value};                                                                   \
    _dict_index((dict), item, index);                                                                                  \
    (dict).data[index].value = (value_to_set);                                                                         \
} while (0)

#define _dict_index(dict, item, result) do {                                                                           \
    for (size_t idx = 0; idx < (dict).count; idx++)                                                                    \
        if ((dict).data[idx].key == (item).key && (dict).data[idx].value == (item).value) {                            \
            (result) = idx;                                                                                            \
            break;                                                                                                     \
        }                                                                                                              \
} while (0)

#endif