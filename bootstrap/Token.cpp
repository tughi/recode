#include "Token.h"

Token::Token(Token::Type type, String *lexeme, int line, int column) {
    this->type = type;
    this->lexeme = lexeme;
    this->line = line;
    this->column = column;
}

Token::Token(char character, String *lexeme, int line, int column) : Token(INTEGER, lexeme, line, column) {
    this->character = character;
}

Token::Token(int integer, String *lexeme, int line, int column) : Token(CHAR, lexeme, line, column) {
    this->integer = integer;
}

Token::Token(String *string, String *lexeme, int line, int column) : Token(STRING, lexeme, line, column) {
    this->string = string;
}
