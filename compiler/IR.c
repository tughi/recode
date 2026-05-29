#include "IR.h"
#include "Builtins.h"
#include "File.h"

static IR_Type IR_TYPES[] = {
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
};

IR_Type *IR_Type__get(IR_Type_Kind kind) {
    return &IR_TYPES[kind];
}

void IR_Value_List__append(IR_Value_List *self, IR_Value *value) {
    if (self->size == self->capacity) {
        self->capacity = self->capacity == 0 ? 4 : self->capacity * 2;
        self->values = (IR_Value **)realloc(self->values, self->capacity * sizeof(IR_Value *));
    }
    self->values[self->size++] = value;
}

static IR_Instruction *IR_Instruction__create(IR_Instruction_Kind kind) {
    IR_Instruction *instruction = (IR_Instruction *)malloc(sizeof(IR_Instruction));
    instruction->kind = kind;
    instruction->arguments = (IR_Value_List){.values = NULL, .size = 0, .capacity = 0};
    instruction->next_instruction = NULL;
    return instruction;
}

IR_Instruction *IR_Instruction__create_const(String *result_name, IR_Type *result_type, uint64_t value) {
    IR_Instruction *instruction = IR_Instruction__create(IR_INSTRUCTION_KIND__CONST);
    instruction->result.kind = IR_VALUE_KIND__INSTRUCTION_RESULT;
    instruction->result.name = result_name;
    instruction->result.type = result_type;
    instruction->const_payload.value = value;
    return instruction;
}

IR_Instruction *IR_Instruction__create_ret(IR_Value *value) {
    IR_Instruction *instruction = IR_Instruction__create(IR_INSTRUCTION_KIND__RET);
    if (value != NULL) {
        IR_Value_List__append(&instruction->arguments, value);
    }
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

IR_Procedure *IR_Procedure__create(String *name, IR_Type *return_type) {
    IR_Procedure *procedure = (IR_Procedure *)malloc(sizeof(IR_Procedure));
    procedure->name = name;
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
    program->first_procedure = NULL;
    program->last_procedure = NULL;
    return program;
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
    default:
        pWriter__write__cstring(stderr_writer, "Cannot print IR type kind: ");
        pWriter__write__int64(stderr_writer, type->kind);
        pWriter__end_line(stderr_writer);
        panic();
    }
}

Writer *pWriter__write__ir_value_reference(Writer *self, IR_Value *value) {
    pWriter__write__char(self, '%');
    return pWriter__write__string(self, value->name);
}

Writer *pWriter__write__ir_value_definition(Writer *self, IR_Value *value) {
    pWriter__write__ir_value_reference(self, value);
    pWriter__write__cstring(self, ": ");
    return pWriter__write__ir_type(self, value->type);
}

Writer *pWriter__write__ir_instruction(Writer *self, IR_Instruction *instruction) {
    switch (instruction->kind) {
    case IR_INSTRUCTION_KIND__CONST:
        pWriter__write__ir_value_definition(self, &instruction->result);
        pWriter__write__cstring(self, " = const ");
        return pWriter__write__uint64(self, instruction->const_payload.value);
    case IR_INSTRUCTION_KIND__RET:
        pWriter__write__cstring(self, "ret");
        if (instruction->arguments.size > 0) {
            pWriter__write__char(self, ' ');
            pWriter__write__ir_value_reference(self, instruction->arguments.values[0]);
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
    pWriter__write__char(self, '$');
    pWriter__write__string(self, procedure->name);
    pWriter__write__char(self, '(');
    pWriter__write__char(self, ')');
    if (procedure->return_type != NULL) {
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

Writer *pWriter__write__ir_program(Writer *self, IR_Program *program) {
    IR_Procedure *procedure = program->first_procedure;
    bool first = true;
    while (procedure != NULL) {
        if (!first) {
            pWriter__end_line(self);
        }
        first = false;
        pWriter__write__ir_procedure(self, procedure);
        procedure = procedure->next_procedure;
    }
    return self;
}
