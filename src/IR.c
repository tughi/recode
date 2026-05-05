#include "IR.h"
#include <stdlib.h>
#include <string.h>

static IR_Type ir_type_bool_singleton = {
    .kind = IR_TYPE__BOOL,
};

IR_Type *ir_type_bool(void) {
    return &ir_type_bool_singleton;
}

static IR_Type ir_type_i8_singleton = {
    .kind = IR_TYPE__I8,
};

IR_Type *ir_type_i8(void) {
    return &ir_type_i8_singleton;
}

static IR_Type ir_type_i16_singleton = {
    .kind = IR_TYPE__I16,
};

IR_Type *ir_type_i16(void) {
    return &ir_type_i16_singleton;
}

static IR_Type ir_type_i32_singleton = {
    .kind = IR_TYPE__I32,
};

IR_Type *ir_type_i32(void) {
    return &ir_type_i32_singleton;
}

static IR_Type ir_type_i64_singleton = {
    .kind = IR_TYPE__I64,
};

IR_Type *ir_type_i64(void) {
    return &ir_type_i64_singleton;
}

static IR_Type ir_type_isize_singleton = {
    .kind = IR_TYPE__ISIZE,
};

IR_Type *ir_type_isize(void) {
    return &ir_type_isize_singleton;
}

static IR_Type ir_type_u8_singleton = {
    .kind = IR_TYPE__U8,
};

IR_Type *ir_type_u8(void) {
    return &ir_type_u8_singleton;
}

static IR_Type ir_type_u16_singleton = {
    .kind = IR_TYPE__U16,
};

IR_Type *ir_type_u16(void) {
    return &ir_type_u16_singleton;
}

static IR_Type ir_type_u32_singleton = {
    .kind = IR_TYPE__U32,
};

IR_Type *ir_type_u32(void) { return &ir_type_u32_singleton; }

static IR_Type ir_type_u64_singleton = {
    .kind = IR_TYPE__U64,
};

IR_Type *ir_type_u64(void) { return &ir_type_u64_singleton; }

static IR_Type ir_type_usize_singleton = {
    .kind = IR_TYPE__USIZE,
};

IR_Type *ir_type_usize(void) { return &ir_type_usize_singleton; }

static IR_Type ir_type_void_singleton = {
    .kind = IR_TYPE__VOID,
};

IR_Type *ir_type_void(void) { return &ir_type_void_singleton; }

void ir_type_list_add(IR_Type_List *list, IR_Type *type) {
    if (list->size == list->capacity) {
        list->capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        list->items = realloc(list->items, list->capacity * sizeof(IR_Type *));
    }
    list->items[list->size++] = type;
}

