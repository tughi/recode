#pragma once

#include <string.h>

typedef struct {
    const char *content;
    size_t length;
} String;

static inline String string_from(const char *s) {
    String str = {s, strlen(s)};
    return str;
}

static inline int string_ends_with(String s, String suffix) {
    return s.length >= suffix.length && memcmp(s.content + s.length - suffix.length, suffix.content, suffix.length) == 0;
}
