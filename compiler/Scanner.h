/* Copyright (C) 2023-2024 Stefan Selariu */

#ifndef __SCANNER_H__
#define __SCANNER_H__

#include "Token.h"

typedef struct Scanner {
    Source *source;
    size_t current_char_index;
    uint16_t current_line;
    uint16_t current_column;
    Token *current_token;
} Scanner;

Token *Scanner__next_token(Scanner *self);

Token *Scanner__peek_token(Scanner *self, uint8_t offset);

Scanner *Scanner__create(Source *source);

#endif
