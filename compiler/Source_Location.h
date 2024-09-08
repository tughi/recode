/* Copyright (C) 2024 Stefan Selariu */

#ifndef __SOURCE_LOCATION_H__
#define __SOURCE_LOCATION_H__

#include "Source.h"
#include "Writer.h"

typedef struct Source_Location {
    Source *source;
    size_t line;
    size_t column;
} Source_Location;

Source_Location *create_source_location(Source *source, size_t line, size_t column);

Writer *pWriter__write__location(Writer *writer, Source_Location *location);

#endif
