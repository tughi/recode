#ifndef __IR_H__
#define __IR_H__

#include "String.h"
#include "Token.h"
#include "Writer.h"

typedef enum IR_Type_Kind {
    IR_TYPE_KIND__ANY,
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
    IR_TYPE_KIND__NOTHING,
    IR_TYPE_KIND__MULTI_POINTER,
    IR_TYPE_KIND__OPAQUE,
    IR_TYPE_KIND__POINTER,
    IR_TYPE_KIND__PROCEDURE,
    IR_TYPE_KIND__STRUCT,
} IR_Type_Kind;

typedef struct IR_Type {
    IR_Type_Kind kind;
} IR_Type;

IR_Type *IR_Type__get(IR_Type_Kind kind);

size_t IR_Type__alignment(IR_Type *type);

size_t IR_Type__size(IR_Type *type);

typedef struct IR_Named_Type {
    IR_Type super;
    String *name;
    struct IR_Named_Type *next_type;
} IR_Named_Type;

typedef struct IR_Opaque_Type {
    IR_Named_Type super;
} IR_Opaque_Type;

IR_Opaque_Type *IR_Opaque_Type__create(String *name);

typedef struct IR_Struct_Type_Field {
    String *name;
    IR_Type *type;
    struct IR_Struct_Type_Field *next_field;
} IR_Struct_Type_Field;

typedef struct IR_Struct_Type {
    IR_Named_Type super;
    IR_Struct_Type_Field *first_field;
    IR_Struct_Type_Field *last_field;
} IR_Struct_Type;

IR_Struct_Type *IR_Struct_Type__create(String *name);

void IR_Struct_Type__append_field(IR_Struct_Type *self, String *name, IR_Type *type);

typedef struct IR_Multi_Pointer_Type {
    IR_Type super;
    IR_Type *pointee;
} IR_Multi_Pointer_Type;

IR_Multi_Pointer_Type *IR_Multi_Pointer_Type__create(IR_Type *pointee);

typedef struct IR_Pointer_Type {
    IR_Type super;
    IR_Type *pointee;
} IR_Pointer_Type;

IR_Pointer_Type *IR_Pointer_Type__create(IR_Type *pointee);

typedef struct IR_Procedure_Type {
    IR_Type super;
    IR_Type **parameter_types;
    size_t parameter_count;
    IR_Type *return_type;
} IR_Procedure_Type;

IR_Procedure_Type *IR_Procedure_Type__create(IR_Type **parameter_types, size_t parameter_count, IR_Type *return_type);

typedef struct IR_Variable IR_Variable;

typedef enum IR_Value_Kind {
    IR_VALUE_KIND__GLOBAL,
    IR_VALUE_KIND__INSTRUCTION_RESULT,
    IR_VALUE_KIND__PARAMETER,
    IR_VALUE_KIND__PROCEDURE,
} IR_Value_Kind;

typedef struct IR_Value {
    IR_Value_Kind kind;
    String *name;
    IR_Type *type;
    IR_Variable *variable;
} IR_Value;

IR_Value *IR_Value__create(IR_Value_Kind kind, String *name, IR_Type *type);

String *IR__value_name(char sigil, String *name);

bool String__equals__value_name(String *self, char sigil, String *name);

typedef struct IR_Symbol {
    IR_Value value;
} IR_Symbol;

typedef struct IR_Variable {
    IR_Symbol super;
    int32_t version;
} IR_Variable;

IR_Variable *IR_Variable__create(String *name, IR_Type *type);

typedef struct IR_Global {
    IR_Symbol super;
    struct IR_Global *next_global;
} IR_Global;

IR_Global *IR_Global__create(String *name, IR_Type *type);

typedef struct IR_Value_List {
    IR_Value **values;
    size_t size;
    size_t capacity;
} IR_Value_List;

void IR_Value_List__append(IR_Value_List *self, IR_Value *value);

