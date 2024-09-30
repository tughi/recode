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

Writer *pWriter__write__location(Writer *writer, Source_Location *location) {
    pWriter__write__string(writer, location->source->file_path);
    pWriter__write__char(writer, ':');
    pWriter__write__uint64(writer, location->line);
    pWriter__write__char(writer, ':');
    pWriter__write__uint64(writer, location->column);
    return writer;
}

Writer *pWriter__begin_location_message(Writer *writer, Source_Location *location, Writer_Style style) {
    pWriter__write__location(writer, location);
    pWriter__write__cstring(writer, ": ");
    pWriter__style(writer, style);
    return writer;
}

Writer *pWriter__end_location_message(Writer *writer) {
    pWriter__style(writer, WRITER_STYLE__DEFAULT);
    pWriter__end_line(writer);
    return writer;
}
