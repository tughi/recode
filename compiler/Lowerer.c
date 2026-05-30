#include "Lowerer.h"
#include "Builtins.h"
#include "File.h"

typedef struct Lowerer {
    IR_Program *program;
    IR_Block *block;
    int32_t value_counter;
    IR_Value_List globals;
    IR_Value_List scope;
} Lowerer;

IR_Value *Lowerer__find_global(Lowerer *self, String *name) {
    for (size_t i = 0; i < self->globals.size; i++) {
        if (String__equals_string(self->globals.values[i]->name, name)) {
            return self->globals.values[i];
        }
    }
    pWriter__write__cstring(stderr_writer, "No IR global named: ");
    pWriter__write__string(stderr_writer, name);
    pWriter__end_line(stderr_writer);
    panic();
}

IR_Value *Lowerer__find_scope(Lowerer *self, String *name) {
    for (size_t i = 0; i < self->scope.size; i++) {
        if (String__equals_string(self->scope.values[i]->name, name)) {
            return self->scope.values[i];
        }
    }
    pWriter__write__cstring(stderr_writer, "No IR value in scope named: ");
    pWriter__write__string(stderr_writer, name);
    pWriter__end_line(stderr_writer);
    panic();
}

String *Lowerer__fresh_name(Lowerer *self) {
    self->value_counter++;
    String *name = String__create();
    String__append_int16_t(name, self->value_counter);
    return name;
}

IR_Type *Lowerer__lower_type(Lowerer *self, Checked_Type *type) {
    switch (type->kind) {
    case CHECKED_TYPE_KIND__BOOL:
        return IR_Type__get(IR_TYPE_KIND__BOOL);
    case CHECKED_TYPE_KIND__I8:
        return IR_Type__get(IR_TYPE_KIND__I8);
    case CHECKED_TYPE_KIND__I16:
        return IR_Type__get(IR_TYPE_KIND__I16);
    case CHECKED_TYPE_KIND__I32:
        return IR_Type__get(IR_TYPE_KIND__I32);
    case CHECKED_TYPE_KIND__I64:
        return IR_Type__get(IR_TYPE_KIND__I64);
    case CHECKED_TYPE_KIND__ISIZE:
        return IR_Type__get(IR_TYPE_KIND__ISIZE);
    case CHECKED_TYPE_KIND__U8:
        return IR_Type__get(IR_TYPE_KIND__U8);
    case CHECKED_TYPE_KIND__U16:
        return IR_Type__get(IR_TYPE_KIND__U16);
    case CHECKED_TYPE_KIND__U32:
        return IR_Type__get(IR_TYPE_KIND__U32);
    case CHECKED_TYPE_KIND__U64:
        return IR_Type__get(IR_TYPE_KIND__U64);
    case CHECKED_TYPE_KIND__USIZE:
        return IR_Type__get(IR_TYPE_KIND__USIZE);
    default:
        pWriter__write__cstring(stderr_writer, "Lowering not supported yet: type kind ");
        pWriter__write__int64(stderr_writer, type->kind);
        pWriter__end_line(stderr_writer);
        panic();
    }
}

IR_Value *Lowerer__lower_expression(Lowerer *self, Checked_Expression *expression) {
    switch (expression->kind) {
    case CHECKED_EXPRESSION_KIND__CALL: {
        Checked_Call_Expression *call_expression = (Checked_Call_Expression *)expression;
        if (call_expression->callee_expression->kind != CHECKED_EXPRESSION_KIND__SYMBOL) {
            pWriter__write__cstring(stderr_writer, "Lowering not supported yet: indirect call");
            pWriter__end_line(stderr_writer);
            panic();
        }
        Checked_Symbol *symbol = ((Checked_Symbol_Expression *)call_expression->callee_expression)->symbol;
        if (symbol->kind != CHECKED_SYMBOL_KIND__PROCEDURE) {
            pWriter__write__cstring(stderr_writer, "Lowering not supported yet: callee symbol kind ");
            pWriter__write__int64(stderr_writer, symbol->kind);
            pWriter__end_line(stderr_writer);
            panic();
        }
        IR_Value *callee = Lowerer__find_global(self, symbol->name);
        IR_Value_List arguments = {.values = NULL, .size = 0, .capacity = 0};
        for (Checked_Call_Argument *argument = call_expression->first_argument; argument != NULL; argument = argument->next_argument) {
            IR_Value_List__append(&arguments, Lowerer__lower_expression(self, argument->expression));
        }
        IR_Call_Instruction *instruction = IR_Call_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), callee);
        for (size_t i = 0; i < arguments.size; i++) {
            IR_Value_List__append(&instruction->super.operands, arguments.values[i]);
        }
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        return &instruction->super.result;
    }
    case CHECKED_EXPRESSION_KIND__INTEGER: {
        Checked_Integer_Expression *integer_expression = (Checked_Integer_Expression *)expression;
        IR_Const_Instruction *instruction = IR_Const_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), integer_expression->value);
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        return &instruction->super.result;
    }
    case CHECKED_EXPRESSION_KIND__SYMBOL: {
        Checked_Symbol *symbol = ((Checked_Symbol_Expression *)expression)->symbol;
        if (symbol->kind != CHECKED_SYMBOL_KIND__PROCEDURE_PARAMETER) {
            pWriter__write__cstring(stderr_writer, "Lowering not supported yet: symbol kind ");
            pWriter__write__int64(stderr_writer, symbol->kind);
            pWriter__end_line(stderr_writer);
            panic();
        }
        return Lowerer__find_scope(self, symbol->name);
    }
    default:
        pWriter__write__cstring(stderr_writer, "Lowering not supported yet: expression kind ");
        pWriter__write__int64(stderr_writer, expression->kind);
        pWriter__end_line(stderr_writer);
        panic();
    }
}

