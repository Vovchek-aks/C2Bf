#pragma ide diagnostic ignored "modernize-use-nullptr"

#include "../types/types.h"

static DICT(char *, type_t *) types;
static LIST(type_t) builtin_types;

type_t *get_type_named(char *name) {
    return dict_get_cmp(types, name, NULL, strcmp);
}

static void add_builtin_type(char *name, type_kind_t kind, type_data_t data, size_t bytes) {
    type_t type = {kind, data, bytes};
    list_push(builtin_types, type);
    dict_set_cmp(types, name, &list_last(builtin_types), strcmp);
}

void init_types_validation() {
    dict_alloc(types);
    list_alloc(builtin_types);

    add_builtin_type("void", type_kind_void, (type_data_t) {}, 0);
    for (int bytes = 1; bytes <= 8; bytes *= 2) {
        char name[10] = {};
        sprintf(name, "uint%d_t", bytes * 8);
        add_builtin_type(name, type_kind_int, (type_data_t) {.as_int={false}}, bytes);
        add_builtin_type(name + 1, type_kind_int, (type_data_t) {.as_int={true}}, bytes);
    }
    dict_set_cmp(types, "bool", get_type_named("uint8_t"), strcmp);
}

//parsed_type_t *get_type_of(expression_t *expression) {
//    switch (expression->kind) {
//        case expression_kind_literal:
//            return dict_get(types, expression->data.as_literal.token.d)
//        default:
//            abort();
//    }
//    return NULL;
//}