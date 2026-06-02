#include "IR.h"
#include "Builtins.h"
#include "File.h"

static IR_Type IR_TYPES[] = {
    [IR_TYPE_KIND__ANY] = {.kind = IR_TYPE_KIND__ANY},
    [IR_TYPE_KIND__BOOL] = {.kind = IR_TYPE_KIND__BOOL},
    [IR_TYPE_KIND__I8] = {.kind = IR_TYPE_KIND__I8},
    [IR_TYPE_KIND__I16] = {.kind = IR_TYPE_KIND__I16},
    [IR_TYPE_KIND__I32] = {.kind = IR_TYPE_KIND__I32},
    [IR_TYPE_KIND__I64] = {.kind = IR_TYPE_KIND__I64},
    [IR_TYPE_KIND__ISIZE] = {.kind = IR_TYPE_KIND__ISIZE},
    [IR_TYPE_KIND__U8] = {.kind = IR_TYPE_KIND__U8},
    [IR_TYPE_KIND__U16] = {.kind = IR_TYPE_KIND__U16},
    [IR_TYPE_KIND__U32] = {.kind = IR_TYPE_KIND__U32},
    [IR_TYPE_KIND__U64] = {.kind = IR_TYPE_KIND__U64},
    [IR_TYPE_KIND__USIZE] = {.kind = IR_TYPE_KIND__USIZE},
    [IR_TYPE_KIND__NOTHING] = {.kind = IR_TYPE_KIND__NOTHING},
};

IR_Type *IR_Type__get(IR_Type_Kind kind) {
    return &IR_TYPES[kind];
}

size_t IR_Type__alignment(IR_Type *type) {
    size_t size = IR_Type__size(type);
    if (size == 0) {
        return 1;
    }
    if (size >= 8) {
        return 8;
    }
    return size;
}

size_t IR_Type__size(IR_Type *type) {
    switch (type->kind) {
    case IR_TYPE_KIND__BOOL:
    case IR_TYPE_KIND__I8:
    case IR_TYPE_KIND__U8:
        return 1;
    case IR_TYPE_KIND__I16:
    case IR_TYPE_KIND__U16:
        return 2;
    case IR_TYPE_KIND__I32:
    case IR_TYPE_KIND__U32:
        return 4;
    case IR_TYPE_KIND__I64:
    case IR_TYPE_KIND__U64:
    case IR_TYPE_KIND__ISIZE:
    case IR_TYPE_KIND__USIZE:
    case IR_TYPE_KIND__MULTI_POINTER:
    case IR_TYPE_KIND__POINTER:
    case IR_TYPE_KIND__PROCEDURE:
        return 8;
    default:
        pWriter__write__cstring(stderr_writer, "Lowering not supported yet: size of type kind ");
        pWriter__write__int64(stderr_writer, type->kind);
        pWriter__end_line(stderr_writer);
        panic();
    }
}

static IR_Type *IR_Type__create_kind(IR_Type_Kind kind, size_t size) {
    IR_Type *type = (IR_Type *)malloc(size);
    type->kind = kind;
    return type;
}

IR_Opaque_Type *IR_Opaque_Type__create(String *name) {
    IR_Opaque_Type *type = (IR_Opaque_Type *)IR_Type__create_kind(IR_TYPE_KIND__OPAQUE, sizeof(IR_Opaque_Type));
    type->super.name = name;
    type->super.next_type = NULL;
    return type;
}

IR_Multi_Pointer_Type *IR_Multi_Pointer_Type__create(IR_Type *pointee) {
    IR_Multi_Pointer_Type *type = (IR_Multi_Pointer_Type *)IR_Type__create_kind(IR_TYPE_KIND__MULTI_POINTER, sizeof(IR_Multi_Pointer_Type));
    type->pointee = pointee;
    return type;
}

IR_Pointer_Type *IR_Pointer_Type__create(IR_Type *pointee) {
    IR_Pointer_Type *type = (IR_Pointer_Type *)IR_Type__create_kind(IR_TYPE_KIND__POINTER, sizeof(IR_Pointer_Type));
    type->pointee = pointee;
    return type;
}

