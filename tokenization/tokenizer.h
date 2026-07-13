#ifndef TOKENIZER
#define TOKENIZER

typedef enum {
    correct,
    can_become_correct,
    incorrect,
    tokenization_statuses_count
} tokenization_status_t;

typedef tokenization_status_t (*tokenizer_t)(char *line);

#endif
