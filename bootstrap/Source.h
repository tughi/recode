#ifndef __recode__source_h__
#define __recode__source_h__

#define TAB_SIZE 4

typedef struct Source {
    char *data;
    int index;
    int line;
    int column;
} Source;

Source *source__create(char *data);

char source__peek(Source *self);

int source__current_line(Source *self);

int source__current_column(Source *self);

char source__advance(Source *self, int (*accepts)(unsigned char));

typedef struct Source_Location {
    Source *source;
    int line;
    int column;
} Source_Location;

Source_Location *source_location__create(Source *source);

#endif
