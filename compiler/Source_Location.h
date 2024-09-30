/* Copyright (C) 2024 Stefan Selariu */

#ifndef __SOURCE_LOCATION_H__
#define __SOURCE_LOCATION_H__

#include "Source.h"
#include "String.h"
#include "Writer.h"

typedef struct Source_Location {
    Source *source;
    uint16_t line;
    uint16_t column;
} Source_Location;

Source_Location *Source_Location__create(Source *source, uint16_t line, uint16_t column);

Writer *pWriter__write__location(Writer *self, Source_Location *location);

Writer *pWriter__begin_location_message(Writer *writer, Source_Location *location, Writer_Style style);

Writer *pWriter__end_location_message(Writer *writer);

#endif
