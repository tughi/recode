#include "Scanner.h"
#include "String.h"

#include <ctype.h>
#include <stdio.h>

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

    String *lexeme = new String();
    int line = current_line;
    int column = current_column;

    while (isspace(current_char)) {
        auto previous_char = current_char;
        next_char();
        if (previous_char == '\n') {
            return new Token(Token::END_OF_LINE, new String("<EOL>"), line, column);
        }
        line = current_line;
        column = current_column;
    }

    if (current_char == EOF) {
        return new Token(Token::END_OF_FILE, new String("<<EOF>>"), line, column);
    }

    if (isalpha(current_char) || current_char == '_') {
        lexeme->append(current_char);
        while (isalnum(next_char()) || current_char == '_') {
            lexeme->append(current_char);
        }
        if (lexeme->equals("enum")) {
            return new Token(Token::ENUM, lexeme, line, column);
        }
        if (lexeme->equals("struct")) {
            return new Token(Token::STRUCT, lexeme, line, column);
        }
        return new Token(Token::IDENTIFIER, lexeme, line, column);
    }

    if (isdigit(current_char)) {
        lexeme->append(current_char);
        int value = current_char - '0';
        while (isdigit(next_char())) {
            lexeme->append(current_char);
            value = value * 10 + current_char - '0';
        }
        return new Token(value, lexeme, line, column);
    }

    if (current_char == '\'') {
        lexeme->append(current_char);
        char value;
        switch (next_char()) {
        case '\\':
            lexeme->append(current_char);
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
                return new Token(Token::ERROR, lexeme, line, column);
            }
            break;
        case EOF:
        case '\'':
        case '\n':
            return new Token(Token::ERROR, lexeme, line, column);
        default:
            value = current_char;
            break;
        }
        lexeme->append(current_char);
        if (next_char() != '\'') {
            return new Token(Token::ERROR, lexeme, line, column);
        }
        lexeme->append(current_char);
        next_char();
        return new Token(value, lexeme, line, column);
    }

    if (current_char == '\"') {
        lexeme->append(current_char);
        String *value = new String();
        while (next_char() != EOF && current_char != '\n' && current_char != '\"') {
            lexeme->append(current_char);
            if (current_char == '\\') {
                switch (next_char()) {
                case 'n':
                    value->append('\n');
                    break;
                case '\'':
                    value->append('\'');
                    break;
                case '\"':
                    value->append('\"');
                    break;
                case '\\':
                    value->append('\\');
                    break;
                case 't':
                    value->append('\t');
                    break;
                case 'r':
                    value->append('\r');
                    break;
                default:
                    return new Token(Token::ERROR, lexeme, line, column);
                }
                lexeme->append(current_char);
            } else {
                value->append(current_char);
            }
        }
        if (current_char != '\"') {
            return new Token(Token::ERROR, lexeme, line, column);
        }
        lexeme->append(current_char);
        next_char();
        return new Token(value, lexeme, line, column);
    }

    lexeme->append(current_char);
    while (next_char() != EOF && !isspace(current_char) && !isalnum(current_char) && current_char != '_' && current_char != '\'' && current_char != '\"') {
        lexeme->append(current_char);
    }
    return new Token(Token::OPERATOR, lexeme, line, column);
}
