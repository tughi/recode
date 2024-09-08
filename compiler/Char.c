/* Copyright (C) 2024 Stefan Selariu */

#include "Char.h"

bool char_is_end_of_line(char c) {
    return c == '\n' || c == '\0';
}
bool char_is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool char_is_identifier_start(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool char_is_identifier_letter(char c) {
    return char_is_identifier_start(c) || (c >= '0' && c <= '9');
}

bool char_is_space(char c) {
    return c == ' ';
}

char escape_char_value(char c) {
    if (c == 'n') {
        return '\n';
    }
    if (c == '"') {
        return '\"';
    }
    if (c == '\'') {
        return '\'';
    }
    if (c == '\\') {
        return '\\';
    }
    if (c == 't') {
        return '\t';
    }
    if (c == '0') {
        return '\0';
    }
    if (c == 'e') {
        return '\033';
    }
    return (char)-1;
}
