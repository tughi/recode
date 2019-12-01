#include "Parser.h"
#include "Scanner.h"

#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

char *load_file(string filen_name);

std::ostream &operator<<(std::ostream &os, const Statement *statement);
std::ostream &operator<<(std::ostream &os, const Statement &statement);
std::ostream &operator<<(std::ostream &os, const Expression *expression);
std::ostream &operator<<(std::ostream &os, const Expression &expression);
std::ostream &operator<<(std::ostream &os, const Token *token);
std::ostream &operator<<(std::ostream &os, const Token &token);

int main(int argc, char *argv[]) {
    auto source_file = string("../src/Source.code");
    auto source = Source(load_file(source_file));

    auto first_token = scan(source);

    auto token = first_token;
    for (int line = 0; token != nullptr; token = token->next) {
        if (token->line != line) {
            if (line > 0) {
                cout << endl;
            }
            line = token->line;
            cout << setw(4) << line << ": ";
        }
        cout << token;
    }

    cout << parse(first_token) << endl;
}

const char *SGR_RESET = "\033[0m";
const char *SGR_ERROR = "\033[42;41m";
const char *SGR_BLACK = "\033[30m";
const char *SGR_CYAN = "\033[36m";
const char *SGR_DEFAULT = "\033[39m";
const char *SGR_GREEN = "\033[32m";
const char *SGR_WHITE_BOLD = "\033[37;1m";
const char *SGR_YELLOW = "\033[33m";
const char *SGR_FAINT_DEFAULT = "\033[2;39m";
const char *SGR_FAINT_YELLOW = "\033[2;33m";

char *load_file(string file_name) {
    auto file = ifstream(file_name);
    if (file.fail()) {
        cout << SGR_ERROR << "Couldn't open file: " << file_name << SGR_RESET << endl;
        exit(1);
    }
    file.seekg(0, ios::end);
    int file_size = file.tellg();
    if (file_size > 0) {
        auto buffer = new char[file_size + 1];
        file.seekg(0);
        file.read(buffer, file_size);
        buffer[file_size] = 0;
        return buffer;
    }
    return new char[0];
}

std::ostream &operator<<(std::ostream &os, const Statement *statement) {
    if (statement) {
        os << *statement;
    } else {
        os << SGR_ERROR << __FILE__ << ':' << __LINE__ << " -- NULL statement" << SGR_RESET;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const Statement &statement) {
    switch (statement.kind) {
    case Statement::STRUCT_DECLARATION: 
        os << statement.struct_declaration.name;
        return os;
    default:
        os << SGR_ERROR << __FILE__ << ':' << __LINE__ << " -- Unsupported statement kind: " << statement.kind << SGR_RESET;
        return os;
    }
}

std::ostream &operator<<(std::ostream &os, const Expression *expression) {
    if (expression) {
        os << *expression;
    } else {
        os << SGR_ERROR << __FILE__ << ':' << __LINE__ << " -- NULL expression" << SGR_RESET;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const Expression &expression) {
    switch (expression.kind) {
    case Expression::BINARY: {
        os << SGR_BLACK << '(' << expression.binary.left_expression << ' ' << expression.binary.operator_token << ' ' << expression.binary.right_expression << SGR_BLACK << ')' << SGR_RESET;
        return os;
    }
    case Expression::LITERAL:
        os << expression.literal.value;
        return os;
    case Expression::VARIABLE:
        os << expression.variable.name;
        return os;
    case Expression::UNARY:
        os << SGR_BLACK << '(' << expression.unary.operator_token << expression.unary.expression << SGR_BLACK << ')' << SGR_RESET;
        return os;
    default:
        os << SGR_ERROR << __FILE__ << ':' << __LINE__ << " -- Unsupported expression kind: " << expression.kind << SGR_RESET;
        return os;
    }
}

std::ostream &operator<<(std::ostream &os, const Token *token) {
    if (token) {
        os << *token;
    } else {
        os << SGR_ERROR << "NULL token" << SGR_RESET;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    switch (token.type) {
    case Token::CHARACTER:
        os << SGR_GREEN << token.lexeme->data << SGR_RESET;
        return os;
    case Token::COMMENT:
        os << SGR_FAINT_DEFAULT << token.lexeme->data << SGR_RESET;
        return os;
    case Token::END_OF_FILE:
        os << SGR_BLACK << "<<EOF>>" << SGR_RESET << endl;
        return os;
    case Token::END_OF_LINE:
        os << SGR_BLACK << "<EOL>" << SGR_RESET;
        return os;
    case Token::ERROR:
        os << SGR_ERROR << token.lexeme->data << SGR_RESET;
        return os;
    case Token::IDENTIFIER:
        os << (token.lexeme->data[0] <= 'Z' ? SGR_FAINT_YELLOW : SGR_DEFAULT) << token.lexeme->data << SGR_RESET;
        return os;
    case Token::INTEGER:
        os << SGR_CYAN << token.lexeme->data << SGR_RESET;
        return os;
    case Token::KEYWORD:
        os << SGR_YELLOW << token.lexeme->data << SGR_RESET;
        return os;
    case Token::OTHER:
        os << SGR_WHITE_BOLD << token.lexeme->data << SGR_RESET;
        return os;
    case Token::SPACE:
        os << ' ';
        return os;
    case Token::STRING:
        os << SGR_GREEN << token.lexeme->data << SGR_RESET;
        return os;
    case Token::TAB:
        os << "    ";
        return os;
    }
    return os;
}
