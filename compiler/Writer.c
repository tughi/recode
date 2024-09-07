/* Copyright (C) 2024 Stefan Selariu */

#include "Writer.h"

Writer *create_writer(void *object, void (*write_char)(void *object, char c)) {
    Writer *writer = malloc(sizeof(Writer));
    writer->object = object;
    writer->write_char = write_char;
    return writer;
}

void delete_writer(Writer *writer) {
    free(writer);
}

Writer *pWriter__write__char(Writer *writer, char c) {
    writer->write_char(writer->object, c);
    return writer;
}

Writer *pWriter__write__cstring(Writer *writer, char *cstring) {
    while (*cstring) {
        writer->write_char(writer->object, *cstring);
        cstring++;
    }
    return writer;
}

Writer *pWriter__write__string(Writer *writer, String *string) {
    char *string_data = string->data;
    while (*string_data) {
        writer->write_char(writer->object, *string_data);
        string_data++;
    }
    return writer;
}

Writer *pWriter__end_line(Writer *writer) {
    writer->write_char(writer->object, '\n');
    return writer;
}
