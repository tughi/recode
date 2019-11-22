#include "String.h"

#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 16

String::String() : String(DEFAULT_SIZE) {}

String::String(int size) {
    this->data = (char *)malloc(size);
    this->data[0] = 0;
    this->length = 0;
    this->size = size;
}

String::String(const char *data) {
    auto data_length = strlen(data);
    this->data = (char *)malloc(data_length + 1);
    strncpy(this->data, data, data_length);
    this->data[data_length] = 0;
    this->length = data_length;
    this->size = data_length + 1;
}

void String::append(char c) {
    if (this->length == this->size - 1) {
        this->size += DEFAULT_SIZE;
        this->data = (char *)realloc(this->data, this->size);
    }
    this->data[this->length] = c;
    this->length += 1;
    this->data[this->length] = 0;
}

bool String::equals(const char *data) {
    return strcmp(this->data, data) == 0;
}