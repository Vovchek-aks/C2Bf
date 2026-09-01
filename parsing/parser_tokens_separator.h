#ifndef PARSER_TOKENS_SEPARATOR

#define PARSER_TOKENS_SEPARATOR(function_name, stuffy_function_name, list_t, target_t, find, parse)                    \
    bool function_name(target_t target, tokens_t tokens, list_t *parts) {                                              \
        return stuffy_function_name(target, tokens, parts, false);                                                     \
    }                                                                                                                  \
                                                                                                                       \
    bool stuffy_function_name(target_t target,                                                                         \
                              tokens_t tokens,                                                                         \
                              list_t *parts,                                                                           \
                              bool require_at_least_one_split) {                                                       \
        tokens_t original = tokens;                                                                                    \
        tokens_t accumulator = {};                                                                                     \
        while (tokens.count > 0) {                                                                                     \
            token_t *separator = find(tokens, target, chop_direction_front);                                           \
            tokens_t part = separator ? split_by(separator, &tokens) : absorb(&tokens);                                \
            combine(&accumulator, part);                                                                               \
                                                                                                                       \
            if (accumulator.count == original.count && require_at_least_one_split)                                     \
                return false;                                                                                          \
                                                                                                                       \
            typeof(*parts->data) parsed = parse(accumulator);                                                          \
            if (parsed) {                                                                                              \
                list_push(*parts, parsed);                                                                             \
                accumulator.count = 0;                                                                                 \
                accumulator.data = NULL;                                                                               \
            }                                                                                                          \
        }                                                                                                              \
                                                                                                                       \
        return accumulator.count == 0;                                                                                 \
    }                                                                                                                  \

#endif