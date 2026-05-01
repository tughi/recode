#include "IR.h"
#include <stdlib.h>

static IR_Type ir_type_bool_singleton = {.kind = IR_TYPE__BOOL};
static IR_Type ir_type_i32_singleton = {.kind = IR_TYPE__I32};

IR_Type *ir_type_bool(void) {
    return &ir_type_bool_singleton;
}

IR_Type *ir_type_i32(void) {
    return &ir_type_i32_singleton;
}

void ir_type_list_add(IR_Type_List *list, IR_Type *type) {
    if (list->size == list->capacity) {
        list->capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        list->items = realloc(list->items, list->capacity * sizeof(IR_Type *));
    }
    list->items[list->size++] = type;
}

IR_Type *ir_type_intern_ptr(IR_Type_List *types, IR_Type *pointee) {
    for (size_t i = 0; i < types->size; i++) {
        IR_Type *existing = types->items[i];
        if (existing->kind == IR_TYPE__PTR && existing->pointee == pointee) {
            return existing;
        }
    }
    IR_Type *type = malloc(sizeof(IR_Type));
    type->kind = IR_TYPE__PTR;
    type->pointee = pointee;
    ir_type_list_add(types, type);
    return type;
}

bool ir_type_equals(IR_Type *a, IR_Type *b) {
    if (a == b) {
        return true;
    }
    if (a == NULL || b == NULL) {
        return false;
    }
    if (a->kind != b->kind) {
        return false;
    }
    if (a->kind == IR_TYPE__PTR) {
        return ir_type_equals(a->pointee, b->pointee);
    }
    return true;
}

void ir_type_fprintf(FILE *out, IR_Type *type) {
    if (type == NULL) {
        fputs("(unknown)", out);
        return;
    }
    switch (type->kind) {
    case IR_TYPE__BOOL:
        fputs("bool", out);
        return;
    case IR_TYPE__I32:
        fputs("i32", out);
        return;
    case IR_TYPE__PTR:
        fputs("ptr<", out);
        ir_type_fprintf(out, type->pointee);
        fputc('>', out);
        return;
    }
}

void ir_value_list_add(IR_Value_List *list, IR_Value *value) {
    if (list->size == list->capacity) {
        list->capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        list->items = realloc(list->items, list->capacity * sizeof(IR_Value *));
    }
    list->items[list->size++] = value;
}

void ir_instruction_list_add(IR_Instruction_List *list, IR_Instruction *instruction) {
    if (list->size == list->capacity) {
        list->capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        list->items = realloc(list->items, list->capacity * sizeof(IR_Instruction *));
    }
    list->items[list->size++] = instruction;
}

void ir_block_list_add(IR_Block_List *list, IR_Block *block) {
    if (list->size == list->capacity) {
        list->capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        list->items = realloc(list->items, list->capacity * sizeof(IR_Block *));
    }
    list->items[list->size++] = block;
}

void ir_function_list_add(IR_Function_List *list, IR_Function function) {
    if (list->size == list->capacity) {
        list->capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        list->items = realloc(list->items, list->capacity * sizeof(IR_Function));
    }
    list->items[list->size++] = function;
}
