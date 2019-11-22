#ifndef __recode__string_h__
#define __recode__string_h__

struct String {
    char *data;
    int length;
    int size;

    String();

    String(int size);

    String(const char *data);

    void append(char c);

    bool equals(const char *data);
};

#endif
