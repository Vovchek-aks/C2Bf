bool is_variable_defined(char *name) {
    variables_tree_t *scope = variables_tree;
    while (scope) {
        if (dict_contains_cmp(scope->type_of, name, strcmp))
            return true;
        scope = scope->parent;
    }
    return false;
}

void variables_usage_after_declaration_expression_push_observer(expression_t *expression) {
    if (expression->kind != expression_kind_name)
        return;

    if (is_variable_defined(expression->data.as_name.token->name))
        return;

    display_validation_error(expression, "Variable was not declared.");
}

void variables_usage_after_declaration_statement_push_observer(statement_t *statement) {
    if (statement->kind != statement_kind_variable_declaration)
        return;

    if (!is_variable_defined(statement->data.as_variable_declaration.name->name))
        return;

    display_validation_error(statement, "Variable has been already declared above.");
}