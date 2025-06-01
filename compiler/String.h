#ifndef __STRING_H__
#define __STRING_H__

#include "Builtins.h"
#include "Writer.h"

typedef struct String {
    char *data;
    size_t data_size;
    size_t length;
} String;

String *String__create();

String *String__create_copy(String *other);

String *String__create_empty(size_t data_size);

String *String__create_from(char *data);

Writer *String__create_writer(String *self);

void String__clear(String *self);

void String__delete(String *self);

String *String__append_char(String *self, char ch);

String *String__append_cstring(String *self, char *s);

String *String__append_int16_t(String *self, int16_t value);

String *String__append_string(String *self, String *other);

String *String__append_zero(String *self);

bool String__ends_with_cstring(String *self, char *s);

bool String__equals_cstring(String *self, char *s);

bool String__equals_string(String *self, String *other);

Writer *pWriter__write__string(Writer *self, String *string);

#endif
