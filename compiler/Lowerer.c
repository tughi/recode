#include "Lowerer.h"
#include "Builtins.h"
#include "File.h"

typedef struct Lowerer {
    IR_Program *program;
    IR_Block *block;
    int32_t value_counter;
} Lowerer;

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
    case CHECKED_EXPRESSION_KIND__INTEGER: {
        Checked_Integer_Expression *integer_expression = (Checked_Integer_Expression *)expression;
        IR_Instruction *instruction = IR_Instruction__create_const(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), integer_expression->value);
        IR_Block__append_instruction(self->block, instruction);
        return &instruction->result;
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
        IR_Block__append_instruction(self->block, IR_Instruction__create_ret(value));
        break;
    }
    default:
        pWriter__write__cstring(stderr_writer, "Lowering not supported yet: statement kind ");
        pWriter__write__int64(stderr_writer, statement->kind);
        pWriter__end_line(stderr_writer);
        panic();
    }
}

void Lowerer__lower_procedure(Lowerer *self, Checked_Procedure_Symbol *procedure_symbol) {
    IR_Type *return_type = Lowerer__lower_type(self, procedure_symbol->procedure_type->return_type);
    IR_Procedure *procedure = IR_Procedure__create(procedure_symbol->procedure_name, return_type);
    IR_Program__append_procedure(self->program, procedure);

    if (procedure_symbol->checked_block_statement == NULL) {
        return;
    }

    self->value_counter = 0;
    IR_Block *block = IR_Block__create(1);
    IR_Procedure__append_block(procedure, block);
    self->block = block;

    Lowerer__lower_statement(self, procedure_symbol->checked_block_statement);
}

IR_Program *lower(Checked_Source *checked_source) {
    Lowerer lowerer;
    lowerer.program = IR_Program__create();
    lowerer.block = NULL;
    lowerer.value_counter = 0;

    Checked_Symbol *symbol = checked_source->symbols->first_symbol;
    while (symbol != NULL) {
        if (symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE) {
            Checked_Procedure_Symbol *procedure_symbol = (Checked_Procedure_Symbol *)symbol;
            if (!procedure_symbol->parsed_procedure_statement->is_external) {
                Lowerer__lower_procedure(&lowerer, procedure_symbol);
            }
        }
        symbol = symbol->next_symbol;
    }

    return lowerer.program;
}
