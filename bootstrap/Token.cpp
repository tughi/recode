#include "Token.h"

void Token::join_next() {
    if (this->next) {
        this->lexeme->append(*this->next->lexeme);
        this->next = this->next->next;
    }
}

Token *create(Token::Kind kind, String *lexeme, int line, int column) {
    return new Token{
        type : kind,
        lexeme : lexeme,
        line : line,
        column : column,
    };
}

Token *create_character(String *lexeme, int line, int column, char value) {
    auto token = create(Token::CHARACTER, lexeme, line, column);
    token->character.value = value;
    return token;
}

Token *create_comment(String *lexeme, int line, int column) {
    return create(Token::COMMENT, lexeme, line, column);
}

Token *create_end_of_file(String *lexeme, int line, int column) {
    return create(Token::END_OF_FILE, lexeme, line, column);
}

Token *create_end_of_line(String *lexeme, int line, int column) {
    return create(Token::END_OF_LINE, lexeme, line, column);
}

Token *create_error(String *lexeme, int line, int column) {
    return create(Token::ERROR, lexeme, line, column);
}

Token *create_identifier(String *lexeme, int line, int column) {
    return create(Token::IDENTIFIER, lexeme, line, column);
}

Token *create_integer(String *lexeme, int line, int column, int value) {
    auto token = create(Token::INTEGER, lexeme, line, column);
    token->integer.value = value;
    return token;
}

Token *create_keyword(String *lexeme, int line, int column) {
    return create(Token::KEYWORD, lexeme, line, column);
}

Token *create_other(String *lexeme, int line, int column) {
    return create(Token::OTHER, lexeme, line, column);
}

Token *create_space(String *lexeme, int line, int column, int count) {
    auto token = create(Token::SPACE, lexeme, line, column);
    token->space.count = count;
    return token;
}

Token *create_string(String *lexeme, int line, int column, String *value) {
    auto token = create(Token::STRING, lexeme, line, column);
    token->string.value = value;
    return token;
}
