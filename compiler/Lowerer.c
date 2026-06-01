#include "Lowerer.h"
#include "Builtins.h"
#include "File.h"

typedef struct Lowerer {
    IR_Program *program;
    IR_Procedure *procedure;
    IR_Block *block;
    int32_t value_counter;
    int32_t block_counter;
    IR_Block *break_block;
    IR_Value_List globals;
    IR_Value_List scope;
} Lowerer;

IR_Block *Lowerer__create_block(Lowerer *self) {
    self->block_counter++;
    return IR_Block__create(self->block_counter);
}

IR_Value *Lowerer__find_global(Lowerer *self, String *name) {
    for (size_t i = 0; i < self->globals.size; i++) {
        if (String__equals__value_name(self->globals.values[i]->name, '$', name)) {
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
        IR_Value *value = self->scope.values[i];
        String *value_name = value->variable != NULL ? value->variable->super.value.name : value->name;
        if (String__equals__value_name(value_name, '%', name)) {
            return value;
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
    String__append_char(name, '%');
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
    case CHECKED_TYPE_KIND__NOTHING:
        return IR_Type__get(IR_TYPE_KIND__NOTHING);
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
        IR_Type *result_type = Lowerer__lower_type(self, expression->type);
        String *result_name = result_type->kind != IR_TYPE_KIND__NOTHING ? Lowerer__fresh_name(self) : NULL;
        IR_Call_Instruction *instruction = IR_Call_Instruction__create(result_name, result_type, callee);
        for (size_t i = 0; i < arguments.size; i++) {
            IR_Value_List__append(&instruction->super.operands, arguments.values[i]);
        }
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        return &instruction->super.result;
    }
    case CHECKED_EXPRESSION_KIND__BOOL: {
        Checked_Bool_Expression *bool_expression = (Checked_Bool_Expression *)expression;
        IR_Const_Instruction *instruction = IR_Const_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), bool_expression->value ? 1 : 0);
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        return &instruction->super.result;
    }
    case CHECKED_EXPRESSION_KIND__INTEGER: {
        Checked_Integer_Expression *integer_expression = (Checked_Integer_Expression *)expression;
        IR_Const_Instruction *instruction = IR_Const_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), integer_expression->value);
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        return &instruction->super.result;
    }
    case CHECKED_EXPRESSION_KIND__ADD:
    case CHECKED_EXPRESSION_KIND__DIVIDE:
    case CHECKED_EXPRESSION_KIND__EQUALS:
    case CHECKED_EXPRESSION_KIND__GREATER:
    case CHECKED_EXPRESSION_KIND__GREATER_OR_EQUALS:
    case CHECKED_EXPRESSION_KIND__LESS:
    case CHECKED_EXPRESSION_KIND__LESS_OR_EQUALS:
    case CHECKED_EXPRESSION_KIND__MODULO:
    case CHECKED_EXPRESSION_KIND__MULTIPLY:
    case CHECKED_EXPRESSION_KIND__NOT_EQUALS:
    case CHECKED_EXPRESSION_KIND__SUBTRACT: {
        Checked_Binary_Expression *binary_expression = (Checked_Binary_Expression *)expression;
        IR_Value *left = Lowerer__lower_expression(self, binary_expression->left_expression);
        IR_Value *right = Lowerer__lower_expression(self, binary_expression->right_expression);
        IR_Instruction_Kind kind;
        switch (expression->kind) {
        case CHECKED_EXPRESSION_KIND__ADD:
            kind = IR_INSTRUCTION_KIND__ADD;
            break;
        case CHECKED_EXPRESSION_KIND__DIVIDE:
            kind = IR_INSTRUCTION_KIND__DIV;
            break;
        case CHECKED_EXPRESSION_KIND__EQUALS:
            kind = IR_INSTRUCTION_KIND__CMP_EQ;
            break;
        case CHECKED_EXPRESSION_KIND__GREATER:
            kind = IR_INSTRUCTION_KIND__CMP_GT;
            break;
        case CHECKED_EXPRESSION_KIND__GREATER_OR_EQUALS:
            kind = IR_INSTRUCTION_KIND__CMP_GE;
            break;
        case CHECKED_EXPRESSION_KIND__LESS:
            kind = IR_INSTRUCTION_KIND__CMP_LT;
            break;
        case CHECKED_EXPRESSION_KIND__LESS_OR_EQUALS:
            kind = IR_INSTRUCTION_KIND__CMP_LE;
            break;
        case CHECKED_EXPRESSION_KIND__MODULO:
            kind = IR_INSTRUCTION_KIND__MOD;
            break;
        case CHECKED_EXPRESSION_KIND__MULTIPLY:
            kind = IR_INSTRUCTION_KIND__MUL;
            break;
        case CHECKED_EXPRESSION_KIND__NOT_EQUALS:
            kind = IR_INSTRUCTION_KIND__CMP_NE;
            break;
        default:
            kind = IR_INSTRUCTION_KIND__SUB;
            break;
        }
        IR_Binary_Instruction *instruction = IR_Binary_Instruction__create(kind, Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), left, right);
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        return &instruction->super.result;
    }
    case CHECKED_EXPRESSION_KIND__LOGIC_AND:
    case CHECKED_EXPRESSION_KIND__LOGIC_OR: {
        Checked_Binary_Expression *binary_expression = (Checked_Binary_Expression *)expression;
        IR_Value *left = Lowerer__lower_expression(self, binary_expression->left_expression);
        IR_Block *left_block = self->block;
        IR_Block *right_block = Lowerer__create_block(self);
        IR_Block *end_block = Lowerer__create_block(self);
        IR_Br_Instruction *branch = expression->kind == CHECKED_EXPRESSION_KIND__LOGIC_AND
                                        ? IR_Br_Instruction__create(left, right_block, end_block)
                                        : IR_Br_Instruction__create(left, end_block, right_block);
        IR_Block__append_instruction(self->block, (IR_Instruction *)branch);
        IR_Procedure__append_block(self->procedure, right_block);
        self->block = right_block;
        IR_Value *right = Lowerer__lower_expression(self, binary_expression->right_expression);
        IR_Block *right_end_block = self->block;
        IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Jmp_Instruction__create(end_block));
        IR_Procedure__append_block(self->procedure, end_block);
        self->block = end_block;
        IR_Phi_Instruction *instruction = IR_Phi_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type));
        IR_Block_List__append(&instruction->blocks, left_block);
        IR_Value_List__append(&instruction->super.operands, left);
        IR_Block_List__append(&instruction->blocks, right_end_block);
        IR_Value_List__append(&instruction->super.operands, right);
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        return &instruction->super.result;
    }
    case CHECKED_EXPRESSION_KIND__MINUS: {
        Checked_Unary_Expression *unary_expression = (Checked_Unary_Expression *)expression;
        IR_Value *value = Lowerer__lower_expression(self, unary_expression->other_expression);
        IR_Neg_Instruction *instruction = IR_Neg_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), value);
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        return &instruction->super.result;
    }
    case CHECKED_EXPRESSION_KIND__NOT: {
        Checked_Unary_Expression *unary_expression = (Checked_Unary_Expression *)expression;
        IR_Value *value = Lowerer__lower_expression(self, unary_expression->other_expression);
        IR_Not_Instruction *instruction = IR_Not_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), value);
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        return &instruction->super.result;
    }
    case CHECKED_EXPRESSION_KIND__GROUP:
        return Lowerer__lower_expression(self, ((Checked_Group_Expression *)expression)->other_expression);
    case CHECKED_EXPRESSION_KIND__SYMBOL: {
        Checked_Symbol *symbol = ((Checked_Symbol_Expression *)expression)->symbol;
        if (symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE_PARAMETER) {
            return Lowerer__find_scope(self, symbol->name);
        }
        if (symbol->kind == CHECKED_SYMBOL_KIND__VARIABLE) {
            IR_Value *value_pointer;
            String *result_name;
            IR_Type *result_type;
            if (symbol->is_global) {
                value_pointer = Lowerer__find_global(self, symbol->name);
                result_type = Lowerer__lower_type(self, expression->type);
                result_name = Lowerer__fresh_name(self);
            } else {
                value_pointer = Lowerer__find_scope(self, symbol->name);
                IR_Variable *variable = value_pointer->variable;
                result_type = variable->super.value.type;
                variable->version++;
                result_name = String__create_copy(variable->super.value.name);
                String__append_char(result_name, '.');
                String__append_int16_t(result_name, variable->version);
            }
            IR_Load_Instruction *instruction = IR_Load_Instruction__create(result_name, result_type, value_pointer);
            IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
            return &instruction->super.result;
        }
        pWriter__write__cstring(stderr_writer, "Lowering not supported yet: symbol kind ");
        pWriter__write__int64(stderr_writer, symbol->kind);
        pWriter__end_line(stderr_writer);
        panic();
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
    case CHECKED_STATEMENT_KIND__ASSIGNMENT: {
        Checked_Assignment_Statement *assignment_statement = (Checked_Assignment_Statement *)statement;
        if (assignment_statement->object_expression->kind != CHECKED_EXPRESSION_KIND__SYMBOL) {
            pWriter__write__cstring(stderr_writer, "Lowering not supported yet: assignment target expression kind ");
            pWriter__write__int64(stderr_writer, assignment_statement->object_expression->kind);
            pWriter__end_line(stderr_writer);
            panic();
        }
        Checked_Symbol *symbol = ((Checked_Symbol_Expression *)assignment_statement->object_expression)->symbol;
        IR_Value *pointer = Lowerer__find_scope(self, symbol->name);
        IR_Value *value = Lowerer__lower_expression(self, assignment_statement->value_expression);
        IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Store_Instruction__create(pointer, value));
        break;
    }
    case CHECKED_STATEMENT_KIND__BLOCK: {
        Checked_Block_Statement *block_statement = (Checked_Block_Statement *)statement;
        Checked_Statement *child_statement = block_statement->statements->first_statement;
        while (child_statement != NULL) {
            Lowerer__lower_statement(self, child_statement);
            child_statement = child_statement->next_statement;
        }
        break;
    }
    case CHECKED_STATEMENT_KIND__BREAK: {
        IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Jmp_Instruction__create(self->break_block));
        break;
    }
    case CHECKED_STATEMENT_KIND__EXPRESSION: {
        Checked_Expression_Statement *expression_statement = (Checked_Expression_Statement *)statement;
        Lowerer__lower_expression(self, expression_statement->expression);
        break;
    }
    case CHECKED_STATEMENT_KIND__IF: {
        Checked_If_Statement *if_statement = (Checked_If_Statement *)statement;
        IR_Value *condition = Lowerer__lower_expression(self, if_statement->condition_expression);
        IR_Block *true_block = Lowerer__create_block(self);
        IR_Block *false_block = if_statement->false_statement != NULL ? Lowerer__create_block(self) : NULL;
        IR_Block *end_block = Lowerer__create_block(self);
        IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Br_Instruction__create(condition, true_block, false_block != NULL ? false_block : end_block));
        IR_Procedure__append_block(self->procedure, true_block);
        self->block = true_block;
        Lowerer__lower_statement(self, if_statement->true_statement);
        if (!IR_Block__is_terminated(self->block)) {
            IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Jmp_Instruction__create(end_block));
        }
        if (false_block != NULL) {
            IR_Procedure__append_block(self->procedure, false_block);
            self->block = false_block;
            Lowerer__lower_statement(self, if_statement->false_statement);
            if (!IR_Block__is_terminated(self->block)) {
                IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Jmp_Instruction__create(end_block));
            }
        }
        IR_Procedure__append_block(self->procedure, end_block);
        self->block = end_block;
        break;
    }
    case CHECKED_STATEMENT_KIND__LOOP: {
        Checked_Loop_Statement *loop_statement = (Checked_Loop_Statement *)statement;
        IR_Block *body_block = Lowerer__create_block(self);
        IR_Block *end_block = Lowerer__create_block(self);
        IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Jmp_Instruction__create(body_block));
        IR_Procedure__append_block(self->procedure, body_block);
        self->block = body_block;
        IR_Block *outer_break_block = self->break_block;
        self->break_block = end_block;
        Lowerer__lower_statement(self, loop_statement->body_statement);
        self->break_block = outer_break_block;
        if (!IR_Block__is_terminated(self->block)) {
            IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Jmp_Instruction__create(body_block));
        }
        IR_Procedure__append_block(self->procedure, end_block);
        self->block = end_block;
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
    case CHECKED_STATEMENT_KIND__VARIABLE: {
        Checked_Variable_Statement *variable_statement = (Checked_Variable_Statement *)statement;
        IR_Variable *variable = IR_Variable__create(variable_statement->variable->super.name, Lowerer__lower_type(self, variable_statement->variable->super.type));
        IR_Alloc_Instruction *instruction = IR_Alloc_Instruction__create(variable);
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        IR_Value_List__append(&self->scope, &instruction->super.result);
        if (variable_statement->expression != NULL) {
            IR_Value *value = Lowerer__lower_expression(self, variable_statement->expression);
            IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Store_Instruction__create(&instruction->super.result, value));
        }
        break;
    }
    case CHECKED_STATEMENT_KIND__WHILE: {
        Checked_While_Statement *while_statement = (Checked_While_Statement *)statement;
        IR_Block *condition_block = Lowerer__create_block(self);
        IR_Block *body_block = Lowerer__create_block(self);
        IR_Block *end_block = Lowerer__create_block(self);
        IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Jmp_Instruction__create(condition_block));
        IR_Procedure__append_block(self->procedure, condition_block);
        self->block = condition_block;
        IR_Value *condition = Lowerer__lower_expression(self, while_statement->condition_expression);
        IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Br_Instruction__create(condition, body_block, end_block));
        IR_Procedure__append_block(self->procedure, body_block);
        self->block = body_block;
        IR_Block *outer_break_block = self->break_block;
        self->break_block = end_block;
        Lowerer__lower_statement(self, while_statement->body_statement);
        self->break_block = outer_break_block;
        if (!IR_Block__is_terminated(self->block)) {
            IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Jmp_Instruction__create(condition_block));
        }
        IR_Procedure__append_block(self->procedure, end_block);
        self->block = end_block;
        break;
    }
    default:
        pWriter__write__cstring(stderr_writer, "Lowering not supported yet: statement kind ");
        pWriter__write__int64(stderr_writer, statement->kind);
        pWriter__end_line(stderr_writer);
        panic();
    }
}

