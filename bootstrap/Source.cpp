#include "Source.h"

Source::Source(char *data) {
    this->data = data;
    this->index = 0;
    this->line = 1;
    this->column = 1;
}

char Source::advance(bool (*accepts)(char)) {
    char next_char = this->data[this->index];
    if (next_char && (*accepts)(next_char)) {
        this->index += 1;
        if (next_char == '\n') {
            this->line += 1;
            this->column = 1;
        } else if (next_char == '\t') {
            this->column = (this->column / TAB_SIZE + 1) * TAB_SIZE + 1;
        } else {
            this->column += 1;
        }
        return next_char;
    }
    return 0;
}
