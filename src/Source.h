#pragma once

#include "String.h"

typedef struct Source {
    String path;
    String content;
} Source;

Source load_source(String path);
Source load_source_from_stdin(void);
