#include "File.h"

static void file_write_char(FILE *file, char c) {
    fputc(c, file);
}

static Writer *create_file_writer(FILE *file) {
    return Writer__create(file, (void (*)(void *, char))file_write_char);
}

Writer *stdout_writer = NULL;
Writer *stderr_writer = NULL;

void File__init() {
    stdout_writer = create_file_writer(stdout);
    stderr_writer = create_file_writer(stderr);
}

Writer *File__create_writer(String *file_path) {
    FILE *file = fopen(file_path->data, "w");
    if (file == NULL) {
        panic();
    }
    return create_file_writer(file);
}
