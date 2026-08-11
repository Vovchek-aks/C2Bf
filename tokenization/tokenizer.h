#ifndef TOKENIZER
#define TOKENIZER

typedef enum {
    tokenization_status_correct,
    tokenization_status_can_become_correct,
    tokenization_status_incorrect,
    tokenization_statuses_count __attribute__((unused))
} tokenization_status_t;

typedef tokenization_status_t (*tokenizer_t)(char *line);

#endif
