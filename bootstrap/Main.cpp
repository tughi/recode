#include "Scanner.h"

#include <iomanip>
#include <iostream>

using namespace std;

std::ostream &operator<<(std::ostream &os, const Token &token);

int main() {
    Token *token;
    int line = 0;

    do {
        token = scan_token();
        if (token->line != line) {
            if (line > 0) {
                cout << endl;
            }
            line = token->line;
            cout << setw(4) << line << ": ";
        }
        cout << *token << " ";
    } while (token->type != Token::END_OF_FILE);
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    switch (token.type) {
    case Token::CHARACTER:
        os << token.lexeme->data;
        return os;
    case Token::END_OF_FILE:
        os << "<<EOF>>";
        return os;
    case Token::END_OF_LINE:
        os << "<EOL>";
        return os;
    case Token::ENUM:
        os << token.lexeme->data;
        return os;
    case Token::IDENTIFIER:
        os << token.lexeme->data;
        return os;
    case Token::INTEGER:
        os << token.integer.value;
        return os;
    case Token::OPERATOR:
        os << token.lexeme->data;
        return os;
    case Token::STRING:
        os << token.lexeme->data;
        return os;
    case Token::STRUCT:
        os << token.lexeme->data;
        return os;
    default:
        os << "-?-?-?-?-?-?-?-?-?-?-?-?-?-?-";
        return os;
    }
}
