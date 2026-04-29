#pragma once

#include <string.h>

typedef struct {
    const char *content;
    size_t length;
} String;

static inline String string_from(const char *source) {
    String string = {source, strlen(source)};
    return string;
}

static inline int string_ends_with(String string, String suffix) {
    return string.length >= suffix.length && memcmp(string.content + string.length - suffix.length, suffix.content, suffix.length) == 0;
}
