#pragma ide diagnostic ignored "modernize-use-nullptr"

#include "types.h"
#include "../code_validation/variable_validators/variables_filler.h"

static DICT(char *, type_t *) types;
static LIST(type_t) builtin_types;

static void add_builtin_type(char *name, type_kind_t kind, type_data_t data, size_t bytes) {
    type_t type = {kind, data, bytes};
    list_push(builtin_types, type);
    dict_set_cmp(types, name, &list_last(builtin_types), strcmp);
}

void init_types() {
    dict_alloc(types);
    list_alloc(builtin_types);

    add_builtin_type("void", type_kind_void, (type_data_t) {}, 0);
    for (uint8_t bytes = 1; bytes <= 8; bytes *= 2) {
        char name[10] = {};
        sprintf(name, "uint%d_t", bytes * 8);
        add_builtin_type(strdup(name), type_kind_int, (type_data_t) {.as_int={false}}, bytes);
        add_builtin_type(strdup(name + 1), type_kind_int, (type_data_t) {.as_int={true}}, bytes);
    }
    dict_set_cmp(types, "bool", get_type_named("uint8_t"), strcmp);
}

type_t *get_type_named(char *name) {
    return dict_get_cmp(types, name, NULL, strcmp);
}

type_t *get_type_from_parsed(parsed_type_t *parsed_type) {
    assert(parsed_type->kind == parsed_type_kind_name);
    return get_type_named(parsed_type->data.as_name.name);
}

static size_t get_bytes_count_for(char *int_literal, bool is_signed) {
    uint64_t value;
    sscanf(int_literal + is_signed, "%lld", &value);

    if (is_signed) {
        if (value <= 1 << 7)
            return 1;

        if (value <= 1 << 15)
            return 2;

        if (value <= ((uint64_t) 1) << 31)
            return 4;

        return 8;
    }

    if (value < 1 << 8)
        return 1;

    if (value < 1 << 16)
        return 2;

    if (value < ((uint64_t) 1) << 32)
        return 4;

    return 8;
}

type_t *get_type_of(expression_t *expression) {
    switch (expression->kind) {
        case expression_kind_literal:
            token_literal_data_t *data = expression->data.as_literal.token;
            assert(data->kind == token_literal_kind_int);

            bool is_signed = data->line[0] == '-';
            uint8_t bytes = get_bytes_count_for(data->line, is_signed);

            dict_for(types, pair) {
                type_t *type = pair.value;
                if (type->kind != type_kind_int)
                    continue;
                type_int_data_t type_data = type->data.as_int;
                if (type_data.is_signed == is_signed
                    && type->bytes == bytes)
                    return type;
            }
            abort();

        case expression_kind_name:
            return get_variable_type(expression->data.as_name.token->name);
            break;

        default:
            return NULL;
    }
}

bool is_able_to_assign(type_t *left, type_t *right) {
    if (left == right)
        return true;

    if (left->kind != type_kind_int
        || right->kind != type_kind_int)
        return false;

    if (right->data.as_int.is_signed
        && !left->data.as_int.is_signed)
        return false;

    return left->bytes >= right->bytes;
}
