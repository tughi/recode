#include "Scanner.h"

#include <iostream>

Token *scan_token() {
    static int current_char = ' ';
    static int current_line = 1;
    static int current_column = 1;

    std::string lexeme;
    int line = current_line;
    int column = current_column;

    auto next_char = []() {
        current_char = getchar();
        if (current_char == '\n') {
            current_line += 1;
            current_column = 1;
        } else {
            current_column += 1;
        }
        return current_char;
    };

    while (isspace(current_char)) {
        line = current_line;
        column = current_column;
        current_char = next_char();
    }

    if (current_char == EOF) {
        return new Token(Token::END_OF_FILE, "", line, column);
    }

    lexeme = current_char;

    if (isalpha(current_char) || current_char == '_') {
        while (isalnum(current_char = next_char()) || current_char == '_') {
            lexeme += current_char;
        }

        if (lexeme == "enum") {
            return new Token(Token::ENUM, lexeme, line, column);
        }
        if (lexeme == "struct") {
            return new Token(Token::STRUCT, lexeme, line, column);
        }
        return new Token(Token::IDENTIFIER, lexeme, line, column);
    }

    if (isdigit(current_char)) {
        while (isdigit(current_char = next_char())) {
            lexeme += current_char;
        }

        int value = strtod(lexeme.c_str(), 0);

        return new Token(value, lexeme, line, column);
    }

    current_char = next_char();
    return new Token(Token::OTHER, lexeme, line, column);
}
