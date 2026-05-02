#include "Lexer.h"
#include <stdlib.h>

struct Lexer {
    String source;
    size_t source_column;
    size_t source_line;
    size_t source_position;
};

Lexer *lexer_create(String source) {
    Lexer *lexer = malloc(sizeof(Lexer));
    lexer->source = source;
    lexer->source_column = 1;
    lexer->source_line = 1;
    lexer->source_position = 0;
    return lexer;
}

void lexer_destroy(Lexer *lexer) {
    free(lexer);
}

static void lexer_advance(Lexer *lexer, size_t from, size_t to) {
    const char *source = lexer->source.content;
    for (size_t i = from; i < to; i++) {
        if (source[i] == '\n') {
            lexer->source_line++;
            lexer->source_column = 1;
        } else {
            lexer->source_column++;
        }
    }
    lexer->source_position = to;
}

static Token scan_space(Lexer *lexer) {
    const char *source = lexer->source.content;
    size_t length = lexer->source.length;
    size_t start = lexer->source_position;
    size_t position = start;
    while (position < length && source[position] == ' ') {
        position++;
    }
    Source_Location location = {.column = lexer->source_column, .line = lexer->source_line};
    lexer_advance(lexer, start, position);
    Token token;
    token.kind = TOKEN_KIND__SPACE;
    token.space.lexeme = (String){.content = source + start, .length = position - start};
    token.space.location = location;
    token.space.count = position - start;
    return token;
}

static Token scan_end_of_line(Lexer *lexer) {
    const char *source = lexer->source.content;
    size_t start = lexer->source_position;
    Source_Location location = {.column = lexer->source_column, .line = lexer->source_line};
    lexer_advance(lexer, start, start + 1);
    Token token;
    token.kind = TOKEN_KIND__END_OF_LINE;
    token.end_of_line.lexeme = (String){.content = source + start, .length = 1};
    token.end_of_line.location = location;
    return token;
}

static Token scan_character(Lexer *lexer) {
    const char *source = lexer->source.content;
    size_t length = lexer->source.length;
    size_t start = lexer->source_position;
    size_t position = start + 1;
    if (position < length && source[position] == '\\') {
        position++;
    }
    if (position < length) {
        position++;
    }
    Source_Location location = {.column = lexer->source_column, .line = lexer->source_line};
    Token token;
    if (position < length && source[position] == '\'') {
        position++;
        token.kind = TOKEN_KIND__CHARACTER;
        token.character.lexeme = (String){.content = source + start, .length = position - start};
        token.character.location = location;
        if (source[start + 1] == '\\') {
            switch (source[start + 2]) {
            case '0': token.character.value = '\0'; break;
            case 'n': token.character.value = '\n'; break;
            case 'r': token.character.value = '\r'; break;
            case 't': token.character.value = '\t'; break;
            default:  token.character.value = (uint8_t)source[start + 2]; break;
            }
        } else {
            token.character.value = (uint8_t)source[start + 1];
        }
    } else {
        token.kind = TOKEN_KIND__ERROR;
        token.error.lexeme = (String){.content = source + start, .length = position - start};
        token.error.location = location;
    }
    lexer_advance(lexer, start, position);
    return token;
}

static Token scan_string(Lexer *lexer) {
    const char *source = lexer->source.content;
    size_t length = lexer->source.length;
    size_t start = lexer->source_position;
    size_t position = start + 1;
    while (position < length && source[position] != '"' && source[position] != '\n') {
        if (source[position] == '\\') {
            position++;
        }
        if (position < length) {
            position++;
        }
    }
    Source_Location location = {.column = lexer->source_column, .line = lexer->source_line};
    Token token;
    if (position < length && source[position] == '"') {
        position++;
        token.kind = TOKEN_KIND__STRING;
        token.string.lexeme = (String){.content = source + start, .length = position - start};
        token.string.location = location;
    } else {
        token.kind = TOKEN_KIND__ERROR;
        token.error.lexeme = (String){.content = source + start, .length = position - start};
        token.error.location = location;
    }
    lexer_advance(lexer, start, position);
    return token;
}

static int is_digit(char c) {
    return c >= '0' && c <= '9';
}

