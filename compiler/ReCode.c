//  Copyright (C) 2023 Stefan Selariu

// Types

typedef char i8;
typedef short i16;
typedef int i32;
typedef long i64;
typedef long int isize;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;
typedef unsigned long int usize;

typedef i8 bool;
const bool true = 1;
const bool false = 0;

// LibC

typedef struct FILE File;

extern File *stdin;
extern File *stdout;
extern File *stderr;

extern i32 fgetc(File *stream);
extern i32 fputc(i32 c, File *stream);

extern void *malloc(usize size);
extern void *realloc(void *ptr, usize size);
extern void free(void *ptr);

extern void abort();

// String

typedef struct {
    u8 *data;
    usize data_size;
    usize length;
} String;

String *create_string(usize data_size) {
    String *string = malloc(sizeof(String));
    string->data = malloc(data_size);
    string->data_size = data_size;
    string->length = 0;
    return string;
}

String *make_string() {
    return create_string(16);
}

String *make_string_from(u8 *data) {
    usize string_length = 0;
    while (1) {
        u8 c = data[string_length];
        if (c == 0) {
            break;
        }
        string_length += 1;
    }
    String *string = malloc(sizeof(String));
    string->data = data;
    string->data_size = string_length + 1;
    string->length = string_length;
    return string;
}

String *String__append_char(String *self, u8 ch) {
    if (self->length >= self->data_size) {
        self->data_size = self->data_size + 16;
        self->data = realloc(self->data, self->data_size);
    }
    self->data[self->length] = ch;
    self->length = self->length + 1;
    return self;
}

void File__write_string(File *self, String *string) {
    usize index = 0;
    while (index < string->length) {
        fputc(string->data[index], self);
        index = index + 1;
    }
}

// Utils

void pass() {
}

void panic(String *message) {
    File__write_string(stderr, message);
    abort();
}

// Scanner

String *scan() {
    String *content = make_string();

    while (true) {
        i32 ch = fgetc(stdin);
        if (ch == -1) {
            break;
        }
        String__append_char(content, ch);
    }

    return content;
}

// Main

i32 main() {
    String *content = scan();

    File__write_string(stdout, content);

    return 0;
}
