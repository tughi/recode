/* Copyright (C) 2024 Stefan Selariu */

#include "File.h"

static void file_write_char(FILE *file, char c) {
    fputc(c, file);
}

Writer *create_file_writer(FILE *file) {
    return create_writer(file, (void (*)(void *, char))file_write_char);
}

Writer *stdout_writer = NULL;
Writer *stderr_writer = NULL;

void init_file_module() {
    stdout_writer = create_file_writer(stdout);
    stderr_writer = create_file_writer(stderr);
}
