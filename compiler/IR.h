#ifndef __IR_H__
#define __IR_H__

#include "String.h"
#include "Writer.h"

typedef enum IR_Type_Kind {
    IR_TYPE_KIND__BOOL,
    IR_TYPE_KIND__I8,
    IR_TYPE_KIND__I16,
    IR_TYPE_KIND__I32,
    IR_TYPE_KIND__I64,
    IR_TYPE_KIND__ISIZE,
    IR_TYPE_KIND__U8,
    IR_TYPE_KIND__U16,
    IR_TYPE_KIND__U32,
    IR_TYPE_KIND__U64,
    IR_TYPE_KIND__USIZE,
} IR_Type_Kind;

typedef struct IR_Type {
    IR_Type_Kind kind;
} IR_Type;

IR_Type *IR_Type__get(IR_Type_Kind kind);

typedef enum IR_Value_Kind {
    IR_VALUE_KIND__INSTRUCTION_RESULT,
} IR_Value_Kind;

typedef struct IR_Value {
    IR_Value_Kind kind;
    String *name;
    IR_Type *type;
} IR_Value;

typedef struct IR_Value_List {
    IR_Value **values;
    size_t size;
    size_t capacity;
} IR_Value_List;

void IR_Value_List__append(IR_Value_List *self, IR_Value *value);

typedef enum IR_Instruction_Kind {
    IR_INSTRUCTION_KIND__CONST,
    IR_INSTRUCTION_KIND__RET,
} IR_Instruction_Kind;

typedef struct IR_Const_Payload {
    uint64_t value;
} IR_Const_Payload;

typedef struct IR_Instruction {
    IR_Value result;
    IR_Instruction_Kind kind;
    IR_Value_List arguments;
    union {
        IR_Const_Payload const_payload;
    };
    struct IR_Instruction *next_instruction;
} IR_Instruction;

IR_Instruction *IR_Instruction__create_const(String *result_name, IR_Type *result_type, uint64_t value);

IR_Instruction *IR_Instruction__create_ret(IR_Value *value);

typedef struct IR_Block {
    size_t label;
    IR_Instruction *first_instruction;
    IR_Instruction *last_instruction;
    struct IR_Block *next_block;
} IR_Block;

IR_Block *IR_Block__create(size_t label);

void IR_Block__append_instruction(IR_Block *self, IR_Instruction *instruction);

typedef struct IR_Procedure {
    String *name;
    IR_Type *return_type;
    IR_Block *first_block;
    IR_Block *last_block;
    struct IR_Procedure *next_procedure;
} IR_Procedure;

IR_Procedure *IR_Procedure__create(String *name, IR_Type *return_type);

void IR_Procedure__append_block(IR_Procedure *self, IR_Block *block);

typedef struct IR_Program {
    IR_Procedure *first_procedure;
    IR_Procedure *last_procedure;
} IR_Program;

IR_Program *IR_Program__create();

void IR_Program__append_procedure(IR_Program *self, IR_Procedure *procedure);

Writer *pWriter__write__ir_program(Writer *self, IR_Program *program);

#endif
