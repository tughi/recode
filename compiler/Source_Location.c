/* Copyright (C) 2024 Stefan Selariu */

#include "Source_Location.h"
#include "File.h"

Source_Location *Source_Location__create(Source *source, uint16_t line, uint16_t column) {
    Source_Location *source_location = (Source_Location *)malloc(sizeof(Source_Location));
    source_location->source = source;
    source_location->line = line;
    source_location->column = column;
    return source_location;
}

void Source_Location__error(Source_Location *self, String *message) {
    pWriter__write__location(stderr_writer, self);
    pWriter__write__cstring(stderr_writer, ": ");
    pWriter__style(stderr_writer, WRITER_STYLE__ERROR);
    pWriter__write__string(stderr_writer, message);
    pWriter__style(stderr_writer, WRITER_STYLE__DEFAULT);
    pWriter__end_line(stderr_writer);
}

void Source_Location__warning(Source_Location *self, String *message) {
    pWriter__write__location(stderr_writer, self);
    pWriter__write__cstring(stderr_writer, ": ");
    pWriter__style(stderr_writer, WRITER_STYLE__WARNING);
    pWriter__write__string(stderr_writer, message);
    pWriter__style(stderr_writer, WRITER_STYLE__DEFAULT);
    pWriter__end_line(stderr_writer);
}

Writer *pWriter__write__location(Writer *writer, Source_Location *location) {
    pWriter__write__string(writer, location->source->file_path);
    pWriter__write__char(writer, ':');
    pWriter__write__uint64(writer, location->line);
    pWriter__write__char(writer, ':');
    pWriter__write__uint64(writer, location->column);
    return writer;
}