IR_Procedure_Type *IR_Procedure_Type__create(IR_Type **parameter_types, size_t parameter_count, IR_Type *return_type) {
    IR_Procedure_Type *type = (IR_Procedure_Type *)IR_Type__create_kind(IR_TYPE_KIND__PROCEDURE, sizeof(IR_Procedure_Type));
    type->parameter_types = parameter_types;
    type->parameter_count = parameter_count;
    type->return_type = return_type;
    return type;
}

String *IR__value_name(char sigil, String *name) {
    String *result = String__create();
    String__append_char(result, sigil);
    String__append_string(result, name);
    return result;
}

bool String__equals__value_name(String *self, char sigil, String *name) {
    if (self->length != name->length + 1 || self->data[0] != sigil) {
        return false;
    }
    for (size_t i = 0; i < name->length; i++) {
        if (self->data[i + 1] != name->data[i]) {
            return false;
        }
    }
    return true;
}

IR_Variable *IR_Variable__create(String *name, IR_Type *type) {
    IR_Variable *variable = (IR_Variable *)malloc(sizeof(IR_Variable));
    variable->super.value.kind = IR_VALUE_KIND__INSTRUCTION_RESULT;
    variable->super.value.name = IR__value_name('%', name);
    variable->super.value.type = type;
    variable->super.value.variable = NULL;
    variable->version = 0;
    return variable;
}

IR_Global *IR_Global__create(String *name, IR_Type *type) {
    IR_Global *global = (IR_Global *)malloc(sizeof(IR_Global));
    global->super.value.kind = IR_VALUE_KIND__GLOBAL;
    global->super.value.name = IR__value_name('$', name);
    global->super.value.type = type;
    global->super.value.variable = NULL;
    global->next_global = NULL;
    return global;
}

IR_Value *IR_Value__create(IR_Value_Kind kind, String *name, IR_Type *type) {
    IR_Value *value = (IR_Value *)malloc(sizeof(IR_Value));
    value->kind = kind;
    value->name = name;
    value->type = type;
    value->variable = NULL;
    return value;
}

void IR_Value_List__append(IR_Value_List *self, IR_Value *value) {
    if (self->size == self->capacity) {
        self->capacity = self->capacity == 0 ? 4 : self->capacity * 2;
        self->values = (IR_Value **)realloc(self->values, self->capacity * sizeof(IR_Value *));
    }
    self->values[self->size++] = value;
}

void IR_Block_List__append(IR_Block_List *self, IR_Block *block) {
    if (self->size == self->capacity) {
        self->capacity = self->capacity == 0 ? 4 : self->capacity * 2;
        self->blocks = (IR_Block **)realloc(self->blocks, self->capacity * sizeof(IR_Block *));
    }
    self->blocks[self->size++] = block;
}

static IR_Instruction *IR_Instruction__create_kind(IR_Instruction_Kind kind, size_t size) {
    IR_Instruction *instruction = (IR_Instruction *)malloc(size);
    instruction->kind = kind;
    instruction->operands = (IR_Value_List){.values = NULL, .size = 0, .capacity = 0};
    instruction->next_instruction = NULL;
    return instruction;
}

IR_Alloc_Instruction *IR_Alloc_Instruction__create(IR_Variable *variable) {
    IR_Alloc_Instruction *instruction = (IR_Alloc_Instruction *)IR_Instruction__create_kind(IR_INSTRUCTION_KIND__ALLOC, sizeof(IR_Alloc_Instruction));
    String *result_name = String__create_copy(variable->super.value.name);
    String__append_cstring(result_name, ".ptr");
    instruction->super.result.kind = IR_VALUE_KIND__INSTRUCTION_RESULT;
    instruction->super.result.name = result_name;
    instruction->super.result.type = (IR_Type *)IR_Pointer_Type__create(variable->super.value.type);
    instruction->super.result.variable = variable;
    instruction->allocated_type = variable->super.value.type;
    return instruction;
}