IR_Type **Lowerer__lower_parameter_types(Lowerer *self, Checked_Procedure_Type *checked_procedure_type, size_t *parameter_count) {
    size_t count = 0;
    for (Checked_Procedure_Parameter *parameter = checked_procedure_type->first_parameter; parameter != NULL; parameter = parameter->next_parameter) {
        count++;
    }
    IR_Type **parameter_types = count > 0 ? (IR_Type **)malloc(count * sizeof(IR_Type *)) : NULL;
    size_t parameter_index = 0;
    for (Checked_Procedure_Parameter *parameter = checked_procedure_type->first_parameter; parameter != NULL; parameter = parameter->next_parameter) {
        parameter_types[parameter_index++] = Lowerer__lower_type(self, parameter->type);
    }
    *parameter_count = count;
    return parameter_types;
}

void Lowerer__declare_procedure(Lowerer *self, Checked_Procedure_Symbol *procedure_symbol) {
    Checked_Procedure_Type *checked_procedure_type = procedure_symbol->procedure_type;
    IR_Type *return_type = Lowerer__lower_type(self, checked_procedure_type->return_type);

    size_t parameter_count;
    IR_Type **parameter_types = Lowerer__lower_parameter_types(self, checked_procedure_type, &parameter_count);

    IR_Procedure *procedure = IR_Procedure__create(procedure_symbol->super.name, parameter_types, parameter_count, return_type);
    IR_Program__append_procedure(self->program, procedure);
    IR_Value_List__append(&self->globals, &procedure->super.value);

    size_t parameter_index = 0;
    for (Checked_Procedure_Parameter *parameter = checked_procedure_type->first_parameter; parameter != NULL; parameter = parameter->next_parameter) {
        IR_Value_List__append(&procedure->parameters, IR_Value__create(IR_VALUE_KIND__PARAMETER, IR__value_name('%', parameter->name), parameter_types[parameter_index++]));
    }
}

