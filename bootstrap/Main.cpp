#include "Scanner.h"

#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

char *load_file(string filen_name);

std::ostream &operator<<(std::ostream &os, const Token &token);

int main(int argc, char *argv[]) {
    auto source_file = string("../src/recode.code");
    auto source = Source(load_file(source_file));

    Token *token;
    int line = 0;

    do {
        token = scan_token(source);
        if (token->line != line) {
            if (line > 0) {
                cout << endl;
            }
            line = token->line;
            cout << setw(4) << line << ": ";
        }
        cout << *token;
    } while (token->type != Token::END_OF_FILE);
}

char *load_file(string file_name) {
    auto file = ifstream(file_name);
    file.seekg(0, ios::end);
    int file_size = file.tellg();
    if (file_size > 0) {
        auto buffer = new char[file_size + 1];
        file.seekg(0);
        file.read(buffer, file_size);
        buffer[file_size + 1] = 0;
        return buffer;
    } else {
        cout << "File not found" << endl;
        exit(1);
    }
    return new char[0];
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
    case Token::ERROR:
        os << '!' << token.lexeme->data << '!';
        return os;
    case Token::IDENTIFIER:
        os << token.lexeme->data;
        return os;
    case Token::INTEGER:
        os << token.integer.value;
        return os;
    case Token::KEYWORD:
        for (int i = 0; i < token.lexeme->length; i++) {
            cout << (char)toupper(token.lexeme->data[i]);
        }
        return os;
    case Token::OTHER:
        os << '_' << token.lexeme->data << '_';
        return os;
    case Token::SPACE:
        os << ' ';
        return os;
    case Token::STRING:
        os << token.lexeme->data;
        return os;
    case Token::TAB:
        os << "    ";
        return os;
    }
    return os;
}
