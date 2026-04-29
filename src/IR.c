#include "IR.h"
#include <stdlib.h>

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
