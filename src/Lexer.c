#include "Lexer.h"

void lexer_init(Lexer *lexer, String source) {
    lexer->source = source;
    lexer->source_position = 0;
}

static Token scan_space(Lexer *lexer) {
    const char *source = lexer->source.content;
    size_t length = lexer->source.length;
    size_t start = lexer->source_position;
    size_t position = start;
    while (position < length && source[position] == ' ') {
        position++;
    }
    lexer->source_position = position;
    Token token;
    token.kind = TOKEN_KIND__SPACE;
    token.space.lexeme = (String){.content = source + start, .length = position - start};
    token.space.source_position = start;
    token.space.count = position - start;
    return token;
}

static Token scan_end_of_line(Lexer *lexer) {
    const char *source = lexer->source.content;
    size_t start = lexer->source_position;
    lexer->source_position = start + 1;
    Token token;
    token.kind = TOKEN_KIND__END_OF_LINE;
    token.end_of_line.lexeme = (String){.content = source + start, .length = 1};
    token.end_of_line.source_position = start;
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
    Token token;
    if (position < length && source[position] == '\'') {
        position++;
        token.kind = TOKEN_KIND__CHARACTER;
        token.character.lexeme = (String){.content = source + start, .length = position - start};
        token.character.source_position = start;
    } else {
        token.kind = TOKEN_KIND__ERROR;
        token.error.lexeme = (String){.content = source + start, .length = position - start};
        token.error.source_position = start;
    }
    lexer->source_position = position;
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
    Token token;
    if (position < length && source[position] == '"') {
        position++;
        token.kind = TOKEN_KIND__STRING;
        token.string.lexeme = (String){.content = source + start, .length = position - start};
        token.string.source_position = start;
    } else {
        token.kind = TOKEN_KIND__ERROR;
        token.error.lexeme = (String){.content = source + start, .length = position - start};
        token.error.source_position = start;
    }
    lexer->source_position = position;
    return token;
}

static int is_digit(char c) {
    return c >= '0' && c <= '9';
}

static int is_hex_digit(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

static Token scan_integer(Lexer *lexer) {
    const char *source = lexer->source.content;
    size_t length = lexer->source.length;
    size_t start = lexer->source_position;
    size_t position = start;
    if (source[position] == '0' && position + 1 < length && (source[position + 1] == 'x' || source[position + 1] == 'X')) {
        position += 2;
        while (position < length && (is_hex_digit(source[position]) || source[position] == '_')) {
            position++;
        }
    } else {
        while (position < length && (is_digit(source[position]) || source[position] == '_')) {
            position++;
        }
    }
    lexer->source_position = position;
    Token token;
    token.kind = TOKEN_KIND__INTEGER;
    token.integer.lexeme = (String){.content = source + start, .length = position - start};
    token.integer.source_position = start;
    return token;
}

static int is_identifier_char(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

static Token scan_identifier(Lexer *lexer) {
    const char *source = lexer->source.content;
    size_t length = lexer->source.length;
    size_t start = lexer->source_position;
    size_t position = start;
    while (position < length && is_identifier_char(source[position])) {
        position++;
    }
    lexer->source_position = position;
    Token token;
    token.kind = TOKEN_KIND__IDENTIFIER;
    token.identifier.lexeme = (String){.content = source + start, .length = position - start};
    token.identifier.source_position = start;
    return token;
}

static Token scan_other(Lexer *lexer) {
    const char *source = lexer->source.content;
    size_t start = lexer->source_position;
    lexer->source_position = start + 1;
    Token token;
    token.kind = TOKEN_KIND__OTHER;
    token.other.lexeme = (String){.content = source + start, .length = 1};
    token.other.source_position = start;
    token.other.value = source[start];
    return token;
}

Token lexer_next(Lexer *lexer) {
    const char *source = lexer->source.content;
    size_t length = lexer->source.length;
    size_t position = lexer->source_position;

    if (position >= length) {
        Token token;
        token.kind = TOKEN_KIND__END_OF_FILE;
        token.end_of_file.lexeme = (String){.content = source + position, .length = 0};
        token.end_of_file.source_position = position;
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
    case '0' ... '9':
        return scan_integer(lexer);
    case 'a' ... 'z':
    case 'A' ... 'Z':
    case '_':
        return scan_identifier(lexer);
    default:
        return scan_other(lexer);
    }
}
