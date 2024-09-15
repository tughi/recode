/* Copyright (C) 2024 Stefan Selariu */

#ifndef __HEADER_SCANNER_H__
#define __HEADER_SCANNER_H__

#include "Token.h"

typedef struct Header_Scanner {
    Source *source;
    size_t current_char_index;
    uint16_t current_line;
    uint16_t current_column;
    Token *current_token;
} Header_Scanner;

Token *Header_Scanner__next_token(Header_Scanner *self);

Token *Header_Scanner__peek_token(Header_Scanner *self, uint8_t offset);

Header_Scanner *Header_Scanner__create(Source *source);

#endif
