/* Copyright (C) 2024 Stefan Selariu */

#include "File.h"

static void file_write_char(FILE *file, char c) {
    fputc(c, file);
}

Writer *create_file_writer(FILE *file) {
    return create_writer(file, (void (*)(void *, char))file_write_char);
}