void Lowerer__declare_external_procedure(Lowerer *self, Checked_Procedure_Symbol *procedure_symbol) {
    Checked_Procedure_Type *checked_procedure_type = procedure_symbol->procedure_type;
    IR_Type *return_type = Lowerer__lower_type(self, checked_procedure_type->return_type);

    size_t parameter_count;
    IR_Type **parameter_types = Lowerer__lower_parameter_types(self, checked_procedure_type, &parameter_count);

    IR_Type *procedure_type = (IR_Type *)IR_Procedure_Type__create(parameter_types, parameter_count, return_type);
    IR_Global *global = IR_Global__create(procedure_symbol->super.name, (IR_Type *)IR_Pointer_Type__create(procedure_type));
    IR_Program__append_global(self->program, global);
    IR_Value_List__append(&self->globals, &global->super.value);
}

void Lowerer__declare_external_variable(Lowerer *self, Checked_Variable_Symbol *variable_symbol) {
    IR_Type *type = Lowerer__lower_type(self, variable_symbol->super.type);
    IR_Global *global = IR_Global__create(variable_symbol->super.name, (IR_Type *)IR_Pointer_Type__create(type));
    IR_Program__append_global(self->program, global);
    IR_Value_List__append(&self->globals, &global->super.value);
}

void Lowerer__define_procedure(Lowerer *self, Checked_Procedure_Symbol *procedure_symbol) {
    if (procedure_symbol->checked_block_statement == NULL) {
        return;
    }

    IR_Procedure *procedure = (IR_Procedure *)Lowerer__find_global(self, procedure_symbol->super.name);

    self->procedure = procedure;
    self->value_counter = 0;
    self->block_counter = 0;
    self->scope.size = 0;
    for (size_t i = 0; i < procedure->parameters.size; i++) {
        IR_Value_List__append(&self->scope, procedure->parameters.values[i]);
    }

    IR_Block *block = Lowerer__create_block(self);
    IR_Procedure__append_block(procedure, block);
    self->block = block;

    Lowerer__lower_statement(self, procedure_symbol->checked_block_statement);

    if (procedure->return_type->kind == IR_TYPE_KIND__NOTHING && !IR_Block__is_terminated(self->block)) {
        IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Ret_Instruction__create(NULL));
    }
}

