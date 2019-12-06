#include "Logging.h"
#include "Parser.h"
#include "Scanner.h"

#include <fstream>

using namespace std;

char *load_file(string filen_name);

std::ostream &operator<<(std::ostream &os, const Type *type);
std::ostream &operator<<(std::ostream &os, const Type &type);
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
            cout << setw(3) << setfill('0') << line << ": ";
        }
        cout << token;
    }

    auto first_statement = parse(first_token);

    auto statement = first_statement;
    while (statement != nullptr) {
        cout << statement << endl;
        statement = statement->next;
    }
}

char *load_file(string file_name) {
    auto file = ifstream(file_name);
    if (file.fail()) {
        ERROR(__FILE__, __LINE__, "Couldn't open file: " << file_name);
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

std::ostream &operator<<(std::ostream &os, const Type *type) {
    if (type) {
        os << *type;
    } else {
        os << SGR_ERROR << "Type::NULL" << SGR_RESET;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const Type &type) {
    switch (type.kind) {
    case Type::ARRAY: {
        os << '[' << type.array.item_type << ']';
        return os;
    }
    case Type::PROCEDURE: {
        os << '(';
        auto parameter = type.procedure.first_parameter;
        while (parameter != nullptr) {
            os << parameter->name << ": " << parameter->type;
            parameter = parameter->next;
            if (parameter != nullptr) {
                os << ", ";
            }
        }
        os << ") -> " << type.procedure.return_type;
        return os;
    }
    case Type::SIMPLE: {
        os << type.simple.name;
        return os;
    }
    case Type::TUPLE: {
        os << '(';
        auto member = type.tuple.first_member;
        while (member != nullptr) {
            os << member->name << ": " << member->type;
            member = member->next;
            if (member != nullptr) {
                os << ", ";
            }
        }
        os << ')';
        return os;
    }
    default:
        os << SGR_ERROR << "Type::" << type.kind << SGR_RESET;
        return os;
    }
}

std::ostream &operator<<(std::ostream &os, const Statement *statement) {
    if (statement) {
        os << *statement;
    } else {
        os << SGR_ERROR << "Statement::NULL" << SGR_RESET;
    }
    return os;
}

#define ALIGNMENT_SIZE 2

std::ostream &operator<<(std::ostream &os, const Statement &statement) {
    static int alignment = 0;
    os << setw(alignment * ALIGNMENT_SIZE) << setfill(' ') << "";
    switch (statement.kind) {
    case Statement::EXPRESSION: {
        os << statement.expression << endl;
        return os;
    }
    case Statement::PROCEDURE_DEFINITION: {
        os << statement.procedure_definition.name << " :: (";
        auto parameter = statement.procedure_definition.first_parameter;
        while (parameter != nullptr) {
            os << parameter->name << ": " << parameter->type;
            parameter = parameter->next;
            if (parameter != nullptr) {
                os << ", ";
            }
        }
        os << ")";
        if (statement.procedure_definition.return_type != nullptr) {
            os << " -> " << statement.procedure_definition.return_type;
        }
        os << " {" << endl;

        alignment += 1;
        auto procedure_statement = statement.procedure_definition.first_statement;
        while (procedure_statement != nullptr) {
            os << procedure_statement;
            procedure_statement = procedure_statement->next;
        }
        alignment -= 1;

        os << setw(alignment * ALIGNMENT_SIZE) << setfill(' ') << ""
           << "}" << endl;
        return os;
    }
    case Statement::RETURN: {
        os << "return " << statement.return_expression << endl;
        return os;
    }
    case Statement::STRUCT_DEFINITION: {
        os << statement.struct_definition.name << " :: struct {" << endl;
        auto member = statement.struct_definition.first_member;
        while (member) {
            os << "    " << member->name << ": " << member->type;
            if (member->default_value) {
                os << " = " << member->default_value;
            }
            os << endl;
            member = member->next;
        }
        os << setw(alignment * ALIGNMENT_SIZE) << setfill(' ') << ""
           << "}" << endl;
        return os;
    }
    case Statement::VARIABLE_DECLARATION: {
        os << statement.variable_declaration.name;
        if (statement.variable_declaration.type != nullptr) {
            os << ": " << statement.variable_declaration.type << " ";
        } else {
            os << " :";
        }
        os << "= " << statement.variable_declaration.value << endl;
        return os;
    }
    default:
        os << SGR_ERROR << "Statement::" << statement.kind << SGR_RESET << endl;
        return os;
    }
}

std::ostream &operator<<(std::ostream &os, const Expression *expression) {
    if (expression) {
        os << *expression;
    } else {
        os << SGR_ERROR << "Expression::NULL" << SGR_RESET;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const Expression &expression) {
    switch (expression.kind) {
    case Expression::ARRAY_ITEM:
        os << expression.array_item.array << '[' << expression.array_item.index << ']';
        return os;
    case Expression::BINARY: {
        os << SGR_BLACK << '(' << expression.binary.left_expression << ' ' << expression.binary.operator_token << ' ' << expression.binary.right_expression << SGR_BLACK << ')' << SGR_RESET;
        return os;
    }
    case Expression::CALL: {
        os << expression.call.callee << SGR_WHITE_BOLD << '(';
        auto argument = expression.call.first_argument;
        while (argument != nullptr) {
            if (argument->name != nullptr) {
                os << argument->name << " = ";
            }
            os << argument->value;
            argument = argument->next;
            if (argument != nullptr) {
                os << SGR_WHITE_BOLD << ", ";
            }
        }
        os << SGR_WHITE_BOLD << ')' << SGR_RESET;
        return os;
    }
    case Expression::LITERAL:
        os << expression.literal.value;
        return os;
    case Expression::MEMBER:
        os << expression.member.object << '.' << expression.member.name;
        return os;
    case Expression::VARIABLE:
        os << expression.variable.name;
        return os;
    case Expression::UNARY:
        os << SGR_BLACK << '(' << expression.unary.operator_token << expression.unary.expression << SGR_BLACK << ')' << SGR_RESET;
        return os;
    default:
        os << SGR_ERROR << "Expression::" << expression.kind << SGR_RESET;
        return os;
    }
}

std::ostream &operator<<(std::ostream &os, const Token *token) {
    if (token) {
        os << *token;
    } else {
        os << SGR_ERROR << "Token::NULL" << SGR_RESET;
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
        os << SGR_BLACK << token.lexeme->data << SGR_RESET << endl;
        return os;
    case Token::END_OF_LINE:
        os << SGR_BLACK << token.lexeme->data << SGR_RESET;
        return os;
    case Token::ERROR:
        os << SGR_ERROR << token.lexeme->data << SGR_RESET;
        return os;
    case Token::IDENTIFIER:
        os << (token.lexeme->data[0] <= 'Z' ? SGR_FAINT_YELLOW : SGR_RESET) << token.lexeme->data << SGR_RESET;
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
        os << SGR_RESET << token.lexeme->data;
        return os;
    case Token::STRING:
        os << SGR_GREEN << token.lexeme->data << SGR_RESET;
        return os;
    }
    return os;
}
