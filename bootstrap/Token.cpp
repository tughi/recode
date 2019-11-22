#include "Token.h"

Token::Token(Token::Type type, std::string lexeme, int line, int column) {
    this->type = type;
    this->lexeme = lexeme;
    this->line = line;
    this->column = column;
}

Token::Token(int integer, std::string lexeme, int line, int column) : Token(INTEGER, lexeme, line, column) {
    this->integer = integer;
}
