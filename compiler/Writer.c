/* Copyright (C) 2024 Stefan Selariu */

#include "Writer.h"

Writer *create_writer(void *object, void (*write_char)(void *object, char c)) {
    Writer *writer = malloc(sizeof(Writer));
    writer->object = object;
    writer->write_char = write_char;
    return writer;
}

void pWriter__destroy(Writer *writer) {
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

Writer *pWriter__write__u64(Writer *writer, uint64_t value) {
    char buffer[21];
    sprintf(buffer, "%lu", value);
    return pWriter__write__cstring(writer, buffer);
}

Writer *pWriter__end_line(Writer *writer) {
    writer->write_char(writer->object, '\n');
    return writer;
}