IR_Array_Offset_Instruction *IR_Array_Offset_Instruction__create(String *result_name, IR_Type *result_type, IR_Value *pointer, IR_Value *index) {
    IR_Array_Offset_Instruction *instruction = (IR_Array_Offset_Instruction *)IR_Instruction__create_kind(IR_INSTRUCTION_KIND__ARRAY_OFFSET, sizeof(IR_Array_Offset_Instruction));
    instruction->super.result.kind = IR_VALUE_KIND__INSTRUCTION_RESULT;
    instruction->super.result.name = result_name;
    instruction->super.result.type = result_type;
    instruction->super.result.variable = NULL;
    IR_Value_List__append(&instruction->super.operands, pointer);
    IR_Value_List__append(&instruction->super.operands, index);
    return instruction;
}

IR_Br_Instruction *IR_Br_Instruction__create(IR_Value *condition, IR_Block *true_block, IR_Block *false_block) {
    IR_Br_Instruction *instruction = (IR_Br_Instruction *)IR_Instruction__create_kind(IR_INSTRUCTION_KIND__BR, sizeof(IR_Br_Instruction));
    instruction->condition = condition;
    instruction->true_block = true_block;
    instruction->false_block = false_block;
    return instruction;
}

IR_Jmp_Instruction *IR_Jmp_Instruction__create(IR_Block *block) {
    IR_Jmp_Instruction *instruction = (IR_Jmp_Instruction *)IR_Instruction__create_kind(IR_INSTRUCTION_KIND__JMP, sizeof(IR_Jmp_Instruction));
    instruction->block = block;
    return instruction;
}

IR_Call_Instruction *IR_Call_Instruction__create(String *result_name, IR_Type *result_type, IR_Value *callee) {
    IR_Call_Instruction *instruction = (IR_Call_Instruction *)IR_Instruction__create_kind(IR_INSTRUCTION_KIND__CALL, sizeof(IR_Call_Instruction));
    instruction->super.result.kind = IR_VALUE_KIND__INSTRUCTION_RESULT;
    instruction->super.result.name = result_name;
    instruction->super.result.type = result_type;
    instruction->super.result.variable = NULL;
    IR_Value_List__append(&instruction->super.operands, callee);
    return instruction;
}

IR_Cast_Instruction *IR_Cast_Instruction__create(String *result_name, IR_Type *result_type, IR_Value *value) {
    IR_Cast_Instruction *instruction = (IR_Cast_Instruction *)IR_Instruction__create_kind(IR_INSTRUCTION_KIND__CAST, sizeof(IR_Cast_Instruction));
    instruction->super.result.kind = IR_VALUE_KIND__INSTRUCTION_RESULT;
    instruction->super.result.name = result_name;
    instruction->super.result.type = result_type;
    instruction->super.result.variable = NULL;
    IR_Value_List__append(&instruction->super.operands, value);
    return instruction;
}

IR_Const_Instruction *IR_Const_Instruction__create(String *result_name, IR_Type *result_type, uint64_t value, Token *literal) {
    IR_Const_Instruction *instruction = (IR_Const_Instruction *)IR_Instruction__create_kind(IR_INSTRUCTION_KIND__CONST, sizeof(IR_Const_Instruction));
    instruction->super.result.kind = IR_VALUE_KIND__INSTRUCTION_RESULT;
    instruction->super.result.name = result_name;
    instruction->super.result.type = result_type;
    instruction->super.result.variable = NULL;
    instruction->value = value;
    instruction->literal = literal;
    return instruction;
}

IR_Load_Instruction *IR_Load_Instruction__create(String *result_name, IR_Type *result_type, IR_Value *pointer) {
    IR_Load_Instruction *instruction = (IR_Load_Instruction *)IR_Instruction__create_kind(IR_INSTRUCTION_KIND__LOAD, sizeof(IR_Load_Instruction));
    instruction->super.result.kind = IR_VALUE_KIND__INSTRUCTION_RESULT;
    instruction->super.result.name = result_name;
    instruction->super.result.type = result_type;
    instruction->super.result.variable = NULL;
    IR_Value_List__append(&instruction->super.operands, pointer);
    return instruction;
}

