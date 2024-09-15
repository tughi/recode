/* Copyright (C) 2024 Stefan Selariu */

#include "Header_Scanner.h"

char Header_Scanner__peek_char(Header_Scanner *self) {
    return self->source->content[self->current_char_index];
}

char Header_Scanner__next_char(Header_Scanner *self) {
    char next_char = Header_Scanner__peek_char(self);
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

Token *Header_Scanner__scan_comment_token(Header_Scanner *self, Source_Location *source_location, String *token_lexeme) {
    do {
        while (Header_Scanner__peek_char(self) != '*') {
            String__append_char(token_lexeme, Header_Scanner__next_char(self));
        }
        String__append_char(token_lexeme, Header_Scanner__next_char(self));
    } while (Header_Scanner__peek_char(self) != '/');
    String__append_char(token_lexeme, Header_Scanner__next_char(self));
    return (Token *)Comment_Token__create(source_location, token_lexeme);
}

bool char_is_identifier_start(char c);

bool char_is_identifier_letter(char c);

Token *Header_Scanner__scan_identifier_token(Header_Scanner *self, Source_Location *source_location, String *token_lexeme) {
    while (char_is_identifier_letter(Header_Scanner__peek_char(self))) {
        String__append_char(token_lexeme, Header_Scanner__next_char(self));
    }
    return (Token *)Identifier_Token__create(source_location, token_lexeme);
}

bool char_is_space(char c);

Token *Header_Scanner__scan_space_token(Header_Scanner *self, Source_Location *source_location, String *token_lexeme) {
    uint16_t count = 0;
    while (char_is_space(Header_Scanner__peek_char(self))) {
        count = count + 1;
        String__append_char(token_lexeme, Header_Scanner__next_char(self));
    }
    return (Token *)Space_Token__create(source_location, token_lexeme, count);
}

Token *Header_Scanner__scan_string_token(Header_Scanner *self, Source_Location *source_location, String *token_lexeme) {
    if (Header_Scanner__next_char(self) != '"') {
        Source_Location__error(source_location, String__create_from("Unexpected char"));
        abort();
    }
    String__append_char(token_lexeme, '"');

    String *value = String__create();

    while (true) {
        char next_char = Header_Scanner__peek_char(self);
        if (char_is_end_of_line(next_char) || next_char == '\t') {
            return (Token *)Error_Token__create(source_location, token_lexeme);
        }

        String__append_char(token_lexeme, Header_Scanner__next_char(self));

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

Token *Header_Scanner__scan_token(Header_Scanner *self) {
    Source_Location *source_location = Source_Location__create(self->source, self->current_line, self->current_column);
    String *token_lexeme = String__create();

    char next_char = Header_Scanner__peek_char(self);

    if (char_is_identifier_start(next_char)) {
        return Header_Scanner__scan_identifier_token(self, source_location, token_lexeme);
    }

    if (char_is_space(next_char)) {
        return Header_Scanner__scan_space_token(self, source_location, token_lexeme);
    }

    if (next_char == '\"') {
        return Header_Scanner__scan_string_token(self, source_location, token_lexeme);
    }

    if (next_char == '/') {
        String__append_char(token_lexeme, Header_Scanner__next_char(self));
        if (Header_Scanner__peek_char(self) == '*') {
            String__append_char(token_lexeme, Header_Scanner__next_char(self));
            return Header_Scanner__scan_comment_token(self, source_location, token_lexeme);
        }
        /* not a comment */
        return (Token *)Other_Token__create(source_location, token_lexeme);
    }

    if (next_char == '\n') {
        String__append_char(token_lexeme, Header_Scanner__next_char(self));
        return (Token *)End_Of_Line_Token__create(source_location, token_lexeme);
    }

    if (next_char == '\0') {
        return (Token *)End_Of_File_Token__create(source_location, token_lexeme);
    }

    String__append_char(token_lexeme, Header_Scanner__next_char(self));
    return (Token *)Other_Token__create(source_location, token_lexeme);
}

Token *Header_Scanner__next_token(Header_Scanner *self) {
    if (self->current_token->next_token == NULL) {
        self->current_token->next_token = Header_Scanner__scan_token(self);
    }
    self->current_token = self->current_token->next_token;
    return self->current_token;
}

Token *Header_Scanner__peek_token(Header_Scanner *self, uint8_t offset) {
    Token *token = self->current_token;
    while (offset > 0) {
        if (token->next_token == NULL) {
            token->next_token = Header_Scanner__scan_token(self);
        }
        token = token->next_token;
        offset = offset - 1;
    }
    return token;
}

Header_Scanner *Header_Scanner__create(Source *source) {
    Header_Scanner *scanner = (Header_Scanner *)malloc(sizeof(Header_Scanner));
    scanner->source = source;
    scanner->current_char_index = 0;
    scanner->current_line = 1;
    scanner->current_column = 1;

    scanner->current_token = Header_Scanner__scan_token(scanner);

    return scanner;
}
