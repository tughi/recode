#ifndef __SOURCE_LOCATION_H__
#define __SOURCE_LOCATION_H__

#include "Source.h"
#include "String.h"
#include "Writer.h"

typedef struct Source_Location {
    Source *source;
    uint16_t start_line;
    uint16_t start_column;
    uint16_t end_line;
    uint16_t end_column;
} Source_Location;

Source_Location Source_Location__union(Source_Location self, Source_Location other);

bool Source_Location__equals(Source_Location self, Source_Location other);

Writer *pWriter__write__location(Writer *self, Source_Location location);

Writer *pWriter__begin_location_message(Writer *writer, Source_Location location, Writer_Style style);

Writer *pWriter__end_location_message(Writer *writer);

#endif
