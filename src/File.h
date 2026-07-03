#pragma once

#include "String.h"
#include <stddef.h>

typedef struct File {
    String path;
    String content;
    String *lines;
    size_t lines_size;
} File;

File load_file(String path);
File load_file_from_stdin(void);
