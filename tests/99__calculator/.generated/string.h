#ifndef __string_H__
#define __string_H__

#include "builtin_types.h"

#include "libc.h"

struct string_Builder {
    uint8_t *data;
    uintmax_t data_size;
    uintmax_t length;
};

struct string_Builder *__alloc__string_Builder__(struct string_Builder value);

struct string_Builder *pstring_Builder__write__1_char(struct string_Builder *self, uint8_t c);

struct String pstring_Builder__build(struct string_Builder *self);

struct string_Builder string__make_string_builder();

struct string_Builder string__make_string_builder__0_initial_data_size(uintmax_t initial_data_size);

void pstring_Builder__write_char(struct string_Builder *self, uint8_t c);

#endif // __string_H__
