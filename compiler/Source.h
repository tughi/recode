/* Copyright (C) 2024 Stefan Selariu */

#ifndef __SOURCE_H__
#define __SOURCE_H__

#include "Builtins.h"

typedef struct Source {
    char *content;
    char *file_path;
    size_t file_size;
} Source;

Source *create_source(char *file_path);

#endif
