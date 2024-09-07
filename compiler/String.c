/* Copyright (C) 2024 Stefan Selariu */

#include "String.h"

String *create_string() {
    return create_string_with_size(8);
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

void delete_string(String *string) {
    free(string->data);
    free(string);
}