typedef enum IR_Instruction_Kind {
    IR_INSTRUCTION_KIND__ADD,
    IR_INSTRUCTION_KIND__ALLOC,
    IR_INSTRUCTION_KIND__ARRAY_OFFSET,
    IR_INSTRUCTION_KIND__BR,
    IR_INSTRUCTION_KIND__CALL,
    IR_INSTRUCTION_KIND__CAST,
    IR_INSTRUCTION_KIND__CMP_EQ,
    IR_INSTRUCTION_KIND__CMP_GE,
    IR_INSTRUCTION_KIND__CMP_GT,
    IR_INSTRUCTION_KIND__CMP_LE,
    IR_INSTRUCTION_KIND__CMP_LT,
    IR_INSTRUCTION_KIND__CMP_NE,
    IR_INSTRUCTION_KIND__CONST,
    IR_INSTRUCTION_KIND__DIV,
    IR_INSTRUCTION_KIND__JMP,
    IR_INSTRUCTION_KIND__LOAD,
    IR_INSTRUCTION_KIND__MOD,
    IR_INSTRUCTION_KIND__MUL,
    IR_INSTRUCTION_KIND__NEG,
    IR_INSTRUCTION_KIND__NOT,
    IR_INSTRUCTION_KIND__PHI,
    IR_INSTRUCTION_KIND__RET,
    IR_INSTRUCTION_KIND__STORE,
    IR_INSTRUCTION_KIND__STRUCT,
    IR_INSTRUCTION_KIND__STRUCT_OFFSET,
    IR_INSTRUCTION_KIND__SUB,
} IR_Instruction_Kind;

typedef struct IR_Block IR_Block;

typedef struct IR_Block_List {
    IR_Block **blocks;
    size_t size;
    size_t capacity;
} IR_Block_List;

void IR_Block_List__append(IR_Block_List *self, IR_Block *block);

typedef struct IR_Instruction {
    IR_Value result;
    IR_Instruction_Kind kind;
    IR_Value_List operands;
    struct IR_Instruction *next_instruction;
} IR_Instruction;

typedef struct IR_Alloc_Instruction {
    IR_Instruction super;
    IR_Type *allocated_type;
} IR_Alloc_Instruction;

IR_Alloc_Instruction *IR_Alloc_Instruction__create(IR_Variable *variable);

typedef struct IR_Array_Offset_Instruction {
    IR_Instruction super;
} IR_Array_Offset_Instruction;

IR_Array_Offset_Instruction *IR_Array_Offset_Instruction__create(String *result_name, IR_Type *result_type, IR_Value *pointer, IR_Value *index);

typedef struct IR_Br_Instruction {
    IR_Instruction super;
    IR_Value *condition;
    IR_Block *true_block;
    IR_Block *false_block;
} IR_Br_Instruction;

IR_Br_Instruction *IR_Br_Instruction__create(IR_Value *condition, IR_Block *true_block, IR_Block *false_block);

typedef struct IR_Call_Instruction {
    IR_Instruction super;
} IR_Call_Instruction;

IR_Call_Instruction *IR_Call_Instruction__create(String *result_name, IR_Type *result_type, IR_Value *callee);

typedef struct IR_Cast_Instruction {
    IR_Instruction super;
} IR_Cast_Instruction;

IR_Cast_Instruction *IR_Cast_Instruction__create(String *result_name, IR_Type *result_type, IR_Value *value);

typedef struct IR_Const_Instruction {
    IR_Instruction super;
    uint64_t value;
    Token *literal;
} IR_Const_Instruction;

IR_Const_Instruction *IR_Const_Instruction__create(String *result_name, IR_Type *result_type, uint64_t value, Token *literal);

typedef struct IR_Jmp_Instruction {
    IR_Instruction super;
    IR_Block *block;
} IR_Jmp_Instruction;

IR_Jmp_Instruction *IR_Jmp_Instruction__create(IR_Block *block);

