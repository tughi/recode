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
    IR_Value *malloc_callee;
    Checked_Struct_Type *string_type;
    int32_t string_counter;
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

IR_Type *Lowerer__lower_type(Lowerer *self, Checked_Type *type);

String *Lowerer__type_name(Lowerer *self, Checked_Type *type) {
    Checked_Named_Type *named_type = (Checked_Named_Type *)type;
    String *name = String__create();
    if (named_type->package != NULL) {
        String__append_string(name, named_type->package->name);
        String__append_char(name, '.');
    }
    String__append_string(name, named_type->name);
    return name;
}

String *Lowerer__procedure_name(Lowerer *self, Checked_Procedure_Symbol *procedure_symbol) {
    Parsed_Procedure_Statement *parsed_procedure_statement = procedure_symbol->parsed_procedure_statement;
    if (parsed_procedure_statement->is_external) {
        return procedure_symbol->external_name != NULL ? procedure_symbol->external_name : procedure_symbol->super.name;
    }
    String *name = String__create();
    Writer writer = String__create_writer(name);
    if (procedure_symbol->receiver_type != NULL) {
        String__append_char(name, '(');
        pWriter__write__ir_type(&writer, Lowerer__lower_type(self, procedure_symbol->receiver_type));
        String__append_cstring(name, ").");
    } else {
        String__append_string(name, procedure_symbol->super.package->name);
        String__append_char(name, '.');
    }
    String__append_string(name, parsed_procedure_statement->super.name->lexeme);
    return name;
}

String *Lowerer__variable_name(Checked_Variable_Symbol *variable_symbol) {
    if (variable_symbol->statement->is_external) {
        return variable_symbol->external_name != NULL ? variable_symbol->external_name : variable_symbol->super.name;
    }
    String *name = String__create();
    String__append_string(name, variable_symbol->super.package->name);
    String__append_char(name, '.');
    String__append_string(name, variable_symbol->super.name);
    return name;
}

