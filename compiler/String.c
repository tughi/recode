/* Copyright (C) 2024 Stefan Selariu */

#include "String.h"

String *create_string() {
    return create_string_with_size(16);
}

String *create_string_with_size(size_t data_size) {
    String *string = malloc(sizeof(String));
    string->data = malloc(data_size);
    string->data_size = data_size;
    string->length = 0;
    return string;
}

String *create_string_from(char *data) {
    uint64_t string_length = 0;
    {
        char *string_data = data;
        while (*string_data != 0) {
            string_data++;
            string_length++;
        }
    }
    String *string = create_string_with_size(string_length + 1);
    {
        char *string_data = data;
        while (*string_data != 0) {
            string->data[string->length++] = *string_data++;
        }
        string->data[string->length] = 0;
    }
    return string;
}

void pString__destroy(String *string) {
    free(string->data);
    free(string);
}

void pString__clear(String *string) {
    string->length = 0;
}

String *pString__append__char(String *string, char c) {
    if (string->length + 1 >= string->data_size) {
        string->data_size = string->data_size + 16;
        string->data = realloc(string->data, string->data_size);
    }
    string->data[string->length++] = c;
    return string;
}

Writer *pWriter__write__string(Writer *writer, String *string) {
    size_t index = 0;
    while (index < string->length) {
        writer->write_char(writer->object, string->data[index]);
        index++;
    }
    return writer;
}
