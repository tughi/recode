#include "Scanner.h"
#include "String.h"

#include <stdio.h>
#include <stdlib.h>

#define KEYWORDS_COUNT 11

const char *KEYWORDS[] = {
    "as",
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

int is_character(char c) {
    return c >= ' ' && c < 128 && c != '\'';
}

int is_digit(char c) {
    return c >= '0' && c <= '9';
}

int is_double_quote(char c) {
    return c == '\"';
}

int is_escape(char c) {
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

int is_identifier_start(char c) {
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_';
}

int is_identifier_body(char c) {
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9';
}

int is_comment_start(char c) {
    return c == '\\';
}

int is_comment_body(char c) {
    return c >= 32 && c <= 127 || c == '\t';
}

int is_single_quote(char c) {
    return c == '\'';
}

int is_whitespace(char c) {
    return c == ' ' || c == '\t';
}

int is_string_character(char c) {
    return c >= ' ' && c < 128 && c != '\"';
}

int is_valid(char c) {
    return c > 0 && c < 128;
}

Token *read_character(Source *source) {
    String *lexeme = string__create_empty(1);
    int line = source__current_line(source);
    int column = source__current_column(source);

    char value = 0;
    char consumed;
    if (consumed = source__advance(source, is_single_quote)) {
        string__append_char(lexeme, consumed);
        if (consumed = source__advance(source, is_character)) {
            string__append_char(lexeme, consumed);
            if (consumed == '\\') {
                if (consumed = source__advance(source, is_escape)) {
                    string__append_char(lexeme, consumed);
                    value = get_escape(consumed);
                }
            } else {
                value = consumed;
            }
        }
    }
    if (value && (consumed = source__advance(source, is_single_quote))) {
        string__append_char(lexeme, consumed);
        return token__create_character(lexeme, line, column, value);
    }
    return token__create_error(lexeme, line, column);
}

Token *read_space(Source *source) {
    String *lexeme = string__create_empty(2);
    int line = source__current_line(source);
    int column = source__current_column(source);

    char consumed;
    int count = 0;
    while (consumed = source__advance(source, is_whitespace)) {
        if (consumed == '\t') {
            count = (count / TAB_SIZE + 1) * TAB_SIZE;
        } else {
            count += 1;
        }
        string__append_char(lexeme, consumed);
    }
    return token__create_space(lexeme, line, column, count);
}

Token *read_comment(Source *source) {
    String *lexeme = string__create_empty(2);
    int line = source__current_line(source);
    int column = source__current_column(source);

    char consumed;
    while (consumed = source__advance(source, is_comment_body)) {
        string__append_char(lexeme, consumed);
    }
    return token__create_comment(lexeme, line, column);
}

Token *read_identifier(Source *source) {
    String *lexeme = string__create_empty(2);
    int line = source__current_line(source);
    int column = source__current_column(source);

    char consumed;
    while ((consumed = source__advance(source, is_identifier_body))) {
        string__append_char(lexeme, consumed);
    }
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (string__equals(lexeme, KEYWORDS[i])) {
            return token__create_keyword(lexeme, line, column);
        }
    }
    return token__create_identifier(lexeme, line, column);
}

Token *read_integer(Source *source) {
    String *lexeme = string__create_empty(2);
    int line = source__current_line(source);
    int column = source__current_column(source);

    char consumed;
    int value = 0;
    while ((consumed = source__advance(source, is_digit))) {
        string__append_char(lexeme, consumed);
        value = value * 10 + (consumed - '0');
    }
    return token__create_integer(lexeme, line, column, value);
}

Token *read_other(Source *source) {
    String *lexeme = string__create_empty(2);
    int line = source__current_line(source);
    int column = source__current_column(source);

    char consumed = source__advance(source, is_valid);
    if (consumed == '\n') {
        string__append_string(lexeme, string__create("<EOL>"));
        return token__create_end_of_line(lexeme, line, column);
    }

    string__append_char(lexeme, consumed);
    return token__create_other(lexeme, line, column);
}

Token *read_string(Source *source) {
    String *lexeme = string__create_empty(2);
    int line = source__current_line(source);
    int column = source__current_column(source);

    String *value = string__create_empty(32);
    char consumed;
    if (consumed = source__advance(source, is_double_quote)) {
        string__append_char(lexeme, consumed);
        while (consumed = source__advance(source, is_string_character)) {
            string__append_char(lexeme, consumed);
            if (consumed == '\\') {
                if (consumed = source__advance(source, is_escape)) {
                    string__append_char(lexeme, consumed);
                    string__append_char(value, get_escape(consumed));
                } else {
                    return token__create_error(lexeme, line, column);
                }
            } else {
                string__append_char(value, consumed);
            }
        }
        if (consumed = source__advance(source, is_double_quote)) {
            string__append_char(lexeme, consumed);
            return token__create_string(lexeme, line, column, value);
        }
    }
    return token__create_error(lexeme, line, column);
}

Token *scan_token(Source *source) {
    char next_char = source__peek(source);
    int token_line = source__current_line(source);
    int token_column = source__current_column(source);

    if (!is_valid(next_char)) {
        return token__create_end_of_file(string__create("<<EOF>>"), token_line, token_column);
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
    } else if (is_whitespace(next_char)) {
        token = read_space(source);
    } else {
        token = read_other(source);
    }

    if (token_column == source__current_column(source) && token_line == source__current_line(source)) {
        printf("Each scan must advance the source");
        exit(1);
    }

    return token;
}

Token *scan(Source *source) {
    Token *first = scan_token(source);
    Token *last = first;

    while (last->kind != TOKEN_END_OF_FILE) {
        last->next = scan_token(source);
        last = last->next;
    }

    return first;
}
