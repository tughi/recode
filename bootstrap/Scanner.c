#include "Scanner.h"

#include "Logging.h"
#include "String.h"
#include "Token.h"

#define KEYWORDS_COUNT 16

const char *KEYWORDS[] = {
    "as",
    "break",
    "else",
    "enum",
    "external",
    "false",
    "if",
    "loop",
    "new",
    "null",
    "return",
    "size_of",
    "skip",
    "struct",
    "true",
    "while",
};

int is_character(unsigned char c) {
    return c >= ' ' && c < 128 && c != '\'';
}

int is_digit(unsigned char c) {
    return c >= '0' && c <= '9';
}

int is_double_quote(unsigned char c) {
    return c == '\"';
}

int is_escape(unsigned char c) {
    return c == 'n' || c == 't' || c == '\"' || c == '\'' || c == '\\' || c == '0';
}

char get_escape(unsigned char c) {
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
    case '0':
        return 0;
    }
    return -1;
}

int is_identifier_start(unsigned char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

int is_identifier_body(unsigned char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c >= '0' && c <= '9');
}

int is_comment_start(unsigned char c) {
    return c == '\\';
}

int is_comment_body(unsigned char c) {
    return (c >= 32 && c <= 127) || c == '\t';
}

int is_single_quote(unsigned char c) {
    return c == '\'';
}

int is_whitespace(unsigned char c) {
    return c == ' ' || c == '\t';
}

int is_string_character(unsigned char c) {
    return c >= ' ' && c < 128 && c != '\"';
}

int is_valid(unsigned char c) {
    return c > 0 && c < 128;
}

Token *read_character(Source *source) {
    Source_Location *location = source_location__create(source);
    String *lexeme = string__create_empty(1);

    char value = -1;
    char consumed;
    if ((consumed = source__advance(source, is_single_quote))) {
        string__append_char(lexeme, consumed);
        if ((consumed = source__advance(source, is_character))) {
            string__append_char(lexeme, consumed);
            if (consumed == '\\') {
                if ((consumed = source__advance(source, is_escape))) {
                    string__append_char(lexeme, consumed);
                    value = get_escape(consumed);
                }
            } else {
                value = consumed;
            }
        }
    }
    if (value >= 0 && (consumed = source__advance(source, is_single_quote))) {
        string__append_char(lexeme, consumed);
        return token__create_character(location, lexeme, value);
    }
    return token__create_error(location, lexeme);
}

Token *read_space(Source *source) {
    Source_Location *location = source_location__create(source);
    String *lexeme = string__create_empty(2);

    char consumed;
    int count = 0;
    while ((consumed = source__advance(source, is_whitespace))) {
        if (consumed == '\t') {
            count = (count / TAB_SIZE + 1) * TAB_SIZE;
        } else {
            count += 1;
        }
        string__append_char(lexeme, consumed);
    }
    return token__create_space(location, lexeme, count);
}

Token *read_comment(Source *source) {
    Source_Location *location = source_location__create(source);
    String *lexeme = string__create_empty(2);

    char consumed;
    while ((consumed = source__advance(source, is_comment_body))) {
        string__append_char(lexeme, consumed);
    }
    return token__create_comment(location, lexeme);
}

Token *read_identifier(Source *source) {
    Source_Location *location = source_location__create(source);
    String *lexeme = string__create_empty(2);

    char consumed;
    while ((consumed = source__advance(source, is_identifier_body))) {
        string__append_char(lexeme, consumed);
    }
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (string__equals(lexeme, KEYWORDS[i])) {
            return token__create_keyword(location, lexeme);
        }
    }
    return token__create_identifier(location, lexeme);
}

Token *read_integer(Source *source) {
    Source_Location *location = source_location__create(source);
    String *lexeme = string__create_empty(2);

    char consumed;
    int value = 0;
    while ((consumed = source__advance(source, is_digit))) {
        string__append_char(lexeme, consumed);
        value = value * 10 + (consumed - '0');
    }
    return token__create_integer(location, lexeme, value);
}

Token *read_other(Source *source) {
    Source_Location *location = source_location__create(source);
    String *lexeme = string__create_empty(2);

    char consumed = source__advance(source, is_valid);
    if (consumed == '\n') {
        string__append_string(lexeme, string__create("<EOL>"));
        return token__create_end_of_line(location, lexeme);
    }

    string__append_char(lexeme, consumed);
    return token__create_other(location, lexeme);
}

Token *read_string(Source *source) {
    Source_Location *location = source_location__create(source);
    String *lexeme = string__create_empty(2);

    String *value = string__create_empty(32);
    char consumed;
    if ((consumed = source__advance(source, is_double_quote))) {
        string__append_char(lexeme, consumed);
        while ((consumed = source__advance(source, is_string_character))) {
            string__append_char(lexeme, consumed);
            if (consumed == '\\') {
                if ((consumed = source__advance(source, is_escape))) {
                    string__append_char(lexeme, consumed);
                    string__append_char(value, get_escape(consumed));
                } else {
                    return token__create_error(location, lexeme);
                }
            } else {
                string__append_char(value, consumed);
            }
        }
        if ((consumed = source__advance(source, is_double_quote))) {
            string__append_char(lexeme, consumed);
            return token__create_string(location, lexeme, value);
        }
    }
    return token__create_error(location, lexeme);
}

Token *scan_token(Source *source) {
    char next_char = source__peek(source);
    int token_line = source__current_line(source);
    int token_column = source__current_column(source);

    if (!is_valid(next_char)) {
        return token__create_end_of_file(source_location__create(source), string__create("<<EOF>>"));
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
        PANIC(__FILE__, __LINE__, "Each scan must advance the source%c", 0);
    }

    return token;
}

List *scan(Source *source) {
    List *tokens = list__create();

    for (;;) {
        Token *token = scan_token(source);
        list__append(tokens, token);
        if (token->kind == TOKEN__END_OF_FILE) {
            return tokens;
        }
    }
}
