#ifndef TYPE_DATAS
#define TYPE_DATAS

typedef struct type type_t;

typedef struct {
} type_void_data_t;

typedef struct {
    bool is_signed;
} type_int_data_t;

typedef struct {
    type_t *element;
} type_array_data_t;

typedef union {
    type_void_data_t as_void;
    type_int_data_t as_int;
    type_array_data_t as_array;
} type_data_t;

#endif