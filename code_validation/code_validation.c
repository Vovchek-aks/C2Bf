#include "code_validation.h"
#include "cycle_flow_validator.c"

typedef void (*on_ast_stack_was_changed)(statement_t *statement);

LIST(on_ast_stack_was_changed) push_observers;
LIST(on_ast_stack_was_changed) pull_observers;

void init_program_validation() {
    list_alloc(push_observers);
    list_alloc(pull_observers);

    init_cycle_flow_validator();
    list_push(push_observers, cycle_flow_push_observer);
    list_push(pull_observers, cycle_flow_pull_observer);
}

static void try_process_statement(statement_t *statement) {
    if (!statement)
        return;

    list_for(push_observers, observe)
        observe(statement);

    switch (statement->kind) {
        case statement_kind_scope:
            list_for(statement->data.as_scope.statements, inner_statement)try_process_statement(inner_statement);
            break;
        case statement_kind_if:
            try_process_statement(statement->data.as_if.true_branch);
            try_process_statement(statement->data.as_if.false_branch);
            break;
        case statement_kind_while:
        case statement_kind_do_while:
            try_process_statement(statement->data.as_while.body);
            break;
        case statement_kind_for:
            try_process_statement(statement->data.as_for.before_first);
            try_process_statement(statement->data.as_for.body);
            try_process_statement(statement->data.as_for.after_each);
            break;
        default:
            break;
    }

    list_for(pull_observers, observe)
        observe(statement);
}

void validate_program(program_t *program) {
    try_process_statement(program->main->body);
}