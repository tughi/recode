#ifndef __recode__source_h__
#define __recode__source_h__

#define TAB_SIZE 4

struct Source {
    char *data;
    int index;
    int line;
    int column;

    Source(char *data);

    char peek() { return this->data[this->index]; }

    int current_line() { return this->line; }

    int current_column() { return this->column; }

    char advance(bool (*accepts)(char));
};

#endif