bool Checked_Procedure_Symbol__is_lowerable(Checked_Procedure_Symbol *procedure_symbol) {
    return !procedure_symbol->parsed_procedure_statement->is_external;
}

IR_Program *lower(Checked_Source *checked_source) {
    Lowerer lowerer;
    lowerer.program = IR_Program__create();
    lowerer.procedure = NULL;
    lowerer.block = NULL;
    lowerer.value_counter = 0;
    lowerer.block_counter = 0;
    lowerer.break_block = NULL;
    lowerer.globals = (IR_Value_List){.values = NULL, .size = 0, .capacity = 0};
    lowerer.scope = (IR_Value_List){.values = NULL, .size = 0, .capacity = 0};

    for (Checked_Symbol *symbol = checked_source->symbols->first_symbol; symbol != NULL; symbol = symbol->next_symbol) {
        if (symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE) {
            if (Checked_Procedure_Symbol__is_lowerable((Checked_Procedure_Symbol *)symbol)) {
                Lowerer__declare_procedure(&lowerer, (Checked_Procedure_Symbol *)symbol);
            } else {
                Lowerer__declare_external_procedure(&lowerer, (Checked_Procedure_Symbol *)symbol);
            }
        } else if (symbol->kind == CHECKED_SYMBOL_KIND__VARIABLE) {
            Checked_Variable_Symbol *variable_symbol = (Checked_Variable_Symbol *)symbol;
            if (variable_symbol->statement->is_external) {
                Lowerer__declare_external_variable(&lowerer, variable_symbol);
            } else {
                pWriter__write__cstring(stderr_writer, "Lowering not supported yet: non-external global variable");
                pWriter__end_line(stderr_writer);
                panic();
            }
        }
    }

    for (Checked_Symbol *symbol = checked_source->symbols->first_symbol; symbol != NULL; symbol = symbol->next_symbol) {
        if (symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE && Checked_Procedure_Symbol__is_lowerable((Checked_Procedure_Symbol *)symbol)) {
            Lowerer__define_procedure(&lowerer, (Checked_Procedure_Symbol *)symbol);
        }
    }

    return lowerer.program;
}
