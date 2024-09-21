/* Copyright (C) 2024 Stefan Selariu */

#include "Scanner.h"

char Scanner__peek_char(Scanner *self) {
    return self->source->content[self->current_char_index];
}

char Scanner__next_char(Scanner *self) {
    char next_char = Scanner__peek_char(self);
    if (next_char != '\0') {
        self->current_char_index = self->current_char_index + 1;
        if (next_char == '\n') {
            self->current_line = self->current_line + 1;
            self->current_column = 1;
        } else {
            self->current_column = self->current_column + 1;
        }
    }
    return next_char;
}

Token *Scanner__scan_character_token(Scanner *self, Source_Location *source_location, String *token_lexeme) {
    if (Scanner__next_char(self) != '\'') {
        Source_Location__error(source_location, String__create_from("Unexpected char"));
        panic();
    }
    String__append_char(token_lexeme, '\'');

    char next_char = Scanner__peek_char(self);
    if (char_is_end_of_line(next_char) || next_char == '\t') {
        return (Token *)Error_Token__create(source_location, token_lexeme);
    }

    String__append_char(token_lexeme, Scanner__next_char(self));
    char value = next_char;

    if (value == '\'') {
        return (Token *)Error_Token__create(source_location, token_lexeme);
    }

    if (value == '\\') {
        next_char = Scanner__peek_char(self);
        if (char_is_end_of_line(next_char) || next_char == '\t') {
            return (Token *)Error_Token__create(source_location, token_lexeme);
        }

        String__append_char(token_lexeme, Scanner__next_char(self));

        value = escape_char_value(next_char);
        if (value == (char)-1) {
            return (Token *)Error_Token__create(source_location, token_lexeme);
        }
    }

    if (Scanner__peek_char(self) != '\'') {
        return (Token *)Error_Token__create(source_location, token_lexeme);
    }

    String__append_char(token_lexeme, Scanner__next_char(self));
    return (Token *)Character_Token__create(source_location, token_lexeme, value);
}

Token *Scanner__scan_comment_token(Scanner *self, Source_Location *source_location, String *token_lexeme) {
    do {
        String__append_char(token_lexeme, Scanner__next_char(self));
    } while (Scanner__peek_char(self) != '\n');
    return (Token *)Comment_Token__create(source_location, token_lexeme);
}

