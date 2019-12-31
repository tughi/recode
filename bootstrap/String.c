#include "String.h"

#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 16

String *string__create_empty(int allocated) {
    String *self = malloc(sizeof(String));
    self->data = malloc(allocated < 1 ? 1 : allocated);
    self->data[0] = 0;
    self->length = 0;
    self->allocated = allocated;
    return self;
}

String *string__create(const char *data) {
    String *self = malloc(sizeof(String));
    int data_length = strlen(data);
    self->data = malloc(data_length + 1);
    strncpy(self->data, data, data_length);
    self->data[data_length] = 0;
    self->length = data_length;
    self->allocated = data_length + 1;
    return self;
}

String *string__append_char(String *self, char data) {
    if (self->length + 1 >= self->allocated) {
        self->allocated += DEFAULT_SIZE;
        self->data = (char *)realloc(self->data, self->allocated);
    }
    self->data[self->length] = data;
    self->length += 1;
    self->data[self->length] = 0;
    return self;
}

String *string__append_chars(String *self, char *data, int data_length) {
    if (self->length + data_length >= self->allocated) {
        self->allocated = self->length + data_length + 1;
        self->data = (char *)realloc(self->data, self->allocated);
    }
    for (int i = 0; i <= data_length; i++) {
        self->data[self->length + i] = data[i];
    }
    self->length += data_length;
    return self;
}

String *string__append_string(String *self, String *other) {
    string__append_chars(self, other->data, other->length);
    return self;
}

String *string__append_int(String *self, int value) {
    if (value == 0) {
        string__append_char(self, '0');
    } else if (value > 0) {
        if (value > 9) {
            string__append_int(self, value / 10);
        }
        string__append_char(self, value % 10 + '0');
    }
    return self;
}

int string__equals(String *self, const char *data) {
    return strcmp(self->data, data) == 0;
}
