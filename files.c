#include <stdio.h>
#include <assert.h>
#include <malloc.h>

char *read_entire_file(char *filename) {
    FILE *file = fopen(filename, "rb");
    assert(file);

    fpos_t start_pos;
    assert(fgetpos(file, &start_pos) == 0);

    assert(fseek(file, 0, SEEK_END) == 0);
    fpos_t end_pos;
    assert(fgetpos(file, &end_pos) == 0);

    int64_t file_size = (int64_t)end_pos - (int64_t)start_pos;
    assert(file_size >= 0);
    assert(fsetpos(file, &start_pos) == 0);

    char *buffer = malloc(file_size + 1);
    assert(buffer);

    assert(fread(buffer, 1, file_size, file) == (size_t)file_size);
    buffer[file_size] = 0;

    fclose(file);
    return buffer;
}
