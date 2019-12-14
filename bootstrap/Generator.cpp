#include "Generator.h"
#include "Logging.h"

#include <fstream>

using namespace std;

std::ostream &operator<<(std::ostream &os, const String *string) {
    if (string != nullptr) {
        os << string->data;
    } else {
        os << SGR_ERROR << ":String:" << SGR_RESET;
    }
    return os;
}

struct Local {
    String *name;
    int name_suffix;
    String *unique_name;
};

std::ostream &operator<<(std::ostream &os, const Local *local) {
    if (local != nullptr) {
        os << local->unique_name;
    } else {
        os << SGR_ERROR << ":Local:" << SGR_RESET;
    }
    return os;
}

struct LocalList {
    struct Item {
        Local *local;
        Item *next;
    };
    Item *first_item = nullptr;
    Item *last_item = nullptr;
};

LocalList::Item *append(LocalList &list, Local *local) {
    auto item = new LocalList::Item{local : local, next : nullptr};
    if (list.first_item == nullptr) {
        list.first_item = item;
    } else {
        list.last_item->next = item;
    }
    list.last_item = item;
    return item;
}

struct Context {
    ofstream file;
    LocalList locals;
};

Local *create_local(Context &context, String *name) {
    int name_suffix = -1;
    bool retry;
    do {
        retry = false;
        auto local_item = context.locals.first_item;
        while (local_item != nullptr) {
            if (local_item->local->name_suffix == name_suffix && local_item->local->name->equals(name->data)) {
                name_suffix += 1;
                retry = true;
                break;
            }
            local_item = local_item->next;
        }
    } while (retry);

    auto unique_name = new String(name->data);
    auto suffix = name_suffix;
    while (suffix > 0) {
        unique_name->append(suffix % 10 + '0');
        suffix /= 10;
    }
    if (name_suffix != -1) {
        if (name_suffix < 100) {
            unique_name->append('0');
        }
        if (name_suffix < 10) {
            unique_name->append('0');
        }
        if (name_suffix == 0) {
            unique_name->append('0');
        }
    }

    auto local = new Local{
        name : name,
        name_suffix : name_suffix,
        unique_name : unique_name,
    };

    append(context.locals, local);

    return local;
}

Local *create_temp_local(Context &context) {
    static auto name = new String("temp");
    return create_local(context, name);
}

Local *get_local(Context &context, String *name) {
    auto list_item = context.locals.first_item;
    while (list_item != nullptr && !list_item->local->name->equals(name->data)) {
        list_item = list_item->next;
    }
    return list_item != nullptr ? list_item->local : nullptr;
}

#define EMIT(code) context.file << code
#define EMIT_LINE(code) EMIT(code) << endl

Local *emit_literal(Context &context, Local *destination, Token *token) {
    switch (token->kind) {
    case Token::INTEGER:
        EMIT_LINE("  %" << destination << " = add i32 " << token->integer.value << ", 0");
        break;
    default:
        WARNING(__FILE__, __LINE__, "Unsupported token type: " << token->kind);
        break;
    }
    return destination;
}

Local *emit_expression(Context &context, Local *destination, Expression *expression) {
    switch (expression->kind) {
    case Expression::BINARY: {
        auto left_local = emit_expression(context, create_temp_local(context), expression->binary.left_expression);
        auto right_local = emit_expression(context, create_temp_local(context), expression->binary.right_expression);
        auto operation = (String *)nullptr;
        if (expression->binary.operator_token->lexeme->equals("+")) {
            static auto add = new String("add");
            operation = add;
        } else if (expression->binary.operator_token->lexeme->equals("-")) {
            static auto sub = new String("sub");
            operation = sub;
        } else if (expression->binary.operator_token->lexeme->equals("*")) {
            static auto mull = new String("mul");
            operation = mull;
        } else if (expression->binary.operator_token->lexeme->equals("/")) {
            static auto div = new String("sdiv");
            operation = div;
        } else {
            ERROR(__FILE__, __LINE__, "Unsupported binary expression operator: " << expression->binary.operator_token->lexeme);
            exit(1);
        }
        EMIT_LINE("  %" << destination << " = " << operation << " i32 %" << left_local << ", %" << right_local);
        break;
    }
    case Expression::CALL: {
        auto procedure = get_local(context, expression->call.callee->variable.name->lexeme);
        if (procedure == nullptr) {
            ERROR(__FILE__, __LINE__, "Undefined procedure: " << expression->call.callee->variable.name->lexeme);
            exit(1);
        }
        auto procedure_arguments = LocalList{};
        auto argument = expression->call.first_argument;
        while (argument != nullptr) {
            auto procedure_argument = create_temp_local(context);
            append(procedure_arguments, procedure_argument);
            emit_expression(context, procedure_argument, argument->value);
            argument = argument->next;
        }
        EMIT("  %" << destination << " = call i32 @" << procedure << "(");
        auto procedure_arguments_item = procedure_arguments.first_item;
        while (procedure_arguments_item != nullptr) {
            EMIT("i32 %" << procedure_arguments_item->local);
            procedure_arguments_item = procedure_arguments_item->next;
            if (procedure_arguments_item != nullptr) {
                EMIT(", ");
            }
        }
        EMIT_LINE(")");
        break;
    }
    case Expression::LITERAL: {
        emit_literal(context, destination, expression->literal.value);
        break;
    }
    case Expression::VARIABLE: {
        EMIT_LINE("  %" << destination << " = add i32 %" << get_local(context, expression->variable.name->lexeme) << ", 0");
        break;
    }
    default:
        WARNING(__FILE__, __LINE__, "Unsupported expression type: " << expression->kind);
        break;
    }

    return destination;
}

void emit_statement(Context &context, Statement &statement) {
    switch (statement.kind) {
    case Statement::RETURN: {
        auto result = emit_expression(context, create_temp_local(context), statement.return_expression);
        EMIT_LINE("  ret i32 %" << result);
        break;
    }
    case Statement::PROCEDURE_DEFINITION: {
        auto procedure_name = create_local(context, statement.procedure_definition.name->literal.value->lexeme);

        auto outer_locals_last = context.locals.last_item;

        EMIT("define i32 @" << procedure_name << "(");
        auto parameter = statement.procedure_definition.first_parameter;
        while (parameter != nullptr) {
            auto name = create_local(context, parameter->name->lexeme);
            EMIT("i32 %" << name);
            parameter = parameter->next;
            if (parameter != nullptr) {
                EMIT(", ");
            }
        }
        EMIT_LINE(") {");

        auto body_statement = statement.procedure_definition.first_statement;
        while (body_statement != nullptr) {
            emit_statement(context, *body_statement);
            body_statement = body_statement->next;
        }

        EMIT_LINE("}");

        outer_locals_last->next = nullptr;
        context.locals.last_item = outer_locals_last;

        break;
    }
    default:
        WARNING(__FILE__, __LINE__, "Unsupported statement type: " << statement.kind);
        break;
    }
}

void generate(Statement *first_statement) {
    auto context = Context{
        file : ofstream("build/code.ll")
    };

    Statement *statement = first_statement;
    while (statement != nullptr) {
        emit_statement(context, *statement);
        statement = statement->next;
    }

    context.file.close();
}
