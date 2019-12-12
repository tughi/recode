#include "Generator.h"
#include "Logging.h"

#include <fstream>

using namespace std;

struct Context {
    ofstream file;
};

#define EMIT(code) context.file << code << endl

void emit_literal(Context &context, Token &token) {
    switch (token.kind) {
    case Token::INTEGER:
        EMIT("   mov $" << token.integer.value << ", %rax");
        break;
    default:
        WARNING(__FILE__, __LINE__, "Unsupported token type: " << token.kind);
        break;
    }
}

void emit_expression(Context &context, Expression &expression) {
    switch (expression.kind) {
    case Expression::BINARY: {
        emit_expression(context, *expression.binary.left_expression);
        EMIT("   push %rax");
        emit_expression(context, *expression.binary.right_expression);
        EMIT("   pop %rcx");
        if (expression.binary.operator_token->lexeme->equals("+")) {
            EMIT("   add %rcx, %rax");
        } else if (expression.binary.operator_token->lexeme->equals("-")) {
            EMIT("   xchg %rcx, %rax");
            EMIT("   sub %rcx, %rax");
        } else {
            ERROR(__FILE__, __LINE__, "Unsupported binary expression operator: " << expression.binary.operator_token->lexeme->data);
            exit(1);
        }

        break;
    }
    case Expression::LITERAL: {
        emit_literal(context, *expression.literal.value);
        break;
    }
    default:
        WARNING(__FILE__, __LINE__, "Unsupported expression type: " << expression.kind);
        break;
    }
}

void emit_statement(Context &context, Statement &statement) {
    switch (statement.kind) {
    case Statement::EXPRESSION:
        emit_expression(context, *statement.expression);
        break;
    default:
        WARNING(__FILE__, __LINE__, "Unsupported statement type: " << statement.kind);
        break;
    }
}

void generate(Statement *first_statement) {
    auto context = Context{
        file : ofstream("build/code.s")
    };
    EMIT("   .globl main");
    EMIT("main:");

    Statement *statement = first_statement;
    while (statement != nullptr) {
        emit_statement(context, *statement);
        statement = statement->next;
    }

    EMIT("   ret");
    context.file.close();
}
