/* Copyright (C) 2024 Stefan Selariu */

#include "File.h"

static void file_write_char(FILE *file, char c) {
    fputc(c, file);
}

static Writer *File__create_writer(FILE *file) {
    return Writer__create(file, (void (*)(void *, char))file_write_char);
}

Writer *stdout_writer = NULL;
Writer *stderr_writer = NULL;

void File__init() {
    stdout_writer = File__create_writer(stdout);
    stderr_writer = File__create_writer(stderr);
}
