#include "code_validation.h"
#include "cycle_flow_validator.c"
#include "types_validator.c"
#include "variable_validators/variables_filler.c"
#include "variable_validators/variables_usage_after_declaration_validation.c"
#pragma ide diagnostic ignored "misc-no-recursion"

typedef void (*statement_observer)(statement_t *statement);
typedef void (*expression_observer)(expression_t *expression);

LIST(statement_observer) statement_push_observers;
LIST(statement_observer) statement_pull_observers;
LIST(expression_observer) expression_push_observers;
LIST(expression_observer) expression_pull_observers;

void init_program_validation() {
    list_alloc(statement_push_observers);
    list_alloc(statement_pull_observers);
    list_alloc(expression_push_observers);
    list_alloc(expression_pull_observers);

    init_cycle_flow_validator();
    list_push(statement_push_observers, cycle_flow_push_observer);
    list_push(statement_pull_observers, cycle_flow_pull_observer);

    init_types_validation();

    init_variables_filler_validator();
    list_push(statement_push_observers, variables_filler_push_observer);
    list_push(statement_pull_observers, variables_filler_pull_observer);

    list_push(expression_push_observers, variables_usage_after_declaration_expression_push_observer);
    list_push(statement_push_observers, variables_usage_after_declaration_statement_push_observer);
}

static void try_process_expression(expression_t *expression);

static void try_process_statement(statement_t *statement) {
    if (!statement)
        return;

    list_for(statement_push_observers, observe)
        observe(statement);

    switch (statement->kind) {
        case statement_kind_scope:
            list_for(statement->data.as_scope.statements, inner_statement)
                try_process_statement(inner_statement);
            break;
        case statement_kind_if:
            try_process_expression(statement->data.as_if.condition);
            try_process_statement(statement->data.as_if.true_branch);
            try_process_statement(statement->data.as_if.false_branch);
            break;
        case statement_kind_while:
        case statement_kind_do_while:
            try_process_expression(statement->data.as_while.condition);
            try_process_statement(statement->data.as_while.body);
            break;
        case statement_kind_for:
            try_process_statement(statement->data.as_for.before_first);
            try_process_expression(statement->data.as_for.condition);
            try_process_statement(statement->data.as_for.body);
            try_process_statement(statement->data.as_for.after_each);
            break;
        case statement_kind_variable_declaration:
            try_process_expression(statement->data.as_variable_declaration.value);
            break;
        case statement_kind_assignment:
            try_process_expression(statement->data.as_assignment.left);
            try_process_expression(statement->data.as_assignment.right);
            break;
        default:
            break;
    }

    list_for(statement_pull_observers, observe)
        observe(statement);
}

static void try_process_expression(expression_t *expression) {
    if (!expression)
        return;

    list_for(expression_push_observers, observe)
        observe(expression);

    switch (expression->kind) {
        case expression_kind_indexing:
            try_process_expression(expression->data.as_indexing.array);
            try_process_expression(expression->data.as_indexing.index);
            break;
        case expression_kind_function_call:
            try_process_expression(expression->data.as_function_call.function);
            list_for(expression->data.as_function_call.arguments, argument)
                try_process_expression(argument);
            break;
        case expression_kind_element_access:
            try_process_expression(expression->data.as_element_access.source);
            break;
        default:
            break;
    }

    list_for(expression_pull_observers, observe)
        observe(expression);
}

void validate_program(program_t *program) {
    try_process_statement(program->main->body);
}