typedef struct IR_Load_Instruction {
    IR_Instruction super;
} IR_Load_Instruction;

IR_Load_Instruction *IR_Load_Instruction__create(String *result_name, IR_Type *result_type, IR_Value *pointer);

typedef struct IR_Neg_Instruction {
    IR_Instruction super;
} IR_Neg_Instruction;

IR_Neg_Instruction *IR_Neg_Instruction__create(String *result_name, IR_Type *result_type, IR_Value *value);

typedef struct IR_Not_Instruction {
    IR_Instruction super;
} IR_Not_Instruction;

IR_Not_Instruction *IR_Not_Instruction__create(String *result_name, IR_Type *result_type, IR_Value *value);

typedef struct IR_Phi_Instruction {
    IR_Instruction super;
    IR_Block_List blocks;
} IR_Phi_Instruction;

IR_Phi_Instruction *IR_Phi_Instruction__create(String *result_name, IR_Type *result_type);

typedef struct IR_Ret_Instruction {
    IR_Instruction super;
} IR_Ret_Instruction;

IR_Ret_Instruction *IR_Ret_Instruction__create(IR_Value *value);

typedef struct IR_Store_Instruction {
    IR_Instruction super;
} IR_Store_Instruction;

IR_Store_Instruction *IR_Store_Instruction__create(IR_Value *pointer, IR_Value *value);

typedef struct IR_Struct_Offset_Instruction {
    IR_Instruction super;
    String *struct_name;
    String *field_name;
} IR_Struct_Offset_Instruction;

IR_Struct_Offset_Instruction *IR_Struct_Offset_Instruction__create(String *result_name, IR_Type *result_type, IR_Value *pointer, String *struct_name, String *field_name);

typedef struct IR_Struct_Instruction {
    IR_Instruction super;
    String **field_names;
    size_t field_count;
    size_t field_capacity;
} IR_Struct_Instruction;

IR_Struct_Instruction *IR_Struct_Instruction__create(String *result_name, IR_Type *result_type);

void IR_Struct_Instruction__append_field(IR_Struct_Instruction *self, String *field_name, IR_Value *value);

typedef struct IR_Binary_Instruction {
    IR_Instruction super;
} IR_Binary_Instruction;

IR_Binary_Instruction *IR_Binary_Instruction__create(IR_Instruction_Kind kind, String *result_name, IR_Type *result_type, IR_Value *left, IR_Value *right);

typedef struct IR_Block {
    size_t label;
    IR_Instruction *first_instruction;
    IR_Instruction *last_instruction;
    struct IR_Block *next_block;
} IR_Block;

IR_Block *IR_Block__create(size_t label);

void IR_Block__append_instruction(IR_Block *self, IR_Instruction *instruction);

bool IR_Block__is_terminated(IR_Block *self);

typedef struct IR_Procedure {
    IR_Symbol super;
    IR_Value_List parameters;
    IR_Type *return_type;
    IR_Block *first_block;
    IR_Block *last_block;
    struct IR_Procedure *next_procedure;
} IR_Procedure;

IR_Procedure *IR_Procedure__create(String *name, IR_Type **parameter_types, size_t parameter_count, IR_Type *return_type);

void IR_Procedure__append_block(IR_Procedure *self, IR_Block *block);

typedef struct IR_Program {
    IR_Named_Type *first_type;
    IR_Named_Type *last_type;
    IR_Global *first_global;
    IR_Global *last_global;
    IR_Procedure *first_procedure;
    IR_Procedure *last_procedure;
} IR_Program;

IR_Program *IR_Program__create();

void IR_Program__append_global(IR_Program *self, IR_Global *global);

void IR_Program__append_type(IR_Program *self, IR_Named_Type *type);

void IR_Program__append_procedure(IR_Program *self, IR_Procedure *procedure);

Writer *pWriter__write__ir_program(Writer *self, IR_Program *program);

#endif
