#include "Source.h"

Source::Source(char *data) {
    this->data = data;
    this->index = 0;
    this->line = 1;
    this->column = 1;
}

char Source::advance(bool (*accepts)(char)) {
    char current = this->data[this->index];
    if (current && (*accepts)(current)) {
        this->index += 1;
        if (current == '\n') {
            this->line += 1;
            this->column = 1;
        } else {
            this->column += 1;
        }
        return current;
    }
    return 0;
}
