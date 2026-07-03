#pragma once

#include "File.h"
#include "Token.h"

typedef struct {
    File file;
    Token *tokens;
    size_t tokens_size;
    Token **lines;
    size_t lines_size;
} Lexed_File;

Lexed_File tokenize(File file);
void lexed_file_destroy(Lexed_File lexed_file);