IR_Type *ir_type_pointer(IR_Type_List *types, IR_Type *pointee) {
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

IR_Type *ir_type_proc(IR_Type_List *types, IR_Type **param_types, size_t param_count, IR_Type *return_type) {
    for (size_t i = 0; i < types->size; i++) {
        IR_Type *type = types->items[i];
        if (type->kind != IR_TYPE__PROC || type->proc.param_count != param_count || !ir_type_equals(type->proc.return_type, return_type)) {
            continue;
        }
        bool match = true;
        for (size_t p = 0; p < param_count; p++) {
            if (!ir_type_equals(type->proc.param_types[p], param_types[p])) {
                match = false;
                break;
            }
        }
        if (match) {
            return type;
        }
    }
    IR_Type *type = malloc(sizeof(IR_Type));
    type->kind = IR_TYPE__PROC;
    type->proc.param_count = param_count;
    type->proc.return_type = return_type;
    if (param_count > 0) {
        type->proc.param_types = malloc(param_count * sizeof(IR_Type *));
        memcpy(type->proc.param_types, param_types, param_count * sizeof(IR_Type *));
    } else {
        type->proc.param_types = NULL;
    }
    ir_type_list_add(types, type);
    return type;
}

IR_Type *ir_type_named_lookup(IR_Type_List *types, String name) {
    for (size_t i = 0; i < types->size; i++) {
        IR_Type *existing = types->items[i];
        if (existing->kind == IR_TYPE__OPAQUE && string_equals(existing->name, name)) {
            return existing;
        }
        if (existing->kind == IR_TYPE__STRUCT && string_equals(existing->strukt.name, name)) {
            return existing;
        }
    }
    return NULL;
}

IR_Type *ir_type_new_opaque(IR_Type_List *types, String name) {
    IR_Type *type = malloc(sizeof(IR_Type));
    type->kind = IR_TYPE__OPAQUE;
    type->name = name;
    ir_type_list_add(types, type);
    return type;
}

size_t ir_type_size(IR_Type *type) {
    if (type->kind == IR_TYPE__STRUCT) {
        size_t total = 0;
        for (size_t i = 0; i < type->strukt.field_count; i++) {
            total += ir_type_size(type->strukt.fields[i]->type);
        }
        return total;
    }
    return 1;
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
    if (a->kind == IR_TYPE__PROC) {
        if (a->proc.param_count != b->proc.param_count || !ir_type_equals(a->proc.return_type, b->proc.return_type)) {
            return false;
        }
        for (size_t i = 0; i < a->proc.param_count; i++) {
            if (!ir_type_equals(a->proc.param_types[i], b->proc.param_types[i])) {
                return false;
            }
        }
        return true;
    }
    if (a->kind == IR_TYPE__PTR) {
        return ir_type_equals(a->pointee, b->pointee);
    }
    if (a->kind == IR_TYPE__OPAQUE) {
        return false;
    }
    if (a->kind == IR_TYPE__STRUCT) {
        return false;
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
    case IR_TYPE__I8:
        fputs("i8", out);
        return;
    case IR_TYPE__I16:
        fputs("i16", out);
        return;
    case IR_TYPE__I32:
        fputs("i32", out);
        return;
    case IR_TYPE__I64:
        fputs("i64", out);
        return;
    case IR_TYPE__ISIZE:
        fputs("isize", out);
        return;
    case IR_TYPE__OPAQUE:
        fprintf(out, "%.*s", STRING(type->name));
        return;
    case IR_TYPE__PROC:
        fputs("proc(", out);
        for (size_t i = 0; i < type->proc.param_count; i++) {
            if (i > 0) {
                fputs(", ", out);
            }
            ir_type_fprintf(out, type->proc.param_types[i]);
        }
        fputs(") -> ", out);
        ir_type_fprintf(out, type->proc.return_type);
        return;
    case IR_TYPE__PTR:
        fputs("ptr<", out);
        ir_type_fprintf(out, type->pointee);
        fputc('>', out);
        return;
    case IR_TYPE__STRUCT:
        fprintf(out, "%.*s", STRING(type->strukt.name));
        return;
    case IR_TYPE__U8:
        fputs("u8", out);
        return;
    case IR_TYPE__U16:
        fputs("u16", out);
        return;
    case IR_TYPE__U32:
        fputs("u32", out);
        return;
    case IR_TYPE__U64:
        fputs("u64", out);
        return;
    case IR_TYPE__USIZE:
        fputs("usize", out);
        return;
    case IR_TYPE__VOID:
        fputs("void", out);
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

void ir_function_list_add(IR_Function_List *list, IR_Function *function) {
    if (list->size == list->capacity) {
        list->capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        list->items = realloc(list->items, list->capacity * sizeof(IR_Function *));
    }
    list->items[list->size++] = function;
}

void ir_global_variable_list_add(IR_Global_Variable_List *list, IR_Global_Variable *global) {
    if (list->size == list->capacity) {
        list->capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        list->items = realloc(list->items, list->capacity * sizeof(IR_Global_Variable *));
    }
    list->items[list->size++] = global;
}
