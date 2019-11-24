#include "Scanner.h"
#include "String.h"

#include <stdio.h>

#define KEYWORDS_COUNT 4

const char *KEYWORDS[] = {
    "bool",
    "enum",
    "struct",
    "return",
};

bool is_character(char c) {
    return c >= ' ' && c < 128 && c != '\'';
}

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool is_double_quote(char c) {
    return c == '\"';
}

bool is_escape(char c) {
    return c == 'n' || c == 't' || c == '\"' || c == '\'' || c == '\\';
}

char get_escape(char c) {
    switch (c) {
    case '\"':
        return '\"';
    case '\'':
        return '\'';
    case '\\':
        return '\\';
    case 'n':
        return '\n';
    case 't':
        return '\t';
    }
    return 0;
}

bool is_identifier_start(char c) {
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_';
}

bool is_identifier_body(char c) {
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9';
}

bool is_single_quote(char c) {
    return c == '\'';
}

bool is_string_character(char c) {
    return c >= ' ' && c < 128 && c != '\"';
}

bool is_valid(char c) {
    return c > 0 && c < 128;
}

Token *read_character(Source &source) {
    String *lexeme = new String();
    int line = source.current_line();
    int column = source.current_column();

    char value = 0;
    char consumed;
    if (consumed = source.advance(is_single_quote)) {
        lexeme->append(consumed);
        if (consumed = source.advance(is_character)) {
            lexeme->append(consumed);
            if (consumed == '\\') {
                if (consumed = source.advance(is_escape)) {
                    lexeme->append(consumed);
                    value = get_escape(consumed);
                }
            } else {
                value = consumed;
            }
        }
    }
    if (value && (consumed = source.advance(is_single_quote))) {
        lexeme->append(consumed);
        return new Token(value, lexeme, line, column);
    }

    return new Token(Token::ERROR, lexeme, line, column);
}

Token *read_identifier(Source &source) {
    String *lexeme = new String();
    int line = source.current_line();
    int column = source.current_column();

    char current;
    while ((current = source.advance(is_identifier_body))) {
        lexeme->append(current);
    }

    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (lexeme->equals(KEYWORDS[i])) {
            return new Token(Token::KEYWORD, lexeme, line, column);
        }
    }

    return new Token(Token::IDENTIFIER, lexeme, line, column);
}

Token *read_integer(Source &source) {
    String *lexeme = new String();
    int line = source.current_line();
    int column = source.current_column();

    char current;
    int value = 0;
    while ((current = source.advance(is_digit))) {
        lexeme->append(current);
        value = value * 10 + (current - '0');
    }

    return new Token(value, lexeme, line, column);
}

Token *read_other(Source &source) {
    String *lexeme = new String();
    int line = source.current_line();
    int column = source.current_column();

    char consumed = source.advance(is_valid);
    switch (consumed) {
    case '\t':
        return new Token(Token::TAB, lexeme, line, column);
    case '\n':
        return new Token(Token::END_OF_LINE, lexeme, line, column);
    case ' ':
        return new Token(Token::SPACE, lexeme, line, column);
    }
    lexeme->append(consumed);
    return new Token(Token::OTHER, lexeme, line, column);
}

Token *read_string(Source &source) {
    String *lexeme = new String();
    int line = source.current_line();
    int column = source.current_column();

    String *value = new String();
    char consumed;
    if (consumed = source.advance(is_double_quote)) {
        lexeme->append(consumed);
        while (consumed = source.advance(is_string_character)) {
            lexeme->append(consumed);
            if (consumed == '\\') {
                if (consumed = source.advance(is_escape)) {
                    lexeme->append(consumed);
                    value->append(get_escape(consumed));
                } else {
                    return new Token(Token::ERROR, lexeme, line, column);
                }
            } else {
                value->append(consumed);
            }
        }
        if (consumed = source.advance(is_double_quote)) {
            lexeme->append(consumed);
            return new Token(value, lexeme, line, column);
        }
    }
    return new Token(Token::ERROR, lexeme, line, column);
}

Token *scan_token(Source &source) {
    char current = source.current();
    int token_line = source.current_line();
    int token_column = source.current_column();

    if (!is_valid(current)) {
        return new Token(Token::END_OF_FILE, new String(""), token_line, token_column);
    }

    Token *token;
    if (is_identifier_start(current)) {
        token = read_identifier(source);
    } else if (is_digit(current)) {
        token = read_integer(source);
    } else if (is_double_quote(current)) {
        token = read_string(source);
    } else if (is_single_quote(current)) {
        token = read_character(source);
    } else {
        token = read_other(source);
    }

    if (token_column == source.current_column() && token_line == source.current_line()) {
        throw "Each scan must advance the source";
    }

    return token;
}