static int is_hex_digit(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

static int hex_digit_value(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
    return 10 + (c - 'A');
}

static Token scan_integer(Lexer *lexer) {
    const char *source = lexer->source.content;
    size_t length = lexer->source.length;
    size_t start = lexer->source_position;
    size_t position = start;
    int64_t value = 0;
    if (source[position] == '0' && position + 1 < length && (source[position + 1] == 'x' || source[position + 1] == 'X')) {
        position += 2;
        while (position < length && (is_hex_digit(source[position]) || source[position] == '_')) {
            if (source[position] != '_') {
                value = value * 16 + hex_digit_value(source[position]);
            }
            position++;
        }
    } else {
        while (position < length && (is_digit(source[position]) || source[position] == '_')) {
            if (source[position] != '_') {
                value = value * 10 + (source[position] - '0');
            }
            position++;
        }
    }
    Source_Location location = {.column = lexer->source_column, .line = lexer->source_line};
    lexer_advance(lexer, start, position);
    Token token;
    token.kind = TOKEN_KIND__INTEGER;
    token.integer.lexeme = (String){.content = source + start, .length = position - start};
    token.integer.location = location;
    token.integer.value = value;
    return token;
}

static int is_identifier_char(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

static Token scan_other(Lexer *lexer);

static int is_variable_body_char(char c) {
    return is_identifier_char(c) || c == '.';
}

static Token scan_label(Lexer *lexer) {
    const char *source = lexer->source.content;
    size_t length = lexer->source.length;
    size_t start = lexer->source_position;
    size_t body_start = start + 1;
    size_t position = body_start;
    size_t value = 0;
    while (position < length && is_digit(source[position])) {
        value = value * 10 + (size_t)(source[position] - '0');
        position++;
    }
    if (position == body_start) {
        return scan_other(lexer);
    }
    Source_Location location = {.column = lexer->source_column, .line = lexer->source_line};
    lexer_advance(lexer, start, position);
    Token token;
    token.kind = TOKEN_KIND__LABEL;
    token.label.lexeme = (String){.content = source + start, .length = position - start};
    token.label.location = location;
    token.label.value = value;
    return token;
}

static Token scan_variable(Lexer *lexer) {
    const char *source = lexer->source.content;
    size_t length = lexer->source.length;
    size_t start = lexer->source_position;
    char prefix = source[start];
    size_t body_start = start + 1;
    size_t position = body_start;
    while (position < length && is_variable_body_char(source[position])) {
        position++;
    }
    if (position == body_start) {
        return scan_other(lexer);
    }
    Source_Location location = {.column = lexer->source_column, .line = lexer->source_line};
    lexer_advance(lexer, start, position);
    Token token;
    token.kind = TOKEN_KIND__VARIABLE;
    token.variable.lexeme = (String){.content = source + start, .length = position - start};
    token.variable.location = location;
    token.variable.prefix = prefix;
    return token;
}

static Token scan_identifier(Lexer *lexer) {
    const char *source = lexer->source.content;
    size_t length = lexer->source.length;
    size_t start = lexer->source_position;
    size_t position = start;
    while (position < length && is_identifier_char(source[position])) {
        position++;
    }
    Source_Location location = {.column = lexer->source_column, .line = lexer->source_line};
    lexer_advance(lexer, start, position);
    Token token;
    token.kind = TOKEN_KIND__IDENTIFIER;
    token.identifier.lexeme = (String){.content = source + start, .length = position - start};
    token.identifier.location = location;
    return token;
}

static Token scan_other(Lexer *lexer) {
    const char *source = lexer->source.content;
    size_t start = lexer->source_position;
    Source_Location location = {.column = lexer->source_column, .line = lexer->source_line};
    lexer_advance(lexer, start, start + 1);
    Token token;
    token.kind = TOKEN_KIND__OTHER;
    token.other.lexeme = (String){.content = source + start, .length = 1};
    token.other.location = location;
    token.other.value = source[start];
    return token;
}

Token lexer_next(Lexer *lexer) {
    const char *source = lexer->source.content;
    size_t length = lexer->source.length;

    for (;;) {
        size_t position = lexer->source_position;

        if (position >= length) {
            Source_Location location = {.column = lexer->source_column, .line = lexer->source_line};
            Token token;
            token.kind = TOKEN_KIND__END_OF_FILE;
            token.end_of_file.lexeme = (String){.content = source + position, .length = 0};
            token.end_of_file.location = location;
            return token;
        }

        switch (source[position]) {
        case ' ':
            return scan_space(lexer);
        case '\n':
            return scan_end_of_line(lexer);
        case '\'':
            return scan_character(lexer);
        case '"':
            return scan_string(lexer);
        case ';': {
            size_t start = position;
            while (position < length && source[position] != '\n') {
                position++;
            }
            lexer_advance(lexer, start, position);
            continue;
        }
        case '0' ... '9':
            return scan_integer(lexer);
        case '@':
            return scan_label(lexer);
        case '%':
        case '$':
            return scan_variable(lexer);
        case 'a' ... 'z':
        case 'A' ... 'Z':
        case '_':
            return scan_identifier(lexer);
        default:
            return scan_other(lexer);
        }
    }
}
