#pragma once

#include "Lexed_File.h"
#include "Source_Location.h"
#include "String.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef enum IR_Type_Kind {
    IR_TYPE__ANY,
    IR_TYPE__ARRAY,
    IR_TYPE__BOOL,
    IR_TYPE__I8,
    IR_TYPE__I16,
    IR_TYPE__I32,
    IR_TYPE__I64,
    IR_TYPE__ISIZE,
    IR_TYPE__MULTI_PTR,
    IR_TYPE__OPAQUE,
    IR_TYPE__PLACEHOLDER,
    IR_TYPE__PROC,
    IR_TYPE__PTR,
    IR_TYPE__STRUCT,
    IR_TYPE__U8,
    IR_TYPE__U16,
    IR_TYPE__U32,
    IR_TYPE__U64,
    IR_TYPE__USIZE,
    IR_TYPE__VOID,
} IR_Type_Kind;

typedef struct IR_Type IR_Type;

typedef struct {
    IR_Type **param_types;
    size_t param_count;
    IR_Type *return_type;
} IR_Proc_Type;

typedef struct {
    String name;
    IR_Type *type;
} IR_Struct_Field;

struct IR_Type {
    IR_Type_Kind kind;
    union {
        struct {
            String name;
            Source_Location location;
            union {
                struct {
                    IR_Struct_Field **struct_fields;
                    size_t struct_field_count;
                };
            };
        };
        IR_Type *pointee;
        IR_Proc_Type proc;
        struct {
            IR_Type *item_type;
            size_t item_count;
        };
    };
};

typedef struct {
    IR_Type **items;
    size_t size;
    size_t capacity;
} IR_Type_List;

void ir_type_list_add(IR_Type_List *list, IR_Type *type);

IR_Type *ir_type_any(void);
IR_Type *ir_type_array(IR_Type_List *types, IR_Type *item_type, size_t item_count);
IR_Type *ir_type_bool(void);
IR_Type *ir_type_i8(void);
IR_Type *ir_type_i16(void);
IR_Type *ir_type_i32(void);
IR_Type *ir_type_i64(void);
IR_Type *ir_type_isize(void);
IR_Type *ir_type_named_lookup(IR_Type_List *types, String name);
IR_Type *ir_type_multipointer(IR_Type_List *types, IR_Type *pointee);
IR_Type *ir_type_pointer(IR_Type_List *types, IR_Type *pointee);
IR_Type *ir_type_proc(IR_Type_List *types, IR_Type **param_types, size_t param_count, IR_Type *return_type);
IR_Type *ir_type_u8(void);
IR_Type *ir_type_u16(void);
IR_Type *ir_type_u32(void);
IR_Type *ir_type_u64(void);
IR_Type *ir_type_usize(void);
IR_Type *ir_type_void(void);
bool ir_type_equals(IR_Type *a, IR_Type *b);
size_t ir_type_size(IR_Type *type);
size_t ir_type_alignment(IR_Type *type);
size_t ir_struct_field_offset(IR_Type *struct_type, size_t field_index);
void fprint_ir_type(FILE *out, IR_Type *type);

typedef enum {
    IR_VALUE__FUNCTION,
    IR_VALUE__GLOBAL_VARIABLE,
    IR_VALUE__INSTRUCTION_RESULT,
    IR_VALUE__UNRESOLVED,
} IR_Value_Kind;

typedef struct {
    uint32_t offset;
    uint32_t size;
} Frame_Slot;

typedef struct IR_Value {
    IR_Value_Kind kind;
    String name;
    IR_Type *type;
    Frame_Slot slot;
} IR_Value;

typedef struct {
    IR_Value **items;
    size_t size;
    size_t capacity;
} IR_Value_List;

void ir_value_list_add(IR_Value_List *list, IR_Value *value);

typedef struct IR_Alloc_Instruction {
    IR_Type *element_type;
    Frame_Slot payload_slot;
} IR_Alloc_Instruction;

typedef struct IR_Br_Instruction {
    size_t true_label;
    size_t false_label;
} IR_Br_Instruction;

typedef struct IR_Const_Instruction {
    int64_t value;
} IR_Const_Instruction;

typedef struct IR_Dbg_Bind_Instruction {
    String variable_name;
    bool indirect;
} IR_Dbg_Bind_Instruction;

typedef struct IR_Dbg_Line_Instruction {
    Source_Location location;
} IR_Dbg_Line_Instruction;

typedef struct IR_Jmp_Instruction {
    size_t label;
} IR_Jmp_Instruction;

typedef struct IR_Offset_Instruction {
    IR_Struct_Field *struct_field;
} IR_Offset_Instruction;

typedef struct IR_Phi_Instruction {
    size_t *labels;
} IR_Phi_Instruction;

typedef struct IR_Struct_Instruction {
    IR_Struct_Field **fields;
} IR_Struct_Instruction;

