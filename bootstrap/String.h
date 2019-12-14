#ifndef __recode__string_h__
#define __recode__string_h__

struct String {
    char *data;
    int length;
    int allocated;

    String();

    String(int allocated);

    String(const char *data);

    void append(char data);

    void append(String &other);

    void append_int(int value);

    bool equals(const char *data);
};

#endif
