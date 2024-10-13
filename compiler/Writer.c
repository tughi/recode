/* Copyright (C) 2024 Stefan Selariu */

#include "Writer.h"

Writer *Writer__create(void *object, void (*write_char)(void *object, char c)) {
    Writer *writer = malloc(sizeof(Writer));
    writer->object = object;
    writer->write_char = write_char;
    return writer;
}

void pWriter__destroy(Writer *self) {
    free(self);
}

Writer *pWriter__write__char(Writer *self, char c) {
    self->write_char(self->object, c);
    return self;
}

Writer *pWriter__write__cstring(Writer *self, char *cstring) {
    while (*cstring) {
        self->write_char(self->object, *cstring);
        cstring++;
    }
    return self;
}

Writer *pWriter__write__int64(Writer *self, int64_t value) {
    char buffer[21];
    sprintf(buffer, "%ld", value);
    return pWriter__write__cstring(self, buffer);
}

Writer *pWriter__write__uint64(Writer *self, uint64_t value) {
    char buffer[21];
    sprintf(buffer, "%lu", value);
    return pWriter__write__cstring(self, buffer);
}

Writer *pWriter__end_line(Writer *self) {
    self->write_char(self->object, '\n');
    return self;
}

Writer *pWriter__style(Writer *self, Writer_Style style) {
    switch (style) {
    case WRITER_STYLE__DEFAULT:
        pWriter__write__cstring(self, "\033[0m");
        break;
    case WRITER_STYLE__ERROR:
        pWriter__write__cstring(self, "\033[0;91m");
        break;
    case WRITER_STYLE__WARNING:
        pWriter__write__cstring(self, "\033[0;93m");
        break;
    }
    return self;
}
