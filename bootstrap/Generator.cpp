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
    bool is_pointer;
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

struct Loop {
    Local *loop_end;
    bool has_break;
    Loop *parent;
};

struct Context {
    ofstream *file;
    LocalList locals;
    Loop *loop;
};

Context *clone(Context &context) {
    auto new_context = new Context();
    new_context->file = context.file;

    auto locals_item = context.locals.first_item;
    while (locals_item != nullptr) {
        append(new_context->locals, locals_item->local);
        locals_item = locals_item->next;
    }

    return new_context;
}

Local *create_local(Context &context, String *name, int name_suffix) {
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
    if (name_suffix != -1) {
        unique_name->append('.');
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
    if (name_suffix >= 0) {
        unique_name->append_int(name_suffix);
    }

    auto local = new Local{
        name : name,
        name_suffix : name_suffix,
        unique_name : unique_name,
    };

    append(context.locals, local);

    return local;
}

Local *create_local(Context &context, String *name) {
    return create_local(context, name, -1);
}

Local *create_temp_local(Context &context) {
    static auto name = new String("");
    return create_local(context, name, 0);
}

Local *get_local(Context &context, String *name) {
    auto list_item = context.locals.first_item;
    while (list_item != nullptr && !list_item->local->name->equals(name->data)) {
        list_item = list_item->next;
    }
    return list_item != nullptr ? list_item->local : nullptr;
}

#define EMIT(code) *context.file << code
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
            EMIT_LINE("  %" << destination << " = add i32 %" << left_local << ", %" << right_local);
        } else if (expression->binary.operator_token->lexeme->equals("-")) {
            EMIT_LINE("  %" << destination << " = sub i32 %" << left_local << ", %" << right_local);
        } else if (expression->binary.operator_token->lexeme->equals("*")) {
            EMIT_LINE("  %" << destination << " = mul i32 %" << left_local << ", %" << right_local);
        } else if (expression->binary.operator_token->lexeme->equals("/")) {
            EMIT_LINE("  %" << destination << " = sdiv i32 %" << left_local << ", %" << right_local);
        } else if (expression->binary.operator_token->lexeme->equals("<")) {
            EMIT_LINE("  %" << destination << " = icmp slt i32 %" << left_local << ", %" << right_local);
        } else if (expression->binary.operator_token->lexeme->equals(">")) {
            EMIT_LINE("  %" << destination << " = icmp sgt i32 %" << left_local << ", %" << right_local);
        } else if (expression->binary.operator_token->lexeme->equals("==")) {
            EMIT_LINE("  %" << destination << " = icmp eq i32 %" << left_local << ", %" << right_local);
        } else {
            ERROR(__FILE__, __LINE__, "Unsupported binary expression operator: " << expression->binary.operator_token->lexeme);
            exit(1);
        }
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
        auto variable = get_local(context, expression->variable.name->lexeme);
        if (variable->is_pointer) {
            EMIT_LINE("  %" << destination << " = load i32, i32* %" << variable << ", align 4");
        } else {
            EMIT_LINE("  %" << destination << " = add i32 %" << variable << ", 0");
        }
        break;
    }
    default:
        WARNING(__FILE__, __LINE__, "Unsupported expression type: " << expression->kind);
        break;
    }

    return destination;
}

void emit_statement(Context &context, Statement *statement) {
    switch (statement->kind) {
    case Statement::ASSIGNMENT: {
        auto variable = get_local(context, statement->assignment.destination->variable.name->lexeme);
        auto value = emit_expression(context, create_temp_local(context), statement->variable_declaration.value);
        EMIT_LINE("  store i32 %" << value << ", i32* %" << variable << ", align 4");
        break;
    }
    case Statement::BLOCK: {
        auto block_statement = statement->block.first_statement;
        while (block_statement != nullptr) {
            emit_statement(context, block_statement);
            block_statement = block_statement->next;
        }
        break;
    }
    case Statement::BREAK: {
        EMIT_LINE("  br label %" << context.loop->loop_end);
        context.loop->has_break = true;
        break;
    }
    case Statement::IF: {
        auto if_cond = emit_expression(context, create_local(context, new String("if_cond"), 0), statement->if_.condition);
        auto if_true = create_local(context, new String("if_true"), 0);
        auto if_false = create_local(context, new String("if_false"), 0);
        auto if_end = create_local(context, new String("if_end"), 0);
        EMIT_LINE("  br i1 %" << if_cond << ", label %" << if_true << ", label %" << (statement->if_.false_block != nullptr ? if_false : if_end));

        EMIT_LINE(if_true << ":");
        emit_statement(context, statement->if_.true_block);
        EMIT_LINE("  br label %" << if_end);

        if (statement->if_.false_block != nullptr) {
            EMIT_LINE(if_false << ":");
            emit_statement(context, statement->if_.false_block);
            EMIT_LINE("  br label %" << if_end);
        }

        EMIT_LINE(if_end << ":");
        break;
    }
    case Statement::LOOP: {
        auto loop_start = create_local(context, new String("loop_start"), 0);
        auto loop_end = create_local(context, new String("loop_end"), 0);
        EMIT_LINE("  br label %" << loop_start);
        EMIT_LINE(loop_start << ":");
        auto loop = new Loop{
            loop_end : loop_end,
            has_break : false,
            parent : context.loop,
        };
        context.loop = loop;
        emit_statement(context, statement->loop.block);
        context.loop = loop->parent;
        EMIT_LINE("  br label %" << loop_start);
        if (loop->has_break) {
            EMIT_LINE(loop_end << ":");
        }
        break;
    }
    case Statement::PROCEDURE_DEFINITION: {
        auto procedure_name = create_local(context, statement->procedure_definition.name->literal.value->lexeme);

        auto procedure_context = clone(context);

        EMIT("define i32 @" << procedure_name << "(");
        auto parameter = statement->procedure_definition.first_parameter;
        while (parameter != nullptr) {
            auto name = create_local(*procedure_context, parameter->name->lexeme);
            EMIT("i32 %" << name);
            parameter = parameter->next;
            if (parameter != nullptr) {
                EMIT(", ");
            }
        }
        EMIT_LINE(") {");

        auto body_statement = statement->procedure_definition.first_statement;
        while (body_statement != nullptr) {
            emit_statement(*procedure_context, body_statement);
            body_statement = body_statement->next;
        }

        EMIT_LINE("}");

        break;
    }
    case Statement::RETURN: {
        auto result = emit_expression(context, create_temp_local(context), statement->return_expression);
        EMIT_LINE("  ret i32 %" << result);
        break;
    }
    case Statement::VARIABLE_DECLARATION: {
        auto variable = create_local(context, statement->variable_declaration.name->variable.name->lexeme);
        variable->is_pointer = true;
        EMIT_LINE("  %" << variable << " = alloca i32, align 4");
        auto value = emit_expression(context, create_temp_local(context), statement->variable_declaration.value);
        EMIT_LINE("  store i32 %" << value << ", i32* %" << variable << ", align 4");
        break;
    }
    default:
        EMIT_LINE("  %" << create_local(context, new String("nop")) << " = add i1 0, 0");
        WARNING(__FILE__, __LINE__, "Unsupported statement type: " << statement->kind);
        break;
    }
}

void generate(Statement *first_statement) {
    auto context = Context{
        file : new ofstream("build/code.ll")
    };

    Statement *statement = first_statement;
    while (statement != nullptr) {
        emit_statement(context, statement);
        statement = statement->next;
    }

    context.file->close();
}
