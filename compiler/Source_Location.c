#include "Source_Location.h"
#include "File.h"

Source_Location Source_Location__merge(Source_Location self, Source_Location other) {
    uint16_t start_line;
    uint16_t start_column;
    if (self.start_line < other.start_line) {
        start_line = self.start_line;
        start_column = self.start_column;
    } else if (self.start_line > other.start_line) {
        start_line = other.start_line;
        start_column = other.start_column;
    } else {
        start_line = self.start_line;
        start_column = self.start_column < other.start_column ? self.start_column : other.start_column;
    }
    uint16_t end_line;
    uint16_t end_column;
    if (self.end_line > other.end_line) {
        end_line = self.end_line;
        end_column = self.end_column;
    } else if (self.end_line < other.end_line) {
        end_line = other.end_line;
        end_column = other.end_column;
    } else {
        end_line = self.end_line;
        end_column = self.end_column > other.end_column ? self.end_column : other.end_column;
    }
    return (Source_Location){
        .source = self.source,
        .start_line = start_line,
        .start_column = start_column,
        .end_line = end_line,
        .end_column = end_column,
    };
}

bool Source_Location__equals(Source_Location self, Source_Location other) {
    return self.source == other.source && self.start_line == other.start_line && self.start_column == other.start_column && self.end_line == other.end_line && self.end_column == other.end_column;
}

Writer *pWriter__write__location_start(Writer *writer, Source_Location location) {
    pWriter__write__string(writer, location.source->file_path);
    pWriter__write__char(writer, ':');
    pWriter__write__uint64(writer, location.start_line);
    pWriter__write__char(writer, ':');
    pWriter__write__uint64(writer, location.start_column);
    return writer;
}

Writer *pWriter__write__location(Writer *writer, Source_Location location) {
    pWriter__write__location_start(writer, location);
    if (location.start_line == location.end_line && location.start_column < location.end_column) {
        pWriter__write__char(writer, '-');
        pWriter__write__uint64(writer, location.end_column);
    }
    return writer;
}

Writer *pWriter__begin_location_message(Writer *writer, Source_Location location, Writer_Style style) {
    pWriter__write__location(writer, location);
    pWriter__write__cstring(writer, ": ");
    pWriter__style(writer, style);
    return writer;
}

Writer *pWriter__begin_location_start_message(Writer *writer, Source_Location location, Writer_Style style) {
    pWriter__write__location_start(writer, location);
    pWriter__write__cstring(writer, ": ");
    pWriter__style(writer, style);
    return writer;
}

Writer *pWriter__end_location_message(Writer *writer) {
    pWriter__style(writer, WRITER_STYLE__DEFAULT);
    pWriter__end_line(writer);
    return writer;
}
