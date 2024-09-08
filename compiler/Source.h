/* Copyright (C) 2024 Stefan Selariu */

#ifndef __SOURCE_H__
#define __SOURCE_H__

#include "String.h"

typedef struct Source {
    char *content;
    String *file_path;
    size_t file_size;

    struct Source *next;
    struct Source *prev;
} Source;

Source *Source__create(String *file_path);

#endif
