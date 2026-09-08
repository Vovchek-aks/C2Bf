#ifndef PARSER_TOKENS_SEPARATOR
#include "../data_structures.h"

#define PARSER_TOKENS_SEPARATOR(function_name, list_t, target_t, find, parse, error_message)                           \
    bool function_name(target_t target,                                                                                \
                       tokens_t tokens,                                                                                \
                       list_t *parts,                                                                                  \
                       bool is_strict,                                                                                 \
                       bool is_end_separator_allowed) {                                                                \
        return CONCAT(specifying_, function_name)(target, tokens, parts, is_strict, is_end_separator_allowed, false);  \
    }                                                                                                                  \
                                                                                                                       \
    bool CONCAT(specifying_, function_name)(target_t target,                                                           \
                              tokens_t tokens,                                                                         \
                              list_t *parts,                                                                           \
                              bool is_strict,                                                                          \
                              bool is_end_separator_allowed,                                                           \
                              bool is_at_least_one_split_required) {                                                   \
        if ((!is_end_separator_allowed) && find(tokens_from(&list_last(tokens)), target, chop_direction_front))        \
            return false;                                                                                              \
        tokens_t original = tokens;                                                                                    \
        tokens_t accumulator = {};                                                                                     \
        while (tokens.count > 0) {                                                                                     \
            token_t *separator = find(tokens, target, chop_direction_front);                                           \
            tokens_t part = separator ? split_by(separator, &tokens) : absorb(&tokens);                                \
            combine(&accumulator, part);                                                                               \
                                                                                                                       \
            if (accumulator.count == original.count && is_at_least_one_split_required)                                 \
                return false;                                                                                          \
                                                                                                                       \
            typeof(*parts->data) parsed = parse(accumulator, false);                                                   \
            if (parsed) {                                                                                              \
                list_push(*parts, parsed);                                                                             \
                accumulator.count = 0;                                                                                 \
                accumulator.data = NULL;                                                                               \
            }                                                                                                          \
        }                                                                                                              \
                                                                                                                       \
        bool is_ok = accumulator.count == 0;                                                                           \
        if (is_strict && !is_ok)                                                                                       \
            display_parsing_error(accumulator, error_message);                                                         \
                                                                                                                       \
        return is_ok;                                                                                                  \
    }                                                                                                                  \

#endif
