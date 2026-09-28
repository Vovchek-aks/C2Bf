static size_t cycle_flow_validator_cycles_deepness = 0;

LIST(statement_kind_t) cycles;
LIST(statement_kind_t) cycle_control_flow_statements;

void init_cycle_flow_validator() {
    list_alloc(cycles);
    list_push(cycles, statement_kind_while);
    list_push(cycles, statement_kind_do_while);
    list_push(cycles, statement_kind_for);
    list_alloc(cycle_control_flow_statements);
    list_push(cycle_control_flow_statements, statement_kind_continue);
    list_push(cycle_control_flow_statements, statement_kind_break);
}

void cycle_flow_push_observer(statement_t *statement) {
    if (list_contains(cycles, statement->kind)) {
        cycle_flow_validator_cycles_deepness++;
        return;
    }

    if (list_contains(cycle_control_flow_statements, statement->kind)
        && cycle_flow_validator_cycles_deepness == 0)
        display_validation_error(statement, "Break and continue cannot appear outside of cycle.");
}

void cycle_flow_pull_observer(statement_t *statement) {
    if (list_contains(cycles, statement->kind))
        cycle_flow_validator_cycles_deepness--;
}
