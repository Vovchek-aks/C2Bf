#pragma ide diagnostic ignored "modernize-use-nullptr"

struct variables_tree_t {
    struct variables_tree_t *parent;
    LIST(struct variables_tree_t) children;
    DICT(char *, type_t *) type_of;
};
typedef struct variables_tree_t variables_tree_t;

variables_tree_t *variables_tree;

void init_variables_filler_validator() {
    variables_tree = malloc(sizeof(variables_tree_t));
    variables_tree->parent = NULL;
    dict_alloc(variables_tree->type_of);
    list_alloc(variables_tree->children);

    type_t *temp_builtin_functions_type = get_type_named("void");
    dict_for(function_of_binary_operation, pair)
        dict_set_cmp(variables_tree->type_of, pair.value, temp_builtin_functions_type, strcmp);
    dict_for(function_of_unary_prefix, pair)
        dict_set_cmp(variables_tree->type_of, pair.value, temp_builtin_functions_type, strcmp);
    dict_for(function_of_unary_postfix, pair)
        dict_set_cmp(variables_tree->type_of, pair.value, temp_builtin_functions_type, strcmp);
}

void variables_filler_push_observer(statement_t *statement) {
    if (statement->kind != statement_kind_scope)
        return;

    variables_tree_t child = { .parent = variables_tree };
    dict_alloc(child.type_of);
    list_alloc(child.children);

    list_push(variables_tree->children, child);
    variables_tree = &list_last(variables_tree->children);
}

void variables_filler_pull_observer(statement_t *statement) {
    if (statement->kind == statement_kind_scope) {
        variables_tree = variables_tree->parent;
        return;
    }

    if (statement->kind != statement_kind_variable_declaration)
        return;

    statement_variable_declaration_data_t data = statement->data.as_variable_declaration;
    dict_set_cmp(variables_tree->type_of, data.name->name, data.type, strcmp);
}