void Lowerer__lower_statement(Lowerer *self, Checked_Statement *statement) {
    switch (statement->kind) {
    case CHECKED_STATEMENT_KIND__BLOCK: {
        Checked_Block_Statement *block_statement = (Checked_Block_Statement *)statement;
        Checked_Statement *child_statement = block_statement->statements->first_statement;
        while (child_statement != NULL) {
            Lowerer__lower_statement(self, child_statement);
            child_statement = child_statement->next_statement;
        }
        break;
    }
    case CHECKED_STATEMENT_KIND__RETURN: {
        Checked_Return_Statement *return_statement = (Checked_Return_Statement *)statement;
        IR_Value *value = NULL;
        if (return_statement->expression != NULL) {
            value = Lowerer__lower_expression(self, return_statement->expression);
        }
        IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Ret_Instruction__create(value));
        break;
    }
    default:
        pWriter__write__cstring(stderr_writer, "Lowering not supported yet: statement kind ");
        pWriter__write__int64(stderr_writer, statement->kind);
        pWriter__end_line(stderr_writer);
        panic();
    }
}

void Lowerer__declare_procedure(Lowerer *self, Checked_Procedure_Symbol *procedure_symbol) {
    Checked_Procedure_Type *checked_procedure_type = procedure_symbol->procedure_type;
    IR_Type *return_type = Lowerer__lower_type(self, checked_procedure_type->return_type);

    size_t parameter_count = 0;
    for (Checked_Procedure_Parameter *parameter = checked_procedure_type->first_parameter; parameter != NULL; parameter = parameter->next_parameter) {
        parameter_count++;
    }
    IR_Type **parameter_types = parameter_count > 0 ? (IR_Type **)malloc(parameter_count * sizeof(IR_Type *)) : NULL;
    size_t parameter_index = 0;
    for (Checked_Procedure_Parameter *parameter = checked_procedure_type->first_parameter; parameter != NULL; parameter = parameter->next_parameter) {
        parameter_types[parameter_index++] = Lowerer__lower_type(self, parameter->type);
    }

    IR_Type *procedure_type = (IR_Type *)IR_Procedure_Type__create(parameter_types, parameter_count, return_type);
    IR_Procedure *procedure = IR_Procedure__create(procedure_symbol->super.name, (IR_Type *)IR_Pointer_Type__create(procedure_type), return_type);
    IR_Program__append_procedure(self->program, procedure);
    IR_Value_List__append(&self->globals, &procedure->value);

    parameter_index = 0;
    for (Checked_Procedure_Parameter *parameter = checked_procedure_type->first_parameter; parameter != NULL; parameter = parameter->next_parameter) {
        IR_Value_List__append(&procedure->parameters, IR_Value__create(IR_VALUE_KIND__PARAMETER, parameter->name, parameter_types[parameter_index++]));
    }
}

void Lowerer__define_procedure(Lowerer *self, Checked_Procedure_Symbol *procedure_symbol) {
    if (procedure_symbol->checked_block_statement == NULL) {
        return;
    }

    IR_Procedure *procedure = (IR_Procedure *)Lowerer__find_global(self, procedure_symbol->super.name);

    self->value_counter = 0;
    self->scope.size = 0;
    for (size_t i = 0; i < procedure->parameters.size; i++) {
        IR_Value_List__append(&self->scope, procedure->parameters.values[i]);
    }

    IR_Block *block = IR_Block__create(1);
    IR_Procedure__append_block(procedure, block);
    self->block = block;

    Lowerer__lower_statement(self, procedure_symbol->checked_block_statement);
}

bool Checked_Procedure_Symbol__is_lowerable(Checked_Procedure_Symbol *procedure_symbol) {
    return !procedure_symbol->parsed_procedure_statement->is_external;
}

IR_Program *lower(Checked_Source *checked_source) {
    Lowerer lowerer;
    lowerer.program = IR_Program__create();
    lowerer.block = NULL;
    lowerer.value_counter = 0;
    lowerer.globals = (IR_Value_List){.values = NULL, .size = 0, .capacity = 0};
    lowerer.scope = (IR_Value_List){.values = NULL, .size = 0, .capacity = 0};

    for (Checked_Symbol *symbol = checked_source->symbols->first_symbol; symbol != NULL; symbol = symbol->next_symbol) {
        if (symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE && Checked_Procedure_Symbol__is_lowerable((Checked_Procedure_Symbol *)symbol)) {
            Lowerer__declare_procedure(&lowerer, (Checked_Procedure_Symbol *)symbol);
        }
    }

    for (Checked_Symbol *symbol = checked_source->symbols->first_symbol; symbol != NULL; symbol = symbol->next_symbol) {
        if (symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE && Checked_Procedure_Symbol__is_lowerable((Checked_Procedure_Symbol *)symbol)) {
            Lowerer__define_procedure(&lowerer, (Checked_Procedure_Symbol *)symbol);
        }
    }

    return lowerer.program;
}
