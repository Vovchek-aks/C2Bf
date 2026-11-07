#pragma ide diagnostic ignored "modernize-use-nullptr"


void assignment_types_checker_push_observer(statement_t *statement) {
    if (statement->kind != statement_kind_assignment)
        return;

    type_t *left = get_type_of(statement->data.as_assignment.left);
    if (!left)
        display_validation_error(statement->data.as_assignment.left, "Cannot identify type.");

    type_t *right = get_type_of(statement->data.as_assignment.right);
    if (!right)
        display_validation_error(statement->data.as_assignment.right, "Cannot identify type.");

    if (!is_able_to_assign(left, right))
        display_validation_error(statement, "Incompatible types.");
}

void declaration_types_checker_push_observer(statement_t *statement) {
    if (statement->kind != statement_kind_variable_declaration)
        return;

    if (!statement->data.as_variable_declaration.value)
        return;

    type_t *left = get_type_from_parsed(statement->data.as_variable_declaration.type);
    if (!left)
        display_validation_error(statement->data.as_assignment.left, "Cannot identify type.");
    
    type_t *right = get_type_of(statement->data.as_variable_declaration.value);
    if (!right)
        display_validation_error(statement->data.as_assignment.right, "Cannot identify type.");

    if (!is_able_to_assign(left, right))
        display_validation_error(statement, "Incompatible types.");
}
