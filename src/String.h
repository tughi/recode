#pragma once

#include <string.h>

typedef struct {
    const char *content;
    size_t length;
} String;

#define STRING(s) (int)(s).length, (s).content

static inline String string_from(const char *source) {
    String string = {source, strlen(source)};
    return string;
}

static inline int string_ends_with(String string, String suffix) {
    return string.length >= suffix.length && memcmp(string.content + string.length - suffix.length, suffix.content, suffix.length) == 0;
}

static inline int string_equals(String a, String b) {
    return a.length == b.length && memcmp(a.content, b.content, a.length) == 0;
}

static inline int string_equals_cstr(String string, const char *literal) {
    size_t length = strlen(literal);
    return string.length == length && memcmp(string.content, literal, length) == 0;
}
