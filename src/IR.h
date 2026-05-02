#pragma once

#include "Source.h"
#include "Source_Location.h"
#include "String.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef enum IR_Type_Kind {
    IR_TYPE__BOOL,
    IR_TYPE__I32,
    IR_TYPE__PTR,
    IR_TYPE__VOID,
} IR_Type_Kind;

typedef struct IR_Type IR_Type;
struct IR_Type {
    IR_Type_Kind kind;
    union {
        IR_Type *pointee;
    };
};

typedef struct {
    IR_Type **items;
    size_t size;
    size_t capacity;
} IR_Type_List;

void ir_type_list_add(IR_Type_List *list, IR_Type *type);

IR_Type *ir_type_bool(void);
IR_Type *ir_type_i32(void);
IR_Type *ir_type_intern_ptr(IR_Type_List *types, IR_Type *pointee);
IR_Type *ir_type_void(void);
bool ir_type_equals(IR_Type *a, IR_Type *b);
void ir_type_fprintf(FILE *out, IR_Type *type);

typedef struct IR_Value {
    String name;
    IR_Type *type;
} IR_Value;

typedef struct {
    IR_Value **items;
    size_t size;
    size_t capacity;
} IR_Value_List;

void ir_value_list_add(IR_Value_List *list, IR_Value *value);

typedef struct IR_Alloc_Instruction {
    IR_Type *element_type;
} IR_Alloc_Instruction;

typedef struct IR_Br_Instruction {
    size_t true_label;
    size_t false_label;
} IR_Br_Instruction;

typedef struct IR_Const_Instruction {
    int64_t value;
} IR_Const_Instruction;

typedef struct IR_Jmp_Instruction {
    size_t label;
} IR_Jmp_Instruction;

typedef struct IR_Phi_Instruction {
    size_t *labels;
} IR_Phi_Instruction;

typedef enum IR_Instruction_Kind {
    IR_INSTRUCTION__ADD,
    IR_INSTRUCTION__ALLOC,
    IR_INSTRUCTION__BR,
    IR_INSTRUCTION__CALL,
    IR_INSTRUCTION__CMP_EQ,
    IR_INSTRUCTION__CMP_GE,
    IR_INSTRUCTION__CMP_GT,
    IR_INSTRUCTION__CMP_LE,
    IR_INSTRUCTION__CMP_LT,
    IR_INSTRUCTION__CMP_NE,
    IR_INSTRUCTION__CONST,
    IR_INSTRUCTION__DIV,
    IR_INSTRUCTION__JMP,
    IR_INSTRUCTION__LOAD,
    IR_INSTRUCTION__MOD,
    IR_INSTRUCTION__MUL,
    IR_INSTRUCTION__NEG,
    IR_INSTRUCTION__NOT,
    IR_INSTRUCTION__PHI,
    IR_INSTRUCTION__PLACEHOLDER,
    IR_INSTRUCTION__RET,
    IR_INSTRUCTION__STORE,
    IR_INSTRUCTION__SUB,
} IR_Instruction_Kind;

typedef struct IR_Instruction IR_Instruction;

typedef struct {
    IR_Instruction **items;
    size_t size;
    size_t capacity;
} IR_Instruction_List;

void ir_instruction_list_add(IR_Instruction_List *list, IR_Instruction *instruction);

struct IR_Instruction {
    IR_Value result;
    IR_Instruction_Kind kind;
    Source_Location location;
    IR_Value_List arguments;
    union {
        IR_Alloc_Instruction alloc_instruction;
        IR_Br_Instruction br_instruction;
        IR_Const_Instruction const_instruction;
        IR_Jmp_Instruction jmp_instruction;
        IR_Phi_Instruction phi_instruction;
    };
};

typedef struct IR_Block IR_Block;

typedef struct {
    IR_Block **items;
    size_t size;
    size_t capacity;
} IR_Block_List;

void ir_block_list_add(IR_Block_List *list, IR_Block *block);

struct IR_Block {
    size_t label;
    Source_Location location;
    IR_Instruction_List instructions;
};

typedef struct IR_Function {
    String name;
    Source_Location location;
    IR_Value_List parameters;
    IR_Type *return_type;
    IR_Block_List blocks;
} IR_Function;

typedef struct {
    IR_Function *items;
    size_t size;
    size_t capacity;
} IR_Function_List;

void ir_function_list_add(IR_Function_List *list, IR_Function function);

typedef struct IR_Module {
    Source source;
    IR_Function_List functions;
    IR_Type_List types;
} IR_Module;
