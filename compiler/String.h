/* Copyright (C) 2024 Stefan Selariu */

#ifndef __STRING_H__
#define __STRING_H__

#include "Writer.h"

typedef struct String {
    char *data;
    size_t data_size;
    size_t length;
} String;

String *create_string();
String *create_string_with_size(size_t data_size);
String *create_string_from(char *data);

void pString__destroy(String *string);

void pString__clear(String *string);

String *pString__append__char(String *string, char c);

Writer *pWriter__write__string(Writer *writer, String *string);

#endif
