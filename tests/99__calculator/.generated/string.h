#ifndef __string_H__
#define __string_H__

#include "types.h"

#include "libc.h"

struct string_Builder *pstring_Builder__write(struct string_Builder *self, uint8_t c);

struct String pstring_Builder__build(struct string_Builder *self);

struct string_Builder string__make_string_builder();

struct string_Builder string__make_string_builder_with_data_size(uintmax_t data_size);

void pstring_Builder__write_char(struct string_Builder *self, uint8_t c);

#endif // __string_H__
