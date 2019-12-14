#include "String.h"

#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 16

String::String() : String(DEFAULT_SIZE) {}

String::String(int allocated) {
    this->data = (char *)malloc(allocated);
    this->data[0] = 0;
    this->length = 0;
    this->allocated = allocated;
}

String::String(const char *data) {
    auto data_length = strlen(data);
    this->data = (char *)malloc(data_length + 1);
    strncpy(this->data, data, data_length);
    this->data[data_length] = 0;
    this->length = data_length;
    this->allocated = data_length + 1;
}

void String::append(char data) {
    if (this->length + 1 >= this->allocated) {
        this->allocated += DEFAULT_SIZE;
        this->data = (char *)realloc(this->data, this->allocated);
    }
    this->data[this->length] = data;
    this->length += 1;
    this->data[this->length] = 0;
}

void String::append(String &other) {
    if (this->length + other.length >= this->allocated) {
        this->allocated = this->length + other.length + 1;
        this->data = (char *)realloc(this->data, this->allocated);
    }
    for (int i = 0; i <= other.length; i++) {
        this->data[this->length + i] = other.data[i];
    }
    this->length += other.length;
}

void String::append_int(int value) {
    if (value > 0) {
        this->append_int(value / 10);
        this->append(value % 10 + '0');
    }
}

bool String::equals(const char *data) {
    return strcmp(this->data, data) == 0;
}
