/* Copyright (C) 2024 Stefan Selariu */

#ifndef __STRING_H__
#define __STRING_H__

#include "Builtins.h"

typedef struct String {
    char *data;
    size_t data_size;
    size_t length;
} String;

String *create_string();
String *create_string_with_size(size_t data_size);
String *create_string_from(char *data);

void delete_string(String *string);

String *string_append_char(String *string, char ch);

#endif