IR_Neg_Instruction *IR_Neg_Instruction__create(String *result_name, IR_Type *result_type, IR_Value *value) {
    IR_Neg_Instruction *instruction = (IR_Neg_Instruction *)IR_Instruction__create_kind(IR_INSTRUCTION_KIND__NEG, sizeof(IR_Neg_Instruction));
    instruction->super.result.kind = IR_VALUE_KIND__INSTRUCTION_RESULT;
    instruction->super.result.name = result_name;
    instruction->super.result.type = result_type;
    instruction->super.result.variable = NULL;
    IR_Value_List__append(&instruction->super.operands, value);
    return instruction;
}

IR_Not_Instruction *IR_Not_Instruction__create(String *result_name, IR_Type *result_type, IR_Value *value) {
    IR_Not_Instruction *instruction = (IR_Not_Instruction *)IR_Instruction__create_kind(IR_INSTRUCTION_KIND__NOT, sizeof(IR_Not_Instruction));
    instruction->super.result.kind = IR_VALUE_KIND__INSTRUCTION_RESULT;
    instruction->super.result.name = result_name;
    instruction->super.result.type = result_type;
    instruction->super.result.variable = NULL;
    IR_Value_List__append(&instruction->super.operands, value);
    return instruction;
}

IR_Phi_Instruction *IR_Phi_Instruction__create(String *result_name, IR_Type *result_type) {
    IR_Phi_Instruction *instruction = (IR_Phi_Instruction *)IR_Instruction__create_kind(IR_INSTRUCTION_KIND__PHI, sizeof(IR_Phi_Instruction));
    instruction->super.result.kind = IR_VALUE_KIND__INSTRUCTION_RESULT;
    instruction->super.result.name = result_name;
    instruction->super.result.type = result_type;
    instruction->super.result.variable = NULL;
    instruction->blocks = (IR_Block_List){.blocks = NULL, .size = 0, .capacity = 0};
    return instruction;
}

IR_Ret_Instruction *IR_Ret_Instruction__create(IR_Value *value) {
    IR_Ret_Instruction *instruction = (IR_Ret_Instruction *)IR_Instruction__create_kind(IR_INSTRUCTION_KIND__RET, sizeof(IR_Ret_Instruction));
    if (value != NULL) {
        IR_Value_List__append(&instruction->super.operands, value);
    }
    return instruction;
}

IR_Binary_Instruction *IR_Binary_Instruction__create(IR_Instruction_Kind kind, String *result_name, IR_Type *result_type, IR_Value *left, IR_Value *right) {
    IR_Binary_Instruction *instruction = (IR_Binary_Instruction *)IR_Instruction__create_kind(kind, sizeof(IR_Binary_Instruction));
    instruction->super.result.kind = IR_VALUE_KIND__INSTRUCTION_RESULT;
    instruction->super.result.name = result_name;
    instruction->super.result.type = result_type;
    instruction->super.result.variable = NULL;
    IR_Value_List__append(&instruction->super.operands, left);
    IR_Value_List__append(&instruction->super.operands, right);
    return instruction;
}

IR_Store_Instruction *IR_Store_Instruction__create(IR_Value *pointer, IR_Value *value) {
    IR_Store_Instruction *instruction = (IR_Store_Instruction *)IR_Instruction__create_kind(IR_INSTRUCTION_KIND__STORE, sizeof(IR_Store_Instruction));
    IR_Value_List__append(&instruction->super.operands, pointer);
    IR_Value_List__append(&instruction->super.operands, value);
    return instruction;
}

IR_Block *IR_Block__create(size_t label) {
    IR_Block *block = (IR_Block *)malloc(sizeof(IR_Block));
    block->label = label;
    block->first_instruction = NULL;
    block->last_instruction = NULL;
    block->next_block = NULL;
    return block;
}

void IR_Block__append_instruction(IR_Block *self, IR_Instruction *instruction) {
    if (self->first_instruction == NULL) {
        self->first_instruction = instruction;
    } else {
        self->last_instruction->next_instruction = instruction;
    }
    self->last_instruction = instruction;
}

bool IR_Block__is_terminated(IR_Block *self) {
    if (self->last_instruction == NULL) {
        return false;
    }
    switch (self->last_instruction->kind) {
    case IR_INSTRUCTION_KIND__BR:
    case IR_INSTRUCTION_KIND__JMP:
    case IR_INSTRUCTION_KIND__RET:
        return true;
    default:
        return false;
    }
}