typedef enum IR_Instruction_Kind {
    IR_INSTRUCTION__ADD,
    IR_INSTRUCTION__ALLOC,
    IR_INSTRUCTION__BR,
    IR_INSTRUCTION__CALL,
    IR_INSTRUCTION__CAST,
    IR_INSTRUCTION__CMP_EQ,
    IR_INSTRUCTION__CMP_GE,
    IR_INSTRUCTION__CMP_GT,
    IR_INSTRUCTION__CMP_LE,
    IR_INSTRUCTION__CMP_LT,
    IR_INSTRUCTION__CMP_NE,
    IR_INSTRUCTION__CONST,
    IR_INSTRUCTION__DBG_BIND,
    IR_INSTRUCTION__DBG_LINE,
    IR_INSTRUCTION__DIV,
    IR_INSTRUCTION__JMP,
    IR_INSTRUCTION__LOAD,
    IR_INSTRUCTION__MOD,
    IR_INSTRUCTION__MUL,
    IR_INSTRUCTION__NEG,
    IR_INSTRUCTION__NOT,
    IR_INSTRUCTION__OFFSET,
    IR_INSTRUCTION__PHI,
    IR_INSTRUCTION__PLACEHOLDER,
    IR_INSTRUCTION__RET,
    IR_INSTRUCTION__STORE,
    IR_INSTRUCTION__STRUCT,
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
        IR_Dbg_Bind_Instruction dbg_bind_instruction;
        IR_Dbg_Line_Instruction dbg_line_instruction;
        IR_Jmp_Instruction jmp_instruction;
        IR_Offset_Instruction offset_instruction;
        IR_Phi_Instruction phi_instruction;
        IR_Struct_Instruction struct_instruction;
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

typedef enum {
    IR_EXTERNAL_FUNCTION__SDL_CreateRenderer,
    IR_EXTERNAL_FUNCTION__SDL_CreateWindow,
    IR_EXTERNAL_FUNCTION__SDL_Delay,
    IR_EXTERNAL_FUNCTION__SDL_DestroyRenderer,
    IR_EXTERNAL_FUNCTION__SDL_DestroyWindow,
    IR_EXTERNAL_FUNCTION__SDL_GetError,
    IR_EXTERNAL_FUNCTION__SDL_GetWindowID,
    IR_EXTERNAL_FUNCTION__SDL_GetWindowSize,
    IR_EXTERNAL_FUNCTION__SDL_Init,
    IR_EXTERNAL_FUNCTION__SDL_PollEvent,
    IR_EXTERNAL_FUNCTION__SDL_Quit,
    IR_EXTERNAL_FUNCTION__SDL_RenderClear,
    IR_EXTERNAL_FUNCTION__SDL_RenderDrawLine,
    IR_EXTERNAL_FUNCTION__SDL_RenderDrawPoint,
    IR_EXTERNAL_FUNCTION__SDL_RenderDrawRect,
    IR_EXTERNAL_FUNCTION__SDL_RenderFillRect,
    IR_EXTERNAL_FUNCTION__SDL_RenderPresent,
    IR_EXTERNAL_FUNCTION__SDL_RenderSetClipRect,
    IR_EXTERNAL_FUNCTION__SDL_SetRenderDrawColor,
    IR_EXTERNAL_FUNCTION__SDL_WaitEvent,
    IR_EXTERNAL_FUNCTION__closedir,
    IR_EXTERNAL_FUNCTION__exit,
    IR_EXTERNAL_FUNCTION__fclose,
    IR_EXTERNAL_FUNCTION__fflush,
    IR_EXTERNAL_FUNCTION__fopen,
    IR_EXTERNAL_FUNCTION__fputc,
    IR_EXTERNAL_FUNCTION__fputs,
    IR_EXTERNAL_FUNCTION__fread,
    IR_EXTERNAL_FUNCTION__free,
    IR_EXTERNAL_FUNCTION__fseek,
    IR_EXTERNAL_FUNCTION__ftell,
    IR_EXTERNAL_FUNCTION__fwrite,
    IR_EXTERNAL_FUNCTION__get_dirent_name,
    IR_EXTERNAL_FUNCTION__malloc,
    IR_EXTERNAL_FUNCTION__opendir,
    IR_EXTERNAL_FUNCTION__readdir,
    IR_EXTERNAL_FUNCTION__realloc,
    IR_EXTERNAL_FUNCTION__strlen,
} IR_External_Function;

typedef struct IR_Function {
    IR_Value value;
    String name;
    Source_Location location;
    bool is_external;
    IR_Type *return_type;
    IR_Value_List parameters;
    union {
        struct {
            IR_Block_List blocks;
            uint32_t frame_size;
        };
        IR_External_Function which;
    };
} IR_Function;

typedef struct {
    IR_Function **items;
    size_t size;
    size_t capacity;
} IR_Function_List;

void ir_function_list_add(IR_Function_List *list, IR_Function *function);

typedef struct IR_Global_Variable {
    IR_Value value;
    String name;
    Source_Location location;
    bool is_external;
    IR_Type *type;
    Frame_Slot payload_slot;
    const uint8_t *payload_data;
} IR_Global_Variable;

typedef struct {
    IR_Global_Variable **items;
    size_t size;
    size_t capacity;
} IR_Global_Variable_List;

void ir_global_variable_list_add(IR_Global_Variable_List *list, IR_Global_Variable *global);

typedef struct {
    String *items;
    size_t size;
    size_t capacity;
} IR_Source_File_List;

void ir_source_file_list_add(IR_Source_File_List *list, String path);

typedef struct IR_Module {
    Lexed_File lexed_file;
    IR_Source_File_List source_files;
    IR_Function_List functions;
    IR_Global_Variable_List global_variables;
    IR_Type_List types;
    uint32_t globals_size;
} IR_Module;
