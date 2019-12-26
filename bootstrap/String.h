#ifndef __recode__string_h__
#define __recode__string_h__

typedef struct String {
    char *data;
    int length;
    int allocated;
} String;

String *string__create_empty(int allocated);

String *string__create(const char *data);

void string__append_char(String *self, char data);

void string__append_chars(String *self, char *data, int data_length);

void string__append_string(String *self, String *other);

void string__append_int(String *self, int value);

int string__equals(String *self, const char *data);

#endif
