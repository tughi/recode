/* Copyright (C) 2024 Stefan Selariu */

#ifndef __CHAR_H__
#define __CHAR_H__

#include "Builtins.h"

bool char_is_end_of_line(char c);

bool char_is_digit(char c);

bool char_is_identifier_start(char c);

bool char_is_identifier_letter(char c);

bool char_is_space(char c);

char escape_char_value(char c);

#endif
