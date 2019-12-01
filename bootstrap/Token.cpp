#include "Token.h"

Token::Token(Token::Kind kind, String *lexeme, int line, int column) {
    this->type = kind;
    this->lexeme = lexeme;
    this->line = line;
    this->column = column;
}

Token::Token(char value, String *lexeme, int line, int column) : Token(CHARACTER, lexeme, line, column) {
    this->character.value = value;
}

Token::Token(int value, String *lexeme, int line, int column) : Token(INTEGER, lexeme, line, column) {
    this->integer.value = value;
}

Token::Token(String *value, String *lexeme, int line, int column) : Token(STRING, lexeme, line, column) {
    this->string.value = value;
}

void Token::join_next() {
    if (this->next) {
        this->lexeme->append(*this->next->lexeme);
        this->next = this->next->next;
    }
}
