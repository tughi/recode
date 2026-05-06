#pragma once

#include <stddef.h>

typedef struct Source_Location {
    String source;
    size_t line;
    size_t column;
} Source_Location;