IR_Value *Lowerer__find_scope(Lowerer *self, Checked_Symbol *symbol) {
    for (size_t i = self->scope.size; i > 0; i--) {
        IR_Value *value = self->scope.values[i - 1];
        if (value->variable != NULL) {
            if (value->variable->symbol == symbol) {
                return value;
            }
        } else if (String__equals__value_name(value->name, '%', symbol->name)) {
            return value;
        }
    }
    pWriter__write__cstring(stderr_writer, "No IR value in scope named: ");
    pWriter__write__string(stderr_writer, symbol->name);
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

IR_Variable *Lowerer__declare_variable(Lowerer *self, Checked_Symbol *symbol, IR_Type *type) {
    String *source_name = symbol->name;
    int32_t count = 0;
    for (size_t i = 0; i < self->scope.size; i++) {
        IR_Variable *existing = self->scope.values[i]->variable;
        if (existing != NULL && String__equals_string(existing->symbol->name, source_name)) {
            count++;
        }
    }
    String *display_name = source_name;
    if (count > 0) {
        display_name = String__create_copy(source_name);
        String__append_char(display_name, '.');
        String__append_int16_t(display_name, count + 1);
    }
    IR_Variable *variable = IR_Variable__create(display_name, type);
    variable->symbol = symbol;
    return variable;
}

IR_Type **Lowerer__lower_parameter_types(Lowerer *self, Checked_Procedure_Type *checked_procedure_type, size_t *parameter_count);

IR_Type *Lowerer__lower_external_type(Lowerer *self, String *name) {
    for (IR_Named_Type *type = self->program->first_type; type != NULL; type = type->next_type) {
        if (String__equals_string(type->name, name)) {
            return (IR_Type *)type;
        }
    }
    IR_Opaque_Type *opaque_type = IR_Opaque_Type__create(name);
    IR_Program__append_type(self->program, &opaque_type->super);
    return (IR_Type *)opaque_type;
}

IR_Type *Lowerer__lower_type(Lowerer *self, Checked_Type *type) {
    switch (type->kind) {
    case CHECKED_TYPE_KIND__ANY:
        return IR_Type__get(IR_TYPE_KIND__ANY);
    case CHECKED_TYPE_KIND__ARRAY: {
        Checked_Array_Type *array_type = (Checked_Array_Type *)type;
        return (IR_Type *)IR_Array_Type__create(Lowerer__lower_type(self, array_type->item_type), array_type->length);
    }
    case CHECKED_TYPE_KIND__BOOL:
        return IR_Type__get(IR_TYPE_KIND__BOOL);
    case CHECKED_TYPE_KIND__ENUM:
        return IR_Type__get(IR_TYPE_KIND__I32);
    case CHECKED_TYPE_KIND__EXTERNAL:
        return Lowerer__lower_external_type(self, ((Checked_External_Type *)type)->super.name);
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
    case CHECKED_TYPE_KIND__NULL:
        return (IR_Type *)IR_Pointer_Type__create(IR_Type__get(IR_TYPE_KIND__ANY));
    case CHECKED_TYPE_KIND__MULTI_POINTER:
        return (IR_Type *)IR_Multi_Pointer_Type__create(Lowerer__lower_type(self, ((Checked_Multi_Pointer_Type *)type)->item_type));
    case CHECKED_TYPE_KIND__POINTER:
        return (IR_Type *)IR_Pointer_Type__create(Lowerer__lower_type(self, ((Checked_Pointer_Type *)type)->other_type));
    case CHECKED_TYPE_KIND__PROCEDURE: {
        Checked_Procedure_Type *procedure_type = (Checked_Procedure_Type *)type;
        IR_Type *return_type = Lowerer__lower_type(self, procedure_type->return_type);
        size_t parameter_count;
        IR_Type **parameter_types = Lowerer__lower_parameter_types(self, procedure_type, &parameter_count);
        return (IR_Type *)IR_Pointer_Type__create((IR_Type *)IR_Procedure_Type__create(parameter_types, parameter_count, return_type));
    }
    case CHECKED_TYPE_KIND__STRUCT: {
        Checked_Struct_Type *struct_type = (Checked_Struct_Type *)type;
        String *name = Lowerer__type_name(self, type);
        for (IR_Named_Type *existing_type = self->program->first_type; existing_type != NULL; existing_type = existing_type->next_type) {
            if (String__equals_string(existing_type->name, name)) {
                return (IR_Type *)existing_type;
            }
        }
        IR_Struct_Type *ir_struct_type = IR_Struct_Type__create(name);
        IR_Program__append_type(self->program, &ir_struct_type->super);
        for (Checked_Struct_Member *member = struct_type->first_member; member != NULL; member = member->next_member) {
            IR_Struct_Type__append_field(ir_struct_type, member->name, Lowerer__lower_type(self, member->type));
        }
        return (IR_Type *)ir_struct_type;
    }
    case CHECKED_TYPE_KIND__STR:
        return Lowerer__lower_type(self, (Checked_Type *)self->string_type);
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

IR_Value *Lowerer__lower_expression(Lowerer *self, Checked_Expression *expression);
void Lowerer__lower_statement(Lowerer *self, Checked_Statement *statement);

IR_Value *Lowerer__lower_temporary_pointer(Lowerer *self, Checked_Expression *expression) {
    IR_Value *value = Lowerer__lower_expression(self, expression);
    self->value_counter++;
    String *temporary_name = String__create();
    String__append_int16_t(temporary_name, self->value_counter);
    IR_Variable *variable = IR_Variable__create(temporary_name, Lowerer__lower_type(self, expression->type));
    IR_Alloc_Instruction *instruction = IR_Alloc_Instruction__create(variable);
    IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
    IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Store_Instruction__create(&instruction->super.result, value));
    return &instruction->super.result;
}

IR_Value *Lowerer__lower_object_pointer(Lowerer *self, Checked_Expression *expression);

IR_Value *Lowerer__lower_array_offset(Lowerer *self, Checked_Array_Access_Expression *array_access_expression) {
    IR_Value *array;
    if (array_access_expression->array_expression->type->kind == CHECKED_TYPE_KIND__ARRAY) {
        array = Lowerer__lower_object_pointer(self, array_access_expression->array_expression);
    } else {
        array = Lowerer__lower_expression(self, array_access_expression->array_expression);
    }
    IR_Value *index = Lowerer__lower_expression(self, array_access_expression->index_expression);
    IR_Type *item_type = Lowerer__lower_type(self, array_access_expression->super.type);
    IR_Array_Offset_Instruction *instruction = IR_Array_Offset_Instruction__create(Lowerer__fresh_name(self), (IR_Type *)IR_Pointer_Type__create(item_type), array, index);
    IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
    return &instruction->super.result;
}

IR_Value *Lowerer__lower_struct_offset(Lowerer *self, Checked_Member_Access_Expression *member_access_expression);

IR_Value *Lowerer__lower_object_pointer(Lowerer *self, Checked_Expression *expression) {
    if (expression->type->kind == CHECKED_TYPE_KIND__POINTER) {
        return Lowerer__lower_expression(self, expression);
    }
    switch (expression->kind) {
    case CHECKED_EXPRESSION_KIND__SYMBOL: {
        Checked_Symbol *symbol = ((Checked_Symbol_Expression *)expression)->symbol;
        if (symbol->is_global) {
            if (symbol->kind == CHECKED_SYMBOL_KIND__VARIABLE) {
                return Lowerer__find_global(self, Lowerer__variable_name((Checked_Variable_Symbol *)symbol));
            }
            return Lowerer__find_global(self, symbol->name);
        }
        if (symbol->kind == CHECKED_SYMBOL_KIND__VARIABLE) {
            return Lowerer__find_scope(self, symbol);
        }
        return Lowerer__lower_temporary_pointer(self, expression);
    }
    case CHECKED_EXPRESSION_KIND__ARRAY_ACCESS:
        return Lowerer__lower_array_offset(self, (Checked_Array_Access_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__MEMBER_ACCESS:
        return Lowerer__lower_struct_offset(self, (Checked_Member_Access_Expression *)expression);
    default:
        return Lowerer__lower_temporary_pointer(self, expression);
    }
}

IR_Value *Lowerer__lower_struct_offset(Lowerer *self, Checked_Member_Access_Expression *member_access_expression) {
    IR_Value *object_pointer = Lowerer__lower_object_pointer(self, member_access_expression->object_expression);
    Checked_Struct_Member *member = member_access_expression->member;
    IR_Type *member_type = Lowerer__lower_type(self, member_access_expression->super.type);
    IR_Struct_Offset_Instruction *instruction = IR_Struct_Offset_Instruction__create(Lowerer__fresh_name(self), (IR_Type *)IR_Pointer_Type__create(member_type), object_pointer, member->name);
    IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
    return &instruction->super.result;
}

IR_Value *Lowerer__field_pointer(Lowerer *self, IR_Value *struct_pointer, IR_Struct_Type *struct_type, const char *field_name) {
    IR_Type *field_type = NULL;
    for (IR_Struct_Type_Field *field = struct_type->first_field; field != NULL; field = field->next_field) {
        if (String__equals_cstring(field->name, (char *)field_name)) {
            field_type = field->type;
            break;
        }
    }
    IR_Struct_Offset_Instruction *offset = IR_Struct_Offset_Instruction__create(Lowerer__fresh_name(self), (IR_Type *)IR_Pointer_Type__create(field_type), struct_pointer, String__create_from((char *)field_name));
    IR_Block__append_instruction(self->block, (IR_Instruction *)offset);
    return &offset->super.result;
}

IR_Value *Lowerer__load_field(Lowerer *self, IR_Value *struct_pointer, IR_Struct_Type *struct_type, const char *field_name) {
    IR_Value *field_pointer = Lowerer__field_pointer(self, struct_pointer, struct_type, field_name);
    IR_Type *field_type = ((IR_Pointer_Type *)field_pointer->type)->pointee;
    IR_Load_Instruction *load = IR_Load_Instruction__create(Lowerer__fresh_name(self), field_type, field_pointer);
    IR_Block__append_instruction(self->block, (IR_Instruction *)load);
    return &load->super.result;
}

IR_Value *Lowerer__store_temporary(Lowerer *self, IR_Value *value, IR_Type *type) {
    self->value_counter++;
    String *temporary_name = String__create();
    String__append_int16_t(temporary_name, self->value_counter);
    IR_Alloc_Instruction *alloc = IR_Alloc_Instruction__create(IR_Variable__create(temporary_name, type));
    IR_Block__append_instruction(self->block, (IR_Instruction *)alloc);
    IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Store_Instruction__create(&alloc->super.result, value));
    return &alloc->super.result;
}

IR_Value *Lowerer__string_global(Lowerer *self, String *value) {
    for (IR_Global *global = self->program->first_global; global != NULL; global = global->next_global) {
        if (global->literal != NULL && String__equals_string(global->literal, value)) {
            return &global->super.value;
        }
    }
    self->string_counter++;
    String *global_name = String__create_from("str_");
    String__append_int16_t(global_name, self->string_counter);
    IR_Global *global = IR_String_Global__create(global_name, (IR_Type *)IR_Multi_Pointer_Type__create(IR_Type__get(IR_TYPE_KIND__U8)), value);
    IR_Program__append_global(self->program, global);
    return &global->super.value;
}

IR_Value *Lowerer__lower_expression(Lowerer *self, Checked_Expression *expression) {
    switch (expression->kind) {
    case CHECKED_EXPRESSION_KIND__CALL: {
        Checked_Call_Expression *call_expression = (Checked_Call_Expression *)expression;
        IR_Value *callee = Lowerer__lower_expression(self, call_expression->callee_expression);
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
    case CHECKED_EXPRESSION_KIND__ALLOC: {
        Checked_Alloc_Expression *alloc_expression = (Checked_Alloc_Expression *)expression;
        IR_Type *pointer_type = Lowerer__lower_type(self, expression->type);
        IR_Type *allocated_type = ((IR_Pointer_Type *)pointer_type)->pointee;

        IR_Const_Instruction *size = IR_Const_Instruction__create(Lowerer__fresh_name(self), IR_Type__get(IR_TYPE_KIND__USIZE), IR_Type__size(allocated_type), NULL);
        IR_Block__append_instruction(self->block, (IR_Instruction *)size);

        if (self->malloc_callee == NULL) {
            self->malloc_callee = Lowerer__find_global(self, String__create_from("malloc"));
        }
        IR_Call_Instruction *call = IR_Call_Instruction__create(Lowerer__fresh_name(self), (IR_Type *)IR_Pointer_Type__create(IR_Type__get(IR_TYPE_KIND__ANY)), self->malloc_callee);
        IR_Value_List__append(&call->super.operands, &size->super.result);
        IR_Block__append_instruction(self->block, (IR_Instruction *)call);

        IR_Cast_Instruction *cast = IR_Cast_Instruction__create(Lowerer__fresh_name(self), pointer_type, &call->super.result);
        IR_Block__append_instruction(self->block, (IR_Instruction *)cast);

        IR_Value *value = Lowerer__lower_expression(self, alloc_expression->value_expression);
        IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Store_Instruction__create(&cast->super.result, value));

        return &cast->super.result;
    }
    case CHECKED_EXPRESSION_KIND__BOOL: {
        Checked_Bool_Expression *bool_expression = (Checked_Bool_Expression *)expression;
        IR_Const_Instruction *instruction = IR_Const_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), bool_expression->value ? 1 : 0, NULL);
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        return &instruction->super.result;
    }
    case CHECKED_EXPRESSION_KIND__INTEGER: {
        Checked_Integer_Expression *integer_expression = (Checked_Integer_Expression *)expression;
        IR_Const_Instruction *instruction = IR_Const_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), integer_expression->value, integer_expression->literal);
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        return &instruction->super.result;
    }
    case CHECKED_EXPRESSION_KIND__ENUM_MEMBER: {
        Checked_Enum_Member_Expression *enum_member_expression = (Checked_Enum_Member_Expression *)expression;
        IR_Const_Instruction *instruction = IR_Const_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), enum_member_expression->member->value, NULL);
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
    case CHECKED_EXPRESSION_KIND__ADDRESS_OF: {
        Checked_Expression *operand = ((Checked_Unary_Expression *)expression)->other_expression;
        if (operand->kind == CHECKED_EXPRESSION_KIND__SYMBOL) {
            Checked_Symbol *symbol = ((Checked_Symbol_Expression *)operand)->symbol;
            if (symbol->kind == CHECKED_SYMBOL_KIND__VARIABLE) {
                return symbol->is_global ? Lowerer__find_global(self, Lowerer__variable_name((Checked_Variable_Symbol *)symbol)) : Lowerer__find_scope(self, symbol);
            }
        }
        if (operand->kind == CHECKED_EXPRESSION_KIND__ARRAY_ACCESS) {
            return Lowerer__lower_array_offset(self, (Checked_Array_Access_Expression *)operand);
        }
        if (operand->kind == CHECKED_EXPRESSION_KIND__MEMBER_ACCESS) {
            return Lowerer__lower_struct_offset(self, (Checked_Member_Access_Expression *)operand);
        }
        return Lowerer__lower_temporary_pointer(self, operand);
    }
    case CHECKED_EXPRESSION_KIND__ARRAY_ACCESS: {
        IR_Value *pointer = Lowerer__lower_array_offset(self, (Checked_Array_Access_Expression *)expression);
        IR_Load_Instruction *load = IR_Load_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), pointer);
        IR_Block__append_instruction(self->block, (IR_Instruction *)load);
        return &load->super.result;
    }
    case CHECKED_EXPRESSION_KIND__CAST: {
        Checked_Cast_Expression *cast_expression = (Checked_Cast_Expression *)expression;
        IR_Value *value = Lowerer__lower_expression(self, cast_expression->other_expression);
        IR_Cast_Instruction *instruction = IR_Cast_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), value);
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        return &instruction->super.result;
    }
    case CHECKED_EXPRESSION_KIND__CHARACTER: {
        Checked_Character_Expression *character_expression = (Checked_Character_Expression *)expression;
        IR_Const_Instruction *instruction = IR_Const_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), (uint64_t)(uint8_t)character_expression->value, character_expression->literal);
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        return &instruction->super.result;
    }
    case CHECKED_EXPRESSION_KIND__STRING_LENGTH: {
        Checked_String_Length_Expression *string_length_expression = (Checked_String_Length_Expression *)expression;
        Checked_Struct_Member *length_member = self->string_type->first_member->next_member;
        IR_Value *object_pointer = Lowerer__lower_object_pointer(self, string_length_expression->string_expression);
        IR_Type *member_type = Lowerer__lower_type(self, expression->type);
        IR_Struct_Offset_Instruction *offset = IR_Struct_Offset_Instruction__create(Lowerer__fresh_name(self), (IR_Type *)IR_Pointer_Type__create(member_type), object_pointer, length_member->name);
        IR_Block__append_instruction(self->block, (IR_Instruction *)offset);
        IR_Load_Instruction *load = IR_Load_Instruction__create(Lowerer__fresh_name(self), member_type, &offset->super.result);
        IR_Block__append_instruction(self->block, (IR_Instruction *)load);
        return &load->super.result;
    }
    case CHECKED_EXPRESSION_KIND__STRING: {
        Checked_String_Expression *string_expression = (Checked_String_Expression *)expression;
        Checked_Struct_Member *data_member = self->string_type->first_member;
        Checked_Struct_Member *length_member = data_member->next_member;

        IR_Value *data;
        if (string_expression->value->length == 0) {
            IR_Const_Instruction *null = IR_Const_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, data_member->type), 0, NULL);
            IR_Block__append_instruction(self->block, (IR_Instruction *)null);
            data = &null->super.result;
        } else {
            data = Lowerer__string_global(self, string_expression->value);
        }

        IR_Const_Instruction *length = IR_Const_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, length_member->type), string_expression->value->length, NULL);
        IR_Block__append_instruction(self->block, (IR_Instruction *)length);

        IR_Struct_Instruction *instruction = IR_Struct_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type));
        IR_Struct_Instruction__append_field(instruction, data_member->name, data);
        IR_Struct_Instruction__append_field(instruction, length_member->name, &length->super.result);
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        return &instruction->super.result;
    }
    case CHECKED_EXPRESSION_KIND__MEMBER_ACCESS: {
        IR_Value *pointer = Lowerer__lower_struct_offset(self, (Checked_Member_Access_Expression *)expression);
        IR_Load_Instruction *load = IR_Load_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), pointer);
        IR_Block__append_instruction(self->block, (IR_Instruction *)load);
        return &load->super.result;
    }
    case CHECKED_EXPRESSION_KIND__MAKE_ARRAY: {
        Checked_Make_Array_Expression *make_array_expression = (Checked_Make_Array_Expression *)expression;
        IR_Array_Type *array_type = (IR_Array_Type *)Lowerer__lower_type(self, expression->type);

        self->value_counter++;
        String *temporary_name = String__create();
        String__append_int16_t(temporary_name, self->value_counter);
        IR_Alloc_Instruction *alloc = IR_Alloc_Instruction__create(IR_Variable__create(temporary_name, (IR_Type *)array_type));
        IR_Block__append_instruction(self->block, (IR_Instruction *)alloc);

        size_t index = 0;
        for (Checked_Call_Argument *argument = make_array_expression->first_argument; argument != NULL; argument = argument->next_argument) {
            IR_Value *item = Lowerer__lower_expression(self, argument->expression);
            IR_Const_Instruction *index_const = IR_Const_Instruction__create(Lowerer__fresh_name(self), IR_Type__get(IR_TYPE_KIND__I32), index, NULL);
            IR_Block__append_instruction(self->block, (IR_Instruction *)index_const);
            IR_Array_Offset_Instruction *item_offset = IR_Array_Offset_Instruction__create(Lowerer__fresh_name(self), (IR_Type *)IR_Pointer_Type__create(array_type->item_type), &alloc->super.result, &index_const->super.result);
            IR_Block__append_instruction(self->block, (IR_Instruction *)item_offset);
            IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Store_Instruction__create(&item_offset->super.result, item));
            index++;
        }

        IR_Load_Instruction *load = IR_Load_Instruction__create(Lowerer__fresh_name(self), (IR_Type *)array_type, &alloc->super.result);
        IR_Block__append_instruction(self->block, (IR_Instruction *)load);
        return &load->super.result;
    }
    case CHECKED_EXPRESSION_KIND__MAKE_STRUCT: {
        Checked_Make_Struct_Expression *make_struct_expression = (Checked_Make_Struct_Expression *)expression;
        IR_Struct_Instruction *instruction = IR_Struct_Instruction__create(NULL, Lowerer__lower_type(self, expression->type));
        for (Checked_Make_Struct_Argument *argument = make_struct_expression->first_argument; argument != NULL; argument = argument->next_argument) {
            IR_Value *value = Lowerer__lower_expression(self, argument->expression);
            IR_Struct_Instruction__append_field(instruction, argument->struct_member->name, value);
        }
        instruction->super.result.name = Lowerer__fresh_name(self);
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        return &instruction->super.result;
    }
    case CHECKED_EXPRESSION_KIND__DEREFERENCE: {
        Checked_Unary_Expression *unary_expression = (Checked_Unary_Expression *)expression;
        IR_Value *pointer = Lowerer__lower_expression(self, unary_expression->other_expression);
        IR_Load_Instruction *instruction = IR_Load_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), pointer);
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
    case CHECKED_EXPRESSION_KIND__NULL: {
        IR_Const_Instruction *instruction = IR_Const_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), 0, NULL);
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        return &instruction->super.result;
    }
    case CHECKED_EXPRESSION_KIND__TYPE_ALIGNMENT: {
        Checked_Type_Alignment_Expression *type_alignment_expression = (Checked_Type_Alignment_Expression *)expression;
        Checked_Type *aligned_type = type_alignment_expression->aligned_type;
        while (aligned_type->kind == CHECKED_TYPE_KIND__MULTI_POINTER) {
            aligned_type = ((Checked_Multi_Pointer_Type *)aligned_type)->item_type;
        }
        uint64_t alignment = IR_Type__alignment(Lowerer__lower_type(self, aligned_type));
        IR_Const_Instruction *instruction = IR_Const_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), alignment, NULL);
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        return &instruction->super.result;
    }
    case CHECKED_EXPRESSION_KIND__TYPE_SIZE: {
        Checked_Type_Size_Expression *type_size_expression = (Checked_Type_Size_Expression *)expression;
        uint64_t size = IR_Type__size(Lowerer__lower_type(self, type_size_expression->sized_type));
        IR_Const_Instruction *instruction = IR_Const_Instruction__create(Lowerer__fresh_name(self), Lowerer__lower_type(self, expression->type), size, NULL);
        IR_Block__append_instruction(self->block, (IR_Instruction *)instruction);
        return &instruction->super.result;
    }
    case CHECKED_EXPRESSION_KIND__GROUP:
        return Lowerer__lower_expression(self, ((Checked_Group_Expression *)expression)->other_expression);
    case CHECKED_EXPRESSION_KIND__SYMBOL: {
        Checked_Symbol *symbol = ((Checked_Symbol_Expression *)expression)->symbol;
        if (symbol->kind == CHECKED_SYMBOL_KIND__CONSTANT) {
            return Lowerer__lower_expression(self, ((Checked_Constant_Symbol *)symbol)->value_expression);
        }
        if (symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE) {
            return Lowerer__find_global(self, Lowerer__procedure_name(self, (Checked_Procedure_Symbol *)symbol));
        }
        if (symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE_PARAMETER) {
            return Lowerer__find_scope(self, symbol);
        }
        if (symbol->kind == CHECKED_SYMBOL_KIND__VARIABLE) {
            IR_Value *value_pointer;
            String *result_name;
            IR_Type *result_type;
            if (symbol->is_global) {
                value_pointer = Lowerer__find_global(self, Lowerer__variable_name((Checked_Variable_Symbol *)symbol));
                result_type = Lowerer__lower_type(self, expression->type);
                result_name = Lowerer__fresh_name(self);
            } else {
                value_pointer = Lowerer__find_scope(self, symbol);
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
    case CHECKED_EXPRESSION_KIND__RECEIVER_METHOD: {
        pWriter__begin_location_message(stderr_writer, expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Code does not have closures");
        pWriter__end_location_message(stderr_writer);
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
        IR_Value *pointer;
        if (assignment_statement->object_expression->kind == CHECKED_EXPRESSION_KIND__SYMBOL) {
            Checked_Symbol *symbol = ((Checked_Symbol_Expression *)assignment_statement->object_expression)->symbol;
            pointer = symbol->is_global ? Lowerer__find_global(self, Lowerer__variable_name((Checked_Variable_Symbol *)symbol)) : Lowerer__find_scope(self, symbol);
        } else if (assignment_statement->object_expression->kind == CHECKED_EXPRESSION_KIND__DEREFERENCE) {
            Checked_Unary_Expression *unary_expression = (Checked_Unary_Expression *)assignment_statement->object_expression;
            pointer = Lowerer__lower_expression(self, unary_expression->other_expression);
        } else if (assignment_statement->object_expression->kind == CHECKED_EXPRESSION_KIND__ARRAY_ACCESS) {
            pointer = Lowerer__lower_array_offset(self, (Checked_Array_Access_Expression *)assignment_statement->object_expression);
        } else if (assignment_statement->object_expression->kind == CHECKED_EXPRESSION_KIND__MEMBER_ACCESS) {
            pointer = Lowerer__lower_struct_offset(self, (Checked_Member_Access_Expression *)assignment_statement->object_expression);
        } else {
            pWriter__write__cstring(stderr_writer, "Lowering not supported yet: assignment target expression kind ");
            pWriter__write__int64(stderr_writer, assignment_statement->object_expression->kind);
            pWriter__end_line(stderr_writer);
            panic();
        }
        IR_Value *value = Lowerer__lower_expression(self, assignment_statement->value_expression);
        IR_Block__append_instruction(self->block, (IR_Instruction *)IR_Store_Instruction__create(pointer, value));
        break;
    }
    case CHECKED_STATEMENT_KIND__BLOCK: {
        Checked_Block_Statement *block_statement = (Checked_Block_Statement *)statement;
        Checked_Statement *child_statement = block_statement->statements->first_statement;
        while (child_statement != NULL && !IR_Block__is_terminated(self->block)) {
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
    case CHECKED_STATEMENT_KIND__PANIC: {
        Checked_Panic_Statement *panic_statement = (Checked_Panic_Statement *)statement;

        String *message = String__create();
        Writer writer = String__create_writer(message);
        pWriter__write__string(&writer, statement->location.source->file_path);
        pWriter__write__char(&writer, ':');
        pWriter__write__uint64(&writer, statement->location.start_line);
        pWriter__write__cstring(&writer, ": Panic!");
        if (panic_statement->message != NULL) {
            pWriter__write__char(&writer, ' ');
            pWriter__write__string(&writer, panic_statement->message);
        }
        pWriter__end_line(&writer);

        IR_Value *data = Lowerer__string_global(self, message);
        IR_Cast_Instruction *buffer = IR_Cast_Instruction__create(Lowerer__fresh_name(self), (IR_Type *)IR_Pointer_Type__create(IR_Type__get(IR_TYPE_KIND__ANY)), data);
        IR_Block__append_instruction(self->block, (IR_Instruction *)buffer);
        IR_Const_Instruction *size = IR_Const_Instruction__create(Lowerer__fresh_name(self), IR_Type__get(IR_TYPE_KIND__USIZE), 1, NULL);
        IR_Block__append_instruction(self->block, (IR_Instruction *)size);
        IR_Const_Instruction *count = IR_Const_Instruction__create(Lowerer__fresh_name(self), IR_Type__get(IR_TYPE_KIND__USIZE), message->length, NULL);
        IR_Block__append_instruction(self->block, (IR_Instruction *)count);
        IR_Value *stderr_global = Lowerer__find_global(self, String__create_from("stderr"));
        IR_Load_Instruction *file = IR_Load_Instruction__create(Lowerer__fresh_name(self), ((IR_Pointer_Type *)stderr_global->type)->pointee, stderr_global);
        IR_Block__append_instruction(self->block, (IR_Instruction *)file);

        IR_Value *fwrite_callee = Lowerer__find_global(self, String__create_from("fwrite"));
        IR_Type *fwrite_return_type = ((IR_Procedure_Type *)((IR_Pointer_Type *)fwrite_callee->type)->pointee)->return_type;
        IR_Call_Instruction *fwrite_call = IR_Call_Instruction__create(fwrite_return_type->kind != IR_TYPE_KIND__NOTHING ? Lowerer__fresh_name(self) : NULL, fwrite_return_type, fwrite_callee);
        IR_Value_List__append(&fwrite_call->super.operands, &buffer->super.result);
        IR_Value_List__append(&fwrite_call->super.operands, &size->super.result);
        IR_Value_List__append(&fwrite_call->super.operands, &count->super.result);
        IR_Value_List__append(&fwrite_call->super.operands, &file->super.result);
        IR_Block__append_instruction(self->block, (IR_Instruction *)fwrite_call);

        IR_Const_Instruction *status = IR_Const_Instruction__create(Lowerer__fresh_name(self), IR_Type__get(IR_TYPE_KIND__I32), 1, NULL);
        IR_Block__append_instruction(self->block, (IR_Instruction *)status);
        IR_Value *exit_callee = Lowerer__find_global(self, String__create_from("exit"));
        IR_Type *exit_return_type = ((IR_Procedure_Type *)((IR_Pointer_Type *)exit_callee->type)->pointee)->return_type;
        IR_Call_Instruction *exit_call = IR_Call_Instruction__create(exit_return_type->kind != IR_TYPE_KIND__NOTHING ? Lowerer__fresh_name(self) : NULL, exit_return_type, exit_callee);
        IR_Value_List__append(&exit_call->super.operands, &status->super.result);
        IR_Block__append_instruction(self->block, (IR_Instruction *)exit_call);
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
        IR_Variable *variable = Lowerer__declare_variable(self, (Checked_Symbol *)variable_statement->variable, Lowerer__lower_type(self, variable_statement->variable->super.type));
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
    Checked_Procedure_Type *checked_procedure_type = ((Checked_Procedure_Type *)procedure_symbol->super.type);
    IR_Type *return_type = Lowerer__lower_type(self, checked_procedure_type->return_type);

    size_t parameter_count;
    IR_Type **parameter_types = Lowerer__lower_parameter_types(self, checked_procedure_type, &parameter_count);

    IR_Procedure *procedure = IR_Procedure__create(Lowerer__procedure_name(self, procedure_symbol), parameter_types, parameter_count, return_type);
    procedure->is_method = procedure_symbol->receiver_type != NULL;
    IR_Program__append_procedure(self->program, procedure);
    IR_Value_List__append(&self->globals, &procedure->super.value);

    size_t parameter_index = 0;
    for (Checked_Procedure_Parameter *parameter = checked_procedure_type->first_parameter; parameter != NULL; parameter = parameter->next_parameter) {
        IR_Value_List__append(&procedure->parameters, IR_Value__create(IR_VALUE_KIND__PARAMETER, IR__value_name('%', parameter->name), parameter_types[parameter_index++]));
    }
}

void Lowerer__declare_external_procedure(Lowerer *self, Checked_Procedure_Symbol *procedure_symbol) {
    Checked_Procedure_Type *checked_procedure_type = ((Checked_Procedure_Type *)procedure_symbol->super.type);
    IR_Type *return_type = Lowerer__lower_type(self, checked_procedure_type->return_type);

    size_t parameter_count;
    IR_Type **parameter_types = Lowerer__lower_parameter_types(self, checked_procedure_type, &parameter_count);

    IR_Type *procedure_type = (IR_Type *)IR_Procedure_Type__create(parameter_types, parameter_count, return_type);
    IR_Global *global = IR_External_Global__create(Lowerer__procedure_name(self, procedure_symbol), (IR_Type *)IR_Pointer_Type__create(procedure_type));
    IR_Program__append_global(self->program, global);
    IR_Value_List__append(&self->globals, &global->super.value);
}

void Lowerer__declare_external_variable(Lowerer *self, Checked_Variable_Symbol *variable_symbol) {
    IR_Type *type = Lowerer__lower_type(self, variable_symbol->super.type);
    IR_Global *global = IR_External_Global__create(Lowerer__variable_name(variable_symbol), (IR_Type *)IR_Pointer_Type__create(type));
    IR_Program__append_global(self->program, global);
    IR_Value_List__append(&self->globals, &global->super.value);
}

IR_Const_Payload *Lowerer__lower_constant(Lowerer *self, Checked_Expression *expression) {
    switch (expression->kind) {
    case CHECKED_EXPRESSION_KIND__BOOL:
        return IR_Const_Payload__create(((Checked_Bool_Expression *)expression)->value ? 1 : 0, NULL);
    case CHECKED_EXPRESSION_KIND__CHARACTER:
        return IR_Const_Payload__create((uint64_t)(uint8_t)((Checked_Character_Expression *)expression)->value, ((Checked_Character_Expression *)expression)->literal);
    case CHECKED_EXPRESSION_KIND__INTEGER:
        return IR_Const_Payload__create(((Checked_Integer_Expression *)expression)->value, ((Checked_Integer_Expression *)expression)->literal);
    case CHECKED_EXPRESSION_KIND__NULL:
        return IR_Const_Payload__create(0, NULL);
    default:
        pWriter__begin_location_message(stderr_writer, expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Lowering not supported yet: non-constant global initializer");
        pWriter__end_line(stderr_writer);
        panic();
    }
}

void Lowerer__declare_global_variable(Lowerer *self, Checked_Variable_Symbol *variable_symbol) {
    IR_Type *type = Lowerer__lower_type(self, variable_symbol->super.type);
    IR_Type *pointer_type = (IR_Type *)IR_Pointer_Type__create(type);
    IR_Global *global;
    if (variable_symbol->statement->expression == NULL) {
        global = IR_Global__create(Lowerer__variable_name(variable_symbol), pointer_type);
    } else {
        global = IR_Constant_Global__create(Lowerer__variable_name(variable_symbol), pointer_type, Lowerer__lower_constant(self, variable_symbol->statement->expression));
    }
    IR_Program__append_global(self->program, global);
    IR_Value_List__append(&self->globals, &global->super.value);
}

void Lowerer__define_procedure(Lowerer *self, Checked_Procedure_Symbol *procedure_symbol) {
    if (procedure_symbol->checked_block_statement == NULL) {
        return;
    }

    IR_Procedure *procedure = (IR_Procedure *)Lowerer__find_global(self, Lowerer__procedure_name(self, procedure_symbol));

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

void Lowerer__define_main(Lowerer *self, Checked_Procedure_Symbol *main_symbol) {
    IR_Procedure *main_procedure = (IR_Procedure *)Lowerer__find_global(self, Lowerer__procedure_name(self, main_symbol));

    size_t parameter_count = main_procedure->parameters.size;
    IR_Type **parameter_types = parameter_count > 0 ? (IR_Type **)malloc(parameter_count * sizeof(IR_Type *)) : NULL;
    for (size_t i = 0; i < parameter_count; i++) {
        parameter_types[i] = main_procedure->parameters.values[i]->type;
    }

    IR_Procedure *procedure = IR_Procedure__create(String__create_from("main"), parameter_types, parameter_count, main_procedure->return_type);
    for (size_t i = 0; i < parameter_count; i++) {
        IR_Value *parameter = main_procedure->parameters.values[i];
        IR_Value_List__append(&procedure->parameters, IR_Value__create(IR_VALUE_KIND__PARAMETER, parameter->name, parameter->type));
    }
    IR_Program__append_procedure(self->program, procedure);

    IR_Block *block = IR_Block__create(1);
    IR_Procedure__append_block(procedure, block);

    IR_Type *return_type = main_procedure->return_type;
    String *result_name = return_type->kind != IR_TYPE_KIND__NOTHING ? String__create_from("%1") : NULL;
    IR_Call_Instruction *call = IR_Call_Instruction__create(result_name, return_type, &main_procedure->super.value);
    for (size_t i = 0; i < parameter_count; i++) {
        IR_Value_List__append(&call->super.operands, procedure->parameters.values[i]);
    }
    IR_Block__append_instruction(block, (IR_Instruction *)call);
    IR_Block__append_instruction(block, (IR_Instruction *)IR_Ret_Instruction__create(return_type->kind != IR_TYPE_KIND__NOTHING ? &call->super.result : NULL));
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
    lowerer.malloc_callee = NULL;
    lowerer.string_type = NULL;
    lowerer.string_counter = 0;

    for (Checked_Symbols *symbols = checked_source->symbols; symbols != NULL; symbols = symbols->parent) {
        for (Checked_Symbol *symbol = symbols->first_symbol; symbol != NULL; symbol = symbol->next_symbol) {
            if (symbol->kind == CHECKED_SYMBOL_KIND__TYPE) {
                Checked_Named_Type *named_type = ((Checked_Type_Symbol *)symbol)->named_type;
                if (named_type->super.kind == CHECKED_TYPE_KIND__STRUCT && String__equals_cstring(named_type->name, "String")) {
                    lowerer.string_type = (Checked_Struct_Type *)named_type;
                }
            }
        }
    }

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
                Lowerer__declare_global_variable(&lowerer, variable_symbol);
            }
        }
    }

    for (Checked_Symbol *symbol = checked_source->symbols->first_symbol; symbol != NULL; symbol = symbol->next_symbol) {
        if (symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE && Checked_Procedure_Symbol__is_lowerable((Checked_Procedure_Symbol *)symbol)) {
            Lowerer__define_procedure(&lowerer, (Checked_Procedure_Symbol *)symbol);
        }
    }

    for (Checked_Symbol *symbol = checked_source->symbols->first_symbol; symbol != NULL; symbol = symbol->next_symbol) {
        if (symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE) {
            Checked_Procedure_Symbol *procedure_symbol = (Checked_Procedure_Symbol *)symbol;
            if (procedure_symbol->super.package == checked_source->first_package && procedure_symbol->receiver_type == NULL && String__equals_cstring(procedure_symbol->procedure_name, "main")) {
                Lowerer__define_main(&lowerer, procedure_symbol);
                break;
            }
        }
    }

    return lowerer.program;
}
