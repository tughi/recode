/* Copyright (C) 2024 Stefan Selariu */

#ifndef __WRITER_H__
#define __WRITER_H__

#include "Builtins.h"

typedef struct Writer {
    void *object;
    void (*write_char)(void *object, char c);
} Writer;

Writer *create_writer(void *object, void (*write_char)(void *object, char c));

void pWriter__destroy(Writer *self);

Writer *pWriter__write__char(Writer *self, char c);
Writer *pWriter__write__cstring(Writer *self, char *cstring);
Writer *pWriter__write__int64(Writer *self, int64_t value);
Writer *pWriter__write__uint64(Writer *self, uint64_t value);

Writer *pWriter__end_line(Writer *self);

typedef enum Writer_Style {
    WRITER_STYLE__DEFAULT,
    WRITER_STYLE__ERROR,
    WRITER_STYLE__TODO,
    WRITER_STYLE__WARNING
} Writer_Style;

Writer *pWriter__style(Writer *self, Writer_Style style);

Writer *pWriter__write__todo(Writer *self, char *file, int32_t line, char *cstring);

#endif