IR_Procedure *IR_Procedure__create(String *name, IR_Type **parameter_types, size_t parameter_count, IR_Type *return_type) {
    IR_Procedure *procedure = (IR_Procedure *)malloc(sizeof(IR_Procedure));
    IR_Procedure_Type *procedure_type = IR_Procedure_Type__create(parameter_types, parameter_count, return_type);
    procedure->super.value.kind = IR_VALUE_KIND__PROCEDURE;
    procedure->super.value.name = IR__value_name('$', name);
    procedure->super.value.type = (IR_Type *)IR_Pointer_Type__create((IR_Type *)procedure_type);
    procedure->super.value.variable = NULL;
    procedure->parameters = (IR_Value_List){.values = NULL, .size = 0, .capacity = 0};
    procedure->return_type = return_type;
    procedure->first_block = NULL;
    procedure->last_block = NULL;
    procedure->next_procedure = NULL;
    return procedure;
}

void IR_Procedure__append_block(IR_Procedure *self, IR_Block *block) {
    if (self->first_block == NULL) {
        self->first_block = block;
    } else {
        self->last_block->next_block = block;
    }
    self->last_block = block;
}

IR_Program *IR_Program__create() {
    IR_Program *program = (IR_Program *)malloc(sizeof(IR_Program));
    program->first_type = NULL;
    program->last_type = NULL;
    program->first_global = NULL;
    program->last_global = NULL;
    program->first_procedure = NULL;
    program->last_procedure = NULL;
    return program;
}

void IR_Program__append_global(IR_Program *self, IR_Global *global) {
    if (self->first_global == NULL) {
        self->first_global = global;
    } else {
        self->last_global->next_global = global;
    }
    self->last_global = global;
}

void IR_Program__append_type(IR_Program *self, IR_Named_Type *type) {
    if (self->first_type == NULL) {
        self->first_type = type;
    } else {
        self->last_type->next_type = type;
    }
    self->last_type = type;
}

void IR_Program__append_procedure(IR_Program *self, IR_Procedure *procedure) {
    if (self->first_procedure == NULL) {
        self->first_procedure = procedure;
    } else {
        self->last_procedure->next_procedure = procedure;
    }
    self->last_procedure = procedure;
}

Writer *pWriter__write__ir_type(Writer *self, IR_Type *type) {
    switch (type->kind) {
    case IR_TYPE_KIND__ANY:
        return pWriter__write__cstring(self, "Any");
    case IR_TYPE_KIND__BOOL:
        return pWriter__write__cstring(self, "bool");
    case IR_TYPE_KIND__I8:
        return pWriter__write__cstring(self, "i8");
    case IR_TYPE_KIND__I16:
        return pWriter__write__cstring(self, "i16");
    case IR_TYPE_KIND__I32:
        return pWriter__write__cstring(self, "i32");
    case IR_TYPE_KIND__I64:
        return pWriter__write__cstring(self, "i64");
    case IR_TYPE_KIND__ISIZE:
        return pWriter__write__cstring(self, "isize");
    case IR_TYPE_KIND__U8:
        return pWriter__write__cstring(self, "u8");
    case IR_TYPE_KIND__U16:
        return pWriter__write__cstring(self, "u16");
    case IR_TYPE_KIND__U32:
        return pWriter__write__cstring(self, "u32");
    case IR_TYPE_KIND__U64:
        return pWriter__write__cstring(self, "u64");
    case IR_TYPE_KIND__USIZE:
        return pWriter__write__cstring(self, "usize");
    case IR_TYPE_KIND__OPAQUE:
        return pWriter__write__string(self, ((IR_Named_Type *)type)->name);
    case IR_TYPE_KIND__MULTI_POINTER:
        pWriter__write__cstring(self, "[*]");
        return pWriter__write__ir_type(self, ((IR_Multi_Pointer_Type *)type)->pointee);
    case IR_TYPE_KIND__POINTER:
        pWriter__write__char(self, '[');
        pWriter__write__ir_type(self, ((IR_Pointer_Type *)type)->pointee);
        return pWriter__write__char(self, ']');
    case IR_TYPE_KIND__PROCEDURE: {
        IR_Procedure_Type *procedure_type = (IR_Procedure_Type *)type;
        pWriter__write__cstring(self, "proc (");
        for (size_t i = 0; i < procedure_type->parameter_count; i++) {
            if (i > 0) {
                pWriter__write__cstring(self, ", ");
            }
            pWriter__write__ir_type(self, procedure_type->parameter_types[i]);
        }
        pWriter__write__char(self, ')');
        if (procedure_type->return_type->kind != IR_TYPE_KIND__NOTHING) {
            pWriter__write__cstring(self, ": ");
            pWriter__write__ir_type(self, procedure_type->return_type);
        }
        return self;
    }
    default:
        pWriter__write__cstring(stderr_writer, "Cannot print IR type kind: ");
        pWriter__write__int64(stderr_writer, type->kind);
        pWriter__end_line(stderr_writer);
        panic();
    }
}

