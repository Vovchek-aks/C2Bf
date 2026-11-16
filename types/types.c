#pragma ide diagnostic ignored "modernize-use-nullptr"
#pragma ide diagnostic ignored "misc-no-recursion"
#pragma ide diagnostic ignored "cert-err34-c"

#include "types.h"
#include "../code_validation/variable_validators/variables_filler.h"

typedef struct {
    type_t *element;
    size_t length;
} array_type_key_t;

#define CMP_ARRAY_TYPE_KEY(left, right) (((left).element == (right).element && (left).length == (right).length) ? 0 : 1)

static DICT(char *, type_t *) named_types;
static DICT(array_type_key_t, type_t *) array_types;
static LIST(type_t) types;

static void add_builtin_type(char *name, type_kind_t kind, type_data_t data, size_t bytes) {
    type_t type = {kind, data, bytes};
    list_push(types, type);
    dict_set_cmp(named_types, name, &list_last(types), strcmp);
}

void init_types() {
    dict_alloc(named_types);
    dict_alloc(array_types);
    list_alloc(types);

    add_builtin_type("void", type_kind_void, (type_data_t) {}, 0);
    for (uint8_t bytes = 1; bytes <= 8; bytes *= 2) {
        char name[10] = {};
        sprintf(name, "uint%d_t", bytes * 8);
        add_builtin_type(strdup(name), type_kind_int, (type_data_t) {.as_int={false}}, bytes);
        add_builtin_type(strdup(name + 1), type_kind_int, (type_data_t) {.as_int={true}}, bytes);
    }
    dict_set_cmp(named_types, "bool", get_type_named("uint8_t"), strcmp);
    dict_set_cmp(named_types, "char", get_type_named("int8_t"), strcmp);
}

type_t *get_type_named(char *name) {
    return dict_get_cmp(named_types, name, NULL, strcmp);
}

type_t *get_type_from_parsed(parsed_type_t *parsed_type) {
    switch (parsed_type->kind) {
        case parsed_type_kind_name:
            return get_type_named(parsed_type->data.as_name.name);
        case parsed_type_kind_array:
            parsed_type_array_data_t data = parsed_type->data.as_array;
            assert(data.size);
            assert(data.size->kind == expression_kind_literal);
            assert(data.size->data.as_literal.token->kind == token_literal_kind_int);
            size_t length = get_token_literal_value_as_int(*data.size->data.as_literal.token);

            type_t *element = get_type_from_parsed(data.element);
            array_type_key_t key = {element, length};
            type_t *type = dict_get_cmp(array_types, key, NULL, CMP_ARRAY_TYPE_KEY);
            if (type)
                return type;

            type_t new_type = {
                    type_kind_array,
                    {
                            .as_array = {
                                    .element = element
                            }
                    },
                    element->bytes * length
            };
            list_push(types, new_type);
            dict_set_cmp(array_types, key, &list_last(types), CMP_ARRAY_TYPE_KEY);
            return &list_last(types);
    }
    abort();
}

static type_t *get_str_type(char *line) {
    parsed_type_t element = {
            .kind = parsed_type_kind_name,
            .data = {
                    .as_name = {"char"}
            }
    };
    fake_tokens_new(1);
    char buffer[10] = {};
    sprintf(buffer, "%lld", strlen(line));
    fake_tokens_append_token_literal(token_literal_kind_int, strdup(buffer));
    expression_t *size = parse_expression(list_view(fake_tokens_current), true);
    parsed_type_t parsed_type = {
            .kind = parsed_type_kind_array,
            .data = {
                    .as_array = {
                            .element = &element,
                            .size = size
                    }
            }
    };
    type_t *type = get_type_from_parsed(&parsed_type);
    fake_tokens_remove_last_list();
    return type;
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

            if (data->kind == token_literal_kind_char)
                return get_type_named("char");

            if (data->kind == token_literal_kind_str)
                return get_str_type(data->line);

            assert(data->kind == token_literal_kind_int);

            bool is_signed = data->line[0] == '-';
            uint8_t bytes = get_bytes_count_for(data->line, is_signed);

            dict_for(named_types, pair) {
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

        case expression_kind_type_conversion:
            return get_type_from_parsed(expression->data.as_type_conversion.type);

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
