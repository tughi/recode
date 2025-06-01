#ifndef __SOURCE_H__
#define __SOURCE_H__

#include "String.h"

typedef struct Source {
    char *content;
    String *file_path;
    size_t file_size;
} Source;

Source *Source__create(String *file_path);

#endif