Writer *pWriter__write__ir_value_reference(Writer *self, IR_Value *value) {
    return pWriter__write__string(self, value->name);
}

Writer *pWriter__write__ir_value_definition(Writer *self, IR_Value *value) {
    pWriter__write__ir_value_reference(self, value);
    pWriter__write__cstring(self, ": ");
    return pWriter__write__ir_type(self, value->type);
}

Writer *pWriter__write__ir_instruction(Writer *self, IR_Instruction *instruction) {
    switch (instruction->kind) {
    case IR_INSTRUCTION_KIND__ALLOC:
        pWriter__write__ir_value_definition(self, &instruction->result);
        pWriter__write__cstring(self, " = alloc ");
        return pWriter__write__ir_type(self, ((IR_Alloc_Instruction *)instruction)->allocated_type);
    case IR_INSTRUCTION_KIND__ARRAY_OFFSET:
        pWriter__write__ir_value_definition(self, &instruction->result);
        pWriter__write__cstring(self, " = offset ");
        pWriter__write__ir_value_reference(self, instruction->operands.values[0]);
        pWriter__write__char(self, ' ');
        return pWriter__write__ir_value_reference(self, instruction->operands.values[1]);
    case IR_INSTRUCTION_KIND__BR: {
        IR_Br_Instruction *br_instruction = (IR_Br_Instruction *)instruction;
        pWriter__write__cstring(self, "br ");
        pWriter__write__ir_value_reference(self, br_instruction->condition);
        pWriter__write__cstring(self, " @");
        pWriter__write__uint64(self, br_instruction->true_block->label);
        pWriter__write__cstring(self, " @");
        return pWriter__write__uint64(self, br_instruction->false_block->label);
    }
    case IR_INSTRUCTION_KIND__CALL:
        if (instruction->result.type->kind != IR_TYPE_KIND__NOTHING) {
            pWriter__write__ir_value_definition(self, &instruction->result);
            pWriter__write__cstring(self, " = ");
        }
        pWriter__write__cstring(self, "call");
        for (size_t i = 0; i < instruction->operands.size; i++) {
            pWriter__write__char(self, ' ');
            pWriter__write__ir_value_reference(self, instruction->operands.values[i]);
        }
        return self;
    case IR_INSTRUCTION_KIND__CAST:
        pWriter__write__ir_value_definition(self, &instruction->result);
        pWriter__write__cstring(self, " = cast ");
        return pWriter__write__ir_value_reference(self, instruction->operands.values[0]);
    case IR_INSTRUCTION_KIND__CONST:
        pWriter__write__ir_value_definition(self, &instruction->result);
        pWriter__write__cstring(self, " = const ");
        if (instruction->result.type->kind == IR_TYPE_KIND__BOOL) {
            return pWriter__write__cstring(self, ((IR_Const_Instruction *)instruction)->value ? "true" : "false");
        }
        if (instruction->result.type->kind == IR_TYPE_KIND__POINTER) {
            return pWriter__write__cstring(self, "null");
        }
        if (((IR_Const_Instruction *)instruction)->literal != NULL) {
            return pWriter__write__string(self, ((IR_Const_Instruction *)instruction)->literal->lexeme);
        }
        return pWriter__write__uint64(self, ((IR_Const_Instruction *)instruction)->value);
    case IR_INSTRUCTION_KIND__JMP:
        pWriter__write__cstring(self, "jmp @");
        return pWriter__write__uint64(self, ((IR_Jmp_Instruction *)instruction)->block->label);
    case IR_INSTRUCTION_KIND__LOAD:
        pWriter__write__ir_value_definition(self, &instruction->result);
        pWriter__write__cstring(self, " = load ");
        return pWriter__write__ir_value_reference(self, instruction->operands.values[0]);
    case IR_INSTRUCTION_KIND__NEG:
        pWriter__write__ir_value_definition(self, &instruction->result);
        pWriter__write__cstring(self, " = neg ");
        return pWriter__write__ir_value_reference(self, instruction->operands.values[0]);
    case IR_INSTRUCTION_KIND__NOT:
        pWriter__write__ir_value_definition(self, &instruction->result);
        pWriter__write__cstring(self, " = not ");
        return pWriter__write__ir_value_reference(self, instruction->operands.values[0]);
    case IR_INSTRUCTION_KIND__PHI: {
        IR_Phi_Instruction *phi_instruction = (IR_Phi_Instruction *)instruction;
        pWriter__write__ir_value_definition(self, &instruction->result);
        pWriter__write__cstring(self, " = phi");
        for (size_t i = 0; i < instruction->operands.size; i++) {
            pWriter__write__cstring(self, " @");
            pWriter__write__uint64(self, phi_instruction->blocks.blocks[i]->label);
            pWriter__write__char(self, ' ');
            pWriter__write__ir_value_reference(self, instruction->operands.values[i]);
        }
        return self;
    }
    case IR_INSTRUCTION_KIND__RET:
        pWriter__write__cstring(self, "ret");
        for (size_t i = 0; i < instruction->operands.size; i++) {
            pWriter__write__char(self, ' ');
            pWriter__write__ir_value_reference(self, instruction->operands.values[i]);
        }
        return self;
    case IR_INSTRUCTION_KIND__STORE:
        pWriter__write__cstring(self, "store");
        for (size_t i = 0; i < instruction->operands.size; i++) {
            pWriter__write__char(self, ' ');
            pWriter__write__ir_value_reference(self, instruction->operands.values[i]);
        }
        return self;
    case IR_INSTRUCTION_KIND__ADD:
    case IR_INSTRUCTION_KIND__CMP_EQ:
    case IR_INSTRUCTION_KIND__CMP_GE:
    case IR_INSTRUCTION_KIND__CMP_GT:
    case IR_INSTRUCTION_KIND__CMP_LE:
    case IR_INSTRUCTION_KIND__CMP_LT:
    case IR_INSTRUCTION_KIND__CMP_NE:
    case IR_INSTRUCTION_KIND__DIV:
    case IR_INSTRUCTION_KIND__MOD:
    case IR_INSTRUCTION_KIND__MUL:
    case IR_INSTRUCTION_KIND__SUB:
        pWriter__write__ir_value_definition(self, &instruction->result);
        switch (instruction->kind) {
        case IR_INSTRUCTION_KIND__ADD:
            pWriter__write__cstring(self, " = add");
            break;
        case IR_INSTRUCTION_KIND__CMP_EQ:
            pWriter__write__cstring(self, " = cmp_eq");
            break;
        case IR_INSTRUCTION_KIND__CMP_GE:
            pWriter__write__cstring(self, " = cmp_ge");
            break;
        case IR_INSTRUCTION_KIND__CMP_GT:
            pWriter__write__cstring(self, " = cmp_gt");
            break;
        case IR_INSTRUCTION_KIND__CMP_LE:
            pWriter__write__cstring(self, " = cmp_le");
            break;
        case IR_INSTRUCTION_KIND__CMP_LT:
            pWriter__write__cstring(self, " = cmp_lt");
            break;
        case IR_INSTRUCTION_KIND__CMP_NE:
            pWriter__write__cstring(self, " = cmp_ne");
            break;
        case IR_INSTRUCTION_KIND__DIV:
            pWriter__write__cstring(self, " = div");
            break;
        case IR_INSTRUCTION_KIND__MOD:
            pWriter__write__cstring(self, " = mod");
            break;
        case IR_INSTRUCTION_KIND__MUL:
            pWriter__write__cstring(self, " = mul");
            break;
        default:
            pWriter__write__cstring(self, " = sub");
            break;
        }
        for (size_t i = 0; i < instruction->operands.size; i++) {
            pWriter__write__char(self, ' ');
            pWriter__write__ir_value_reference(self, instruction->operands.values[i]);
        }
        return self;
    default:
        pWriter__write__cstring(stderr_writer, "Cannot print IR instruction kind: ");
        pWriter__write__int64(stderr_writer, instruction->kind);
        pWriter__end_line(stderr_writer);
        panic();
    }
}

