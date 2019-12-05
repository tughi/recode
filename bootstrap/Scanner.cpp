#include "Scanner.h"
#include "String.h"

#include <stdio.h>

#define KEYWORDS_COUNT 10

const char *KEYWORDS[] = {
    "break",
    "else",
    "enum",
    "false",
    "if",
    "loop",
    "return",
    "skip",
    "struct",
    "true",
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

bool is_comment_start(char c) {
    return c == '\\';
}

bool is_comment_body(char c) {
    return c >= 32 && c <= 127 || c == '\t';
}

bool is_single_quote(char c) {
    return c == '\'';
}

bool is_space(char c) {
    return c == ' ' || c == '\t';
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
        return create_character(lexeme, line, column, value);
    }
    return create_error(lexeme, line, column);
}

Token *read_space(Source &source) {
    String *lexeme = new String();
    int line = source.current_line();
    int column = source.current_column();

    char consumed;
    int count = 0;
    while (consumed = source.advance(is_space)) {
        if (consumed == '\t') {
            count = (count / TAB_SIZE + 1) * TAB_SIZE;
        } else {
            count += 1;
        }
        lexeme->append(consumed);
    }
    return create_space(lexeme, line, column, count);
}

Token *read_comment(Source &source) {
    String *lexeme = new String();
    int line = source.current_line();
    int column = source.current_column();

    char consumed;
    while (consumed = source.advance(is_comment_body)) {
        lexeme->append(consumed);
    }
    return create_comment(lexeme, line, column);
}

Token *read_identifier(Source &source) {
    String *lexeme = new String();
    int line = source.current_line();
    int column = source.current_column();

    char consumed;
    while ((consumed = source.advance(is_identifier_body))) {
        lexeme->append(consumed);
    }
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (lexeme->equals(KEYWORDS[i])) {
            return create_keyword(lexeme, line, column);
        }
    }
    return create_identifier(lexeme, line, column);
}

Token *read_integer(Source &source) {
    String *lexeme = new String();
    int line = source.current_line();
    int column = source.current_column();

    char consumed;
    int value = 0;
    while ((consumed = source.advance(is_digit))) {
        lexeme->append(consumed);
        value = value * 10 + (consumed - '0');
    }
    return create_integer(lexeme, line, column, value);
}

Token *read_other(Source &source) {
    String *lexeme = new String();
    int line = source.current_line();
    int column = source.current_column();

    char consumed = source.advance(is_valid);
    if (consumed == '\n') {
        auto eol = String("<EOL>");
        lexeme->append(eol);
        return create_end_of_line(lexeme, line, column);
    }

    lexeme->append(consumed);
    return create_other(lexeme, line, column);
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
                    return create_error(lexeme, line, column);
                }
            } else {
                value->append(consumed);
            }
        }
        if (consumed = source.advance(is_double_quote)) {
            lexeme->append(consumed);
            return create_string(lexeme, line, column, value);
        }
    }
    return create_error(lexeme, line, column);
}

Token *scan_token(Source &source) {
    char next_char = source.peek();
    int token_line = source.current_line();
    int token_column = source.current_column();

    if (!is_valid(next_char)) {
        return create_end_of_file(new String("<<EOF>>"), token_line, token_column);
    }

    Token *token;
    if (is_identifier_start(next_char)) {
        token = read_identifier(source);
    } else if (is_digit(next_char)) {
        token = read_integer(source);
    } else if (is_double_quote(next_char)) {
        token = read_string(source);
    } else if (is_single_quote(next_char)) {
        token = read_character(source);
    } else if (is_comment_start(next_char)) {
        token = read_comment(source);
    } else if (is_space(next_char)) {
        token = read_space(source);
    } else {
        token = read_other(source);
    }

    if (token_column == source.current_column() && token_line == source.current_line()) {
        throw "Each scan must advance the source";
    }

    return token;
}

Token *scan(Source &source) {
    Token *first = scan_token(source);
    Token *last = first;

    while (last->type != Token::END_OF_FILE) {
        last->next = scan_token(source);
        last = last->next;
    }

    return first;
}
