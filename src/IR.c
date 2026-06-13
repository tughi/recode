#include "IR.h"
#include "Panic.h"
#include <stdlib.h>
#include <string.h>

static IR_Type ir_type_any_singleton = {
    .kind = IR_TYPE__ANY,
};

IR_Type *ir_type_any(void) {
    return &ir_type_any_singleton;
}

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

IR_Type *ir_type_array(IR_Type_List *types, IR_Type *item_type, size_t item_count) {
    for (size_t i = 0; i < types->size; i++) {
        IR_Type *existing = types->items[i];
        if (existing->kind == IR_TYPE__ARRAY && existing->item_type == item_type && existing->item_count == item_count) {
            return existing;
        }
    }
    IR_Type *type = malloc(sizeof(IR_Type));
    type->kind = IR_TYPE__ARRAY;
    type->item_type = item_type;
    type->item_count = item_count;
    ir_type_list_add(types, type);
    return type;
}

IR_Type *ir_type_multipointer(IR_Type_List *types, IR_Type *pointee) {
    for (size_t i = 0; i < types->size; i++) {
        IR_Type *existing = types->items[i];
        if (existing->kind == IR_TYPE__MULTI_PTR && existing->pointee == pointee) {
            return existing;
        }
    }
    IR_Type *type = malloc(sizeof(IR_Type));
    type->kind = IR_TYPE__MULTI_PTR;
    type->pointee = pointee;
    ir_type_list_add(types, type);
    return type;
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
        IR_Type *type = types->items[i];
        switch (type->kind) {
        case IR_TYPE__OPAQUE:
        case IR_TYPE__PLACEHOLDER:
        case IR_TYPE__STRUCT:
            if (string_equals(type->name, name)) {
                return type;
            }
        default:
            break;
        }
    }
    return NULL;
}

static size_t align_up(size_t value, size_t alignment) {
    return (value + alignment - 1) / alignment * alignment;
}

size_t ir_type_size(IR_Type *type) {
    switch (type->kind) {
    case IR_TYPE__BOOL:
    case IR_TYPE__I8:
    case IR_TYPE__U8:
        return 1;
    case IR_TYPE__I16:
    case IR_TYPE__U16:
        return 2;
    case IR_TYPE__I32:
    case IR_TYPE__U32:
        return 4;
    case IR_TYPE__I64:
    case IR_TYPE__U64:
    case IR_TYPE__ISIZE:
    case IR_TYPE__USIZE:
    case IR_TYPE__MULTI_PTR:
    case IR_TYPE__PTR:
    case IR_TYPE__PROC:
        return 8;
    case IR_TYPE__ARRAY:
        return type->item_count * ir_type_size(type->item_type);
    case IR_TYPE__STRUCT: {
        if (type->struct_field_count == 0) {
            return 1;
        }
        size_t last = type->struct_field_count - 1;
        size_t size = ir_struct_field_offset(type, last) + ir_type_size(type->struct_fields[last]->type);
        return align_up(size, ir_type_alignment(type));
    }
    case IR_TYPE__PLACEHOLDER:
        fprintf(stderr, "%.*s:%zu:%zu: Unresolved type '%.*s'\n", STRING(type->location.source), type->location.line, type->location.column, STRING(type->name));
        panic();
    case IR_TYPE__ANY:
    case IR_TYPE__OPAQUE:
    case IR_TYPE__VOID:
        return 0;
    }
    return 0;
}

size_t ir_type_alignment(IR_Type *type) {
    if (type->kind == IR_TYPE__ARRAY) {
        return ir_type_alignment(type->item_type);
    }
    if (type->kind == IR_TYPE__STRUCT) {
        size_t alignment = 1;
        for (size_t i = 0; i < type->struct_field_count; i++) {
            size_t field_alignment = ir_type_alignment(type->struct_fields[i]->type);
            if (field_alignment > alignment) {
                alignment = field_alignment;
            }
        }
        return alignment;
    }
    size_t size = ir_type_size(type);
    if (size == 0) {
        return 1;
    }
    if (size >= 8) {
        return 8;
    }
    return size;
}

size_t ir_struct_field_offset(IR_Type *struct_type, size_t field_index) {
    size_t offset = 0;
    for (size_t i = 0; i < field_index; i++) {
        size_t field_alignment = ir_type_alignment(struct_type->struct_fields[i]->type);
        offset = align_up(offset, field_alignment);
        offset += ir_type_size(struct_type->struct_fields[i]->type);
    }
    return align_up(offset, ir_type_alignment(struct_type->struct_fields[field_index]->type));
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
    if (a->kind == IR_TYPE__ARRAY) {
        return a->item_count == b->item_count && ir_type_equals(a->item_type, b->item_type);
    }
    if (a->kind == IR_TYPE__MULTI_PTR || a->kind == IR_TYPE__PTR) {
        return ir_type_equals(a->pointee, b->pointee);
    }
    if (a->kind == IR_TYPE__OPAQUE) {
        return false;
    }
    if (a->kind == IR_TYPE__PLACEHOLDER) {
        return false;
    }
    if (a->kind == IR_TYPE__STRUCT) {
        return false;
    }
    return true;
}

void fprint_ir_type(FILE *out, IR_Type *type) {
    if (type == NULL) {
        fputs("(unknown)", out);
        return;
    }
    switch (type->kind) {
    case IR_TYPE__ANY:
        fputs("Any", out);
        return;
    case IR_TYPE__ARRAY:
        fprintf(out, "[%zu]", type->item_count);
        fprint_ir_type(out, type->item_type);
        return;
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
    case IR_TYPE__PLACEHOLDER:
    case IR_TYPE__STRUCT:
        fprintf(out, "%.*s", STRING(type->name));
        return;
    case IR_TYPE__PROC:
        fputs("proc (", out);
        for (size_t i = 0; i < type->proc.param_count; i++) {
            if (i > 0) {
                fputs(", ", out);
            }
            fprint_ir_type(out, type->proc.param_types[i]);
        }
        fputs("): ", out);
        fprint_ir_type(out, type->proc.return_type);
        return;
    case IR_TYPE__MULTI_PTR:
        fputs("[*]", out);
        fprint_ir_type(out, type->pointee);
        return;
    case IR_TYPE__PTR:
        fputc('[', out);
        fprint_ir_type(out, type->pointee);
        fputc(']', out);
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