Writer *pWriter__write__ir_block(Writer *self, IR_Block *block) {
    pWriter__write__char(self, '@');
    pWriter__write__uint64(self, block->label);
    pWriter__write__char(self, ':');
    pWriter__end_line(self);
    IR_Instruction *instruction = block->first_instruction;
    while (instruction != NULL) {
        pWriter__write__cstring(self, "  ");
        pWriter__write__ir_instruction(self, instruction);
        pWriter__end_line(self);
        instruction = instruction->next_instruction;
    }
    return self;
}

Writer *pWriter__write__ir_procedure(Writer *self, IR_Procedure *procedure) {
    pWriter__write__string(self, procedure->super.value.name);
    pWriter__write__char(self, '(');
    if (procedure->parameters.size > 0) {
        pWriter__write__ir_value_definition(self, procedure->parameters.values[0]);
        for (size_t i = 1; i < procedure->parameters.size; i++) {
            pWriter__write__cstring(self, ", ");
            pWriter__write__ir_value_definition(self, procedure->parameters.values[i]);
        }
    }
    pWriter__write__char(self, ')');
    if (procedure->return_type->kind != IR_TYPE_KIND__NOTHING) {
        pWriter__write__cstring(self, ": ");
        pWriter__write__ir_type(self, procedure->return_type);
    }
    pWriter__write__cstring(self, " {");
    pWriter__end_line(self);
    IR_Block *block = procedure->first_block;
    while (block != NULL) {
        pWriter__write__ir_block(self, block);
        block = block->next_block;
    }
    pWriter__write__char(self, '}');
    return pWriter__end_line(self);
}

