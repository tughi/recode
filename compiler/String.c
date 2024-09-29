/* Copyright (C) 2024 Stefan Selariu */

#include "String.h"

String *String__create_empty(size_t data_size) {
    String *string = (String *)malloc(sizeof(String));
    string->data = (char *)malloc(data_size);
    string->data_size = data_size;
    string->length = 0;
    return string;
}

String *String__create() {
    return String__create_empty(16);
}

void String__delete(String *self) {
    free((void *)self->data);
    free((void *)self);
}

String *String__append_char(String *self, char ch) {
    if (self->length >= self->data_size) {
        self->data_size = self->data_size + 16;
        self->data = (char *)realloc((void *)self->data, self->data_size);
    }
    self->data[self->length] = ch;
    self->length = self->length + 1;
    return self;
}

String *String__append_cstring(String *self, char *cstring) {
    while (*cstring) {
        String__append_char(self, *cstring);
        cstring++;
    }
    return self;
}

size_t cstring_length(char *s) {
    size_t length = 0;
    while (true) {
        uint8_t c = s[length];
        if (c == 0) {
            break;
        }
        length = length + 1;
    }
    return length;
}

String *String__create_copy(String *other) {
    String *string = String__create_empty(other->length + 1);
    String__append_string(string, other);
    return string;
}

String *String__create_from(char *data) {
    size_t string_length = cstring_length(data);
    String *string = String__create_empty(string_length + 1);
    String__append_cstring(string, data);
    return string;
}

String *String__append_int16_t(String *self, int16_t value) {
    if (value < 0) {
        String__append_char(self, '-');
        String__append_int16_t(self, -value);
    } else {
        if (value >= 10) {
            String__append_int16_t(self, value / 10);
        }
        String__append_char(self, (char)(value % 10) + '0');
    }
    return self;
}

String *String__append_string(String *self, String *other) {
    size_t index = 0;
    while (index < other->length) {
        String__append_char(self, other->data[index]);
        index = index + 1;
    }
    return self;
}

String *String__end_with_zero(String *self) {
    String__append_char(self, '\0');
    self->length = self->length - 1;
    return self;
}

bool String__equals_cstring(String *self, char *s) {
    size_t length = cstring_length(s);
    if (self->length != length) {
        return false;
    }

    size_t index = 0;
    while (index < length) {
        if (self->data[index] != s[index]) {
            return false;
        }
        index = index + 1;
    }

    return true;
}

bool String__equals_string(String *self, String *other) {
    if (self->length != other->length) {
        return false;
    }

    size_t index = 0;
    while (index < self->length) {
        if (self->data[index] != other->data[index]) {
            return false;
        }
        index = index + 1;
    }

    return true;
}

Writer *pWriter__write__string(Writer *self, String *string) {
    size_t index = 0;
    while (index < string->length) {
        self->write_char(self->object, string->data[index]);
        index = index + 1;
    }
    return self;
}
