#include "Scanner.h"

#include <iostream>
#include <string.h>

char *copy_string(std::string string) {
    auto string_length = strlen(string.c_str());
    auto new_string = (char *)malloc(string_length + 1);
    strncpy(new_string, string.c_str(), string_length);
    new_string[string_length] = 0;
    return new_string;
}

Token *scan_token() {
    static int current_char = ' ';
    static int current_line = 1;
    static int current_column = 0;

    auto next_char = []() {
        auto previous_char = current_char;
        current_char = getchar();
        if (previous_char == '\n') {
            current_line += 1;
            current_column = 1;
        } else {
            current_column += 1;
        }
        return current_char;
    };

    std::string lexeme;
    int line = current_line;
    int column = current_column;

    while (isspace(current_char)) {
        auto previous_char = current_char;
        next_char();
        if (previous_char == '\n') {
            return new Token(Token::END_OF_LINE, "<EOL>", line, column);
        }
        line = current_line;
        column = current_column;
    }

    if (current_char == EOF) {
        return new Token(Token::END_OF_FILE, "<<EOF>>", line, column);
    }

    if (isalpha(current_char) || current_char == '_') {
        lexeme = current_char;
        while (isalnum(next_char()) || current_char == '_') {
            lexeme += current_char;
        }
        if (lexeme == "enum") {
            return new Token(Token::ENUM, copy_string(lexeme), line, column);
        }
        if (lexeme == "struct") {
            return new Token(Token::STRUCT, copy_string(lexeme), line, column);
        }
        return new Token(Token::IDENTIFIER, copy_string(lexeme), line, column);
    }

    if (isdigit(current_char)) {
        lexeme = current_char;
        int value = current_char - '0';
        while (isdigit(next_char())) {
            lexeme += current_char;
            value = value * 10 + current_char - '0';
        }
        return new Token(value, copy_string(lexeme), line, column);
    }

    if (current_char == '\'') {
        lexeme = current_char;
        char value;
        switch (next_char()) {
        case '\\':
            lexeme += current_char;
            switch (next_char()) {
            case 'n':
                value = '\n';
                break;
            case '\'':
                value = '\'';
                break;
            case '\"':
                value = '\"';
                break;
            case '\\':
                value = '\\';
                break;
            case 't':
                value = '\t';
                break;
            case 'r':
                value = '\r';
                break;
            default:
                return new Token(Token::ERROR, copy_string(lexeme), line, column);
            }
            break;
        case EOF:
        case '\n':
            return new Token(Token::ERROR, copy_string(lexeme), line, column);
        default:
            value = current_char;
            break;
        }
        lexeme += current_char;
        if (next_char() != '\'') {
            return new Token(Token::ERROR, copy_string(lexeme), line, column);
        }
        lexeme += current_char;
        next_char();
        return new Token(value, copy_string(lexeme), line, column);
    }

    if (current_char == '\"') {
        lexeme = current_char;
        std::string value;
        while (next_char() != EOF && current_char != '\n' && current_char != '\"') {
            lexeme += current_char;
            if (current_char == '\\') {
                switch (next_char()) {
                case 'n':
                    value += '\n';
                    break;
                case '\'':
                    value += '\'';
                    break;
                case '\"':
                    value += '\"';
                    break;
                case '\\':
                    value += '\\';
                    break;
                case 't':
                    value += '\t';
                    break;
                case 'r':
                    value += '\r';
                    break;
                default:
                    return new Token(Token::ERROR, copy_string(lexeme), line, column);
                }
                lexeme += current_char;
            } else {
                value += current_char;
            }
        }
        if (current_char != '\"') {
            return new Token(Token::ERROR, copy_string(lexeme), line, column);
        }
        lexeme += current_char;
        next_char();
        return new Token(value.c_str(), copy_string(lexeme), line, column);
    }

    lexeme = current_char;
    while (next_char() != EOF && !isspace(current_char) && !isalnum(current_char) && current_char != '_' && current_char != '\'' && current_char != '\"') {
        lexeme += current_char;
    }
    return new Token(Token::OPERATOR, copy_string(lexeme), line, column);
}