Token *Scanner__scan_identifier_token(Scanner *self, Source_Location *source_location, String *token_lexeme) {
    while (char_is_identifier_letter(Scanner__peek_char(self))) {
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
    return (Token *)Identifier_Token__create(source_location, token_lexeme);
}

Token *Scanner__scan_integer_token(Scanner *self, Source_Location *source_location, String *token_lexeme) {
    uint64_t value = 0;
    if (Scanner__peek_char(self) == '0') {
        String__append_char(token_lexeme, Scanner__next_char(self));
        if (Scanner__peek_char(self) == 'x') {
            String__append_char(token_lexeme, Scanner__next_char(self));
            while (true) {
                char c = Scanner__peek_char(self);
                if (char_is_digit(c)) {
                    value = value * 16 + (c - '0');
                    String__append_char(token_lexeme, Scanner__next_char(self));
                } else if (c >= 'A' && c <= 'F') {
                    value = value * 16 + (c - 'A' + 10);
                    String__append_char(token_lexeme, Scanner__next_char(self));
                } else if (c >= 'a' && c <= 'f') {
                    value = value * 16 + (c - 'a' + 10);
                    String__append_char(token_lexeme, Scanner__next_char(self));
                } else if (c == '_') {
                    String__append_char(token_lexeme, Scanner__next_char(self));
                } else {
                    break;
                }
            }
        }
    } else {
        while (char_is_digit(Scanner__peek_char(self))) {
            char c = Scanner__next_char(self);
            value = value * 10 + (c - '0');
            String__append_char(token_lexeme, c);
        }
    }
    return (Token *)Integer_Token__create(source_location, token_lexeme, value);
}

Token *Scanner__scan_space_token(Scanner *self, Source_Location *source_location, String *token_lexeme) {
    uint16_t count = 0;
    while (char_is_space(Scanner__peek_char(self))) {
        count = count + 1;
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
    return (Token *)Space_Token__create(source_location, token_lexeme, count);
}

Token *Scanner__scan_string_token(Scanner *self, Source_Location *source_location, String *token_lexeme) {
    if (Scanner__next_char(self) != '"') {
        Source_Location__error(source_location, String__create_from("Unexpected char"));
        panic();
    }
    String__append_char(token_lexeme, '"');

    String *value = String__create();

    while (true) {
        char next_char = Scanner__peek_char(self);
        if (char_is_end_of_line(next_char) || next_char == '\t') {
            return (Token *)Error_Token__create(source_location, token_lexeme);
        }

        String__append_char(token_lexeme, Scanner__next_char(self));

        if (next_char == '"') {
            return (Token *)String_Token__create(source_location, token_lexeme, value);
        }

        if (next_char == '\\') {
            next_char = Scanner__peek_char(self);
            if (char_is_end_of_line(next_char) || next_char == '\t') {
                return (Token *)Error_Token__create(source_location, token_lexeme);
            }

            String__append_char(token_lexeme, Scanner__next_char(self));

            next_char = escape_char_value(next_char);
            if (next_char == ((char)-1)) {
                return (Token *)Error_Token__create(source_location, token_lexeme);
            }
        }

        String__append_char(value, next_char);
    }
}

Token *Scanner__scan_token(Scanner *self) {
    Source_Location *source_location = Source_Location__create(self->source, self->current_line, self->current_column);
    String *token_lexeme = String__create();

    char next_char = Scanner__peek_char(self);

    if (char_is_identifier_start(next_char)) {
        return Scanner__scan_identifier_token(self, source_location, token_lexeme);
    }

    if (char_is_digit(next_char)) {
        return Scanner__scan_integer_token(self, source_location, token_lexeme);
    }

    if (char_is_space(next_char)) {
        return Scanner__scan_space_token(self, source_location, token_lexeme);
    }

    if (next_char == '\'') {
        return Scanner__scan_character_token(self, source_location, token_lexeme);
    }

    if (next_char == '\"') {
        return Scanner__scan_string_token(self, source_location, token_lexeme);
    }

    if (next_char == '\\') {
        return Scanner__scan_comment_token(self, source_location, token_lexeme);
    }

    if (next_char == '\n') {
        String__append_char(token_lexeme, Scanner__next_char(self));
        return (Token *)End_Of_Line_Token__create(source_location, token_lexeme);
    }

    if (next_char == '\0') {
        return (Token *)End_Of_File_Token__create(source_location, token_lexeme);
    }

    String__append_char(token_lexeme, Scanner__next_char(self));
    return (Token *)Other_Token__create(source_location, token_lexeme);
}

Token *Scanner__next_token(Scanner *self) {
    if (self->current_token->next_token == NULL) {
        self->current_token->next_token = Scanner__scan_token(self);
    }
    self->current_token = self->current_token->next_token;
    return self->current_token;
}

Token *Scanner__peek_token(Scanner *self, uint8_t offset) {
    Token *token = self->current_token;
    while (offset > 0) {
        if (token->next_token == NULL) {
            token->next_token = Scanner__scan_token(self);
        }
        token = token->next_token;
        offset = offset - 1;
    }
    return token;
}

Scanner *Scanner__create(Source *source) {
    Scanner *scanner = (Scanner *)malloc(sizeof(Scanner));
    scanner->source = source;
    scanner->current_char_index = 0;
    scanner->current_line = 1;
    scanner->current_column = 1;

    scanner->current_token = Scanner__scan_token(scanner);

    return scanner;
}