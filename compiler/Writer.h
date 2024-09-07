/* Copyright (C) 2024 Stefan Selariu */

#ifndef __WRITER_H__
#define __WRITER_H__

#include "String.h"

typedef struct Writer {
    void *object;
    void (*write_char)(void *object, char c);
} Writer;

Writer *create_writer(void *object, void (*write_char)(void *object, char c));

void delete_writer(Writer *writer);

Writer *pWriter__write__char(Writer *writer, char c);
Writer *pWriter__write__cstring(Writer *writer, char *cstring);
Writer *pWriter__write__string(Writer *writer, String *string);

Writer *pWriter__end_line(Writer *writer);

#endif
