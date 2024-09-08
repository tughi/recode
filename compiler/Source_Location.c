/* Copyright (C) 2024 Stefan Selariu */

#include "Source_Location.h"

Source_Location *create_source_location(Source *source, size_t line, size_t column) {
    Source_Location *location = malloc(sizeof(Source_Location));
    location->source = source;
    location->line = line;
    location->column = column;
    return location;
}

Writer *pWriter__write__location(Writer *writer, Source_Location *location) {
    pWriter__write__cstring(writer, location->source->file_path);
    pWriter__write__char(writer, ':');
    pWriter__write__u64(writer, location->line);
    pWriter__write__char(writer, ':');
    pWriter__write__u64(writer, location->column);
    return writer;
}
