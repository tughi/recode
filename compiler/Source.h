/* Copyright (C) 2024 Stefan Selariu */

#ifndef __SOURCE_H__
#define __SOURCE_H__

#include "String.h"

typedef struct Source {
    String *content;
    char *path;
} Source;

Source *Source__create(FILE *file, char *path);

#endif
