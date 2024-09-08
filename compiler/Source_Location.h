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

void Source_Location__error(Source_Location *self, String *message);

void Source_Location__warning(Source_Location *self, String *message);

Writer *pWriter__write__location(Writer *self, Source_Location *location);

#endif
