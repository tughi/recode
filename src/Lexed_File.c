#include "Lexed_File.h"
#include "Lexer.h"
#include <stdlib.h>

Lexed_File tokenize(File file) {
    size_t tokens_capacity = file.content.length * 3 / 5;

    Lexed_File lexed_file = {
        .file = file,
        .tokens = malloc(tokens_capacity * sizeof(Token)),
    };

    Lexer *lexer = lexer_create(file);
    for (;;) {
        if (lexed_file.tokens_size == tokens_capacity) {
            tokens_capacity = tokens_capacity + tokens_capacity / 2;
            lexed_file.tokens = realloc(lexed_file.tokens, tokens_capacity * sizeof(Token));
        }
        Token token = lexer_next(lexer);
        lexed_file.tokens[lexed_file.tokens_size++] = token;
        if (token.kind == TOKEN_KIND__END_OF_FILE) {
            break;
        }
    }
    lexer_destroy(lexer);

    lexed_file.lines_size = lexed_file.tokens[lexed_file.tokens_size - 1].location.line;
    lexed_file.lines = malloc(lexed_file.lines_size * sizeof(Token *));
    lexed_file.lines[0] = &lexed_file.tokens[0];
    for (size_t i = 0, l = 1; i < lexed_file.tokens_size; i++) {
        if (lexed_file.tokens[i].kind == TOKEN_KIND__END_OF_LINE && i + 1 < lexed_file.tokens_size) {
            lexed_file.lines[l++] = &lexed_file.tokens[i + 1];
        }
    }
    return lexed_file;
}

void lexed_file_destroy(Lexed_File lexed_file) {
    free(lexed_file.tokens);
    free(lexed_file.lines);
}
