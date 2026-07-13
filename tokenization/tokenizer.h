#ifndef TOKENIZER
#define TOKENIZER

typedef enum {
    correct,
    incorrect,
    can_become_correct
} tokenization_status_t;

typedef tokenization_status_t (*tokenizer_t)(char *line);

#endif