Writer *pWriter__write__ir_global(Writer *self, IR_Global *global) {
    pWriter__write__string(self, global->super.value.name);
    pWriter__write__cstring(self, ": ");
    pWriter__write__ir_type(self, global->super.value.type);
    pWriter__write__cstring(self, " = external");
    return pWriter__end_line(self);
}

Writer *pWriter__write__ir_type_declaration(Writer *self, IR_Named_Type *type) {
    pWriter__write__cstring(self, "type ");
    pWriter__write__string(self, type->name);
    pWriter__write__cstring(self, " = ");
    switch (type->super.kind) {
    case IR_TYPE_KIND__OPAQUE:
        pWriter__write__cstring(self, "opaque");
        break;
    default:
        pWriter__write__cstring(stderr_writer, "Cannot print IR type declaration kind: ");
        pWriter__write__int64(stderr_writer, type->super.kind);
        pWriter__end_line(stderr_writer);
        panic();
    }
    return pWriter__end_line(self);
}

Writer *pWriter__write__ir_program(Writer *self, IR_Program *program) {
    for (IR_Named_Type *type = program->first_type; type != NULL; type = type->next_type) {
        pWriter__write__ir_type_declaration(self, type);
        pWriter__end_line(self);
    }
    for (IR_Global *global = program->first_global; global != NULL; global = global->next_global) {
        pWriter__write__ir_global(self, global);
        pWriter__end_line(self);
    }
    bool first = true;
    for (IR_Procedure *procedure = program->first_procedure; procedure != NULL; procedure = procedure->next_procedure) {
        if (!first) {
            pWriter__end_line(self);
        }
        first = false;
        pWriter__write__ir_procedure(self, procedure);
    }
    return self;
}
