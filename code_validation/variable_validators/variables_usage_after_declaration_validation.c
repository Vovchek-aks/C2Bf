void variables_usage_after_declaration_expression_push_observer(expression_t *expression) {
    if (expression->kind != expression_kind_name)
        return;

    if (get_variable_type(expression->data.as_name.token->name))
        return;

    display_validation_error(expression, "Variable was not declared.");
}

void variables_usage_after_declaration_statement_push_observer(statement_t *statement) {
    if (statement->kind != statement_kind_variable_declaration)
        return;

    if (!get_variable_type(statement->data.as_variable_declaration.name->name))
        return;

    display_validation_error(statement, "Variable has been already declared above.");
}