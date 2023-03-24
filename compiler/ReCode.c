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

// Scanner

void scan() {
    while (true) {
        i32 c = fgetc(stdin);
        if (c == -1) {
            break;
        }
        fputc(c, stdout);
    }
}

i32 main() {
    scan();

    return 0;
}
