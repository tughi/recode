#include "Generator.h"
#include "Logging.h"

typedef struct Variable {
    int id;
    String *name;
    Source_Location *location;
    Type *type;
    int is_global;
    int locals_offset;
} Variable;

typedef List Variables;

Variables *variables__create() {
    return list__create();
}

typedef struct Loop {
    int id;
    int has_exit;
    struct Loop *parent;
} Loop;

Loop *loop__create(int id, Loop *parent) {
    Loop *self = malloc(sizeof(Loop));
    self->id = id;
    self->has_exit = 0;
    self->parent = parent;
    return self;
}

typedef struct Counter {
    int count;
} Counter;

static Counter *counter__create() {
    Counter *self = malloc(sizeof(Counter));
    self->count = 0;
    return self;
}

static int counter__inc(Counter *self) {
    self->count += 1;
    return self->count;
}

typedef struct Context {
    struct Context *global_context;
    struct Context *parent_context;
    FILE *file;
    Named_Functions *named_functions;
    Named_Types *named_types;
    Token_List *string_constants;
    Variables *variables;
    Counter *counter;
    Statement *current_function;
    Loop *current_loop;
} Context;

#define emitf(line, ...) fprintf(context->file, line "\n", __VA_ARGS__)
#define emits(line) fprintf(context->file, line "\n")

static Context *context__create(FILE *file, Named_Functions *named_functions, Named_Types *named_types) {
    Context *self = malloc(sizeof(Context));
    self->global_context = self;
    self->parent_context = NULL;
    self->file = file;
    self->named_functions = named_functions;
    self->named_types = named_types;
    self->string_constants = list__create();
    self->variables = variables__create();
    self->counter = counter__create();
    self->current_function = NULL;
    self->current_loop = NULL;
    return self;
}

Context *context__clone(Context *other) {
    Context *self = malloc(sizeof(Context));
    self->global_context = other->global_context;
    self->parent_context = other->parent_context;
    self->file = other->file;
    self->named_functions = other->named_functions;
    self->named_types = other->named_types;
    self->string_constants = other->string_constants;
    self->variables = other->variables;
    self->counter = other->counter;
    self->current_function = other->current_function;
    self->current_loop = other->current_loop;
    return self;
}

Variable *context__find_variable(Context *self, String *name) {
    for (List_Iterator iterator = list__create_reversed_iterator(self->variables); list_iterator__has_next(&iterator);) {
        Variable *variable = list_iterator__next(&iterator);
        if (string__equals(name, variable->name->data)) {
            return variable;
        }
    }
    if (self == self->global_context) {
        return NULL;
    }
    return context__find_variable(self->parent_context, name);
}

int context__compute_type_size(Context *self, Type *type);

Variable *context__last_local_variable(Context *self) {
    if (self->global_context == self) {
        return NULL;
    }
    Variable *variable = list__last(self->variables);
    if (variable != NULL) {
        return variable;
    }
    return context__last_local_variable(self->parent_context);
}

Variable *context__create_variable(Context *self, Source_Location *location, String *name, Type *type) {
    Variable *variable = malloc(sizeof(Variable));
    variable->id = counter__inc(self->counter);
    variable->name = name;
    variable->location = location;
    variable->type = type;
    variable->is_global = self->current_function == NULL;

    Variable *previous_variable = context__last_local_variable(self);
    variable->locals_offset = (previous_variable != NULL ? previous_variable->locals_offset : 0) + context__compute_type_size(self, variable->type);

    list__append(self->variables, variable);

    return variable;
}

Type *context__find_type(Context *self, String *name) {
    return named_types__get(self->named_types, name);
}

String *context__type_name(Context *self, Type *type) {
    if (type->name == NULL) {
        switch (type->kind) {
        case TYPE__NAMED: {
            type->name = type->named_data.name->lexeme;
            break;
        }
        case TYPE__POINTER: {
            type->name = string__create("@");
            string__append_string(type->name, context__type_name(self, type->pointer_data.type));
            break;
        }
        default:
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported type kind: %s", type->location->line, type->location->column, type__get_kind_name(type));
        }
    }
    return type->name;
}

void context__resolve_type(Context *self, Type *type) {
    switch (type->kind) {
    case TYPE__ARRAY: {
        context__resolve_type(self, type->array_data.item_type);
        return;
    }
    case TYPE__NAMED: {
        String *type_name = type->named_data.name->lexeme;
        Type *named_type = context__find_type(self, type_name);
        if (named_type == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unknown type: %s", type->location->line, type->location->column, type_name->data);
        }
        type__convert(type, named_type);
        return;
    }
    case TYPE__POINTER: {
        context__resolve_type(self, type->pointer_data.type);
        return;
    }
    default:
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported type kind: %s", type->location->line, type->location->column, type__get_kind_name(type));
    }
}

int context__is_primitive_type(Context *self, Type *type) {
    switch (type->kind) {
    case TYPE__BOOLEAN:
    case TYPE__INT:
    case TYPE__INT8:
    case TYPE__INT16:
    case TYPE__INT32:
    case TYPE__INT64:
    case TYPE__POINTER:
        return 1;
    default:
        return 0;
    }
}

Type *context__get_boolean_type(Context *self) {
    static String *type_name = NULL;
    if (type_name == NULL) {
        type_name = string__create("Boolean");
    }
    return context__find_type(self, type_name);
}

Type *context__get_int_type(Context *self) {
    static String *type_name = NULL;
    if (type_name == NULL) {
        type_name = string__create("Int");
    }
    return context__find_type(self, type_name);
}

Type *context__get_int8_type(Context *self) {
    static String *type_name = NULL;
    if (type_name == NULL) {
        type_name = string__create("Int8");
    }
    return context__find_type(self, type_name);
}

int context__compute_type_size(Context *self, Type *type) {
    switch (type->kind) {
    case TYPE__ARRAY: {
        int item_type_size = context__compute_type_size(self, type->array_data.item_type);
        return item_type_size * type->array_data.size;
    }
    case TYPE__BOOLEAN:
    case TYPE__INT8:
        return 1;
    case TYPE__INT16:
        return 2;
    case TYPE__INT32:
        return 4;
    case TYPE__INT:
    case TYPE__INT64:
    case TYPE__POINTER:
        return 8;
    case TYPE__NOTHING:
        return 0;
    case TYPE__NAMED: {
        String *type_name = type->named_data.name->lexeme;
        Type *named_type = context__find_type(self, type_name);
        if (named_type == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unknown type: %s", type->location->line, type->location->column, type_name->data);
        }
        return context__compute_type_size(self, named_type);
    }
    case TYPE__STRUCT: {
        int struct_size = type->struct_data.statement->struct_data.size;
        if (struct_size == 0) {
            for (List_Iterator members = list__create_iterator(type->struct_data.statement->struct_data.members); list_iterator__has_next(&members);) {
                Member *member = list_iterator__next(&members);
                member->struct_offset = struct_size;
                struct_size += context__compute_type_size(self, member->type);
            }
            type->struct_data.statement->struct_data.size = struct_size;
        }
        return struct_size;
    }
    default:
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported type kind: %s", type->location->line, type->location->column, type__get_kind_name(type));
    }
}

enum {
    REGISTER__R15,
    REGISTER__R14,
    REGISTER__R13,
    REGISTER__R12,
    REGISTER__R11,
    REGISTER__R10,
    REGISTER__R09,
    REGISTER__R08,
    REGISTER__RCX,
    REGISTER__RDX,
    REGISTER__RSI,
    REGISTER__RDI,
    REGISTERS_COUNT,
};

typedef struct Value_Holder {
    enum {
        VALUE_HOLDER__NEW = 0,
        VALUE_HOLDER__REGISTER,
    } kind;

    int size;
    Type *type;
    union {
        struct {
            int id;
        } register_data;
    };
} Value_Holder;

Value_Holder *registers[REGISTERS_COUNT];

void value_holder__acquire_register(Value_Holder *self, Type *type, Context *context) {
    if (self->kind != VALUE_HOLDER__NEW) {
        PANIC(__FILE__, __LINE__, "Trying to acquire register for an invalid value holder kind: %d", self->kind);
    }
    if (!context__is_primitive_type(context, type)) {
        PANIC(__FILE__, __LINE__, "Trying to acquire register for a non-primitive type: %s", context__type_name(context, type)->data);
    }
    for (int id = 0; id < REGISTERS_COUNT; id++) {
        if (registers[id] == NULL) {
            self->kind = VALUE_HOLDER__REGISTER;
            self->type = type;
            self->size = context__compute_type_size(context, type);
            self->register_data.id = id;
            registers[id] = self;
            return;
        }
    }
    PANIC(__FILE__, __LINE__, "All registers are used already%c", 0);
}

void value_holder__release_register(Value_Holder *self) {
    if (self->kind != VALUE_HOLDER__REGISTER) {
        PANIC(__FILE__, __LINE__, "Trying to release an invalid value holder%c", 0);
    }
    registers[self->register_data.id] = NULL;
    self->kind = VALUE_HOLDER__NEW;
}

char *value_holder__register_name(Value_Holder *self) {
    static char *names_8[REGISTERS_COUNT] = { "r15", "r14", "r13", "r12", "r11", "r10", "r9", "r8", "rcx", "rdx", "rsi", "rdi" };
    static char *names_4[REGISTERS_COUNT] = { "r15d", "r14d", "r13d", "r12d", "r11d", "r10d", "r9d", "r8d", "ecx", "edx", "esi", "edi" };
    static char *names_2[REGISTERS_COUNT] = { "r15w", "r14w", "r13w", "r12w", "r11w", "r10w", "r9w", "r8w", "cx", "dx", "si", "di" };
    static char *names_1[REGISTERS_COUNT] = { "r15b", "r14b", "r13b", "r12b", "r11b", "r10b", "r9b", "r8b", "cl", "dl", "sil", "dil" };

    if (self->kind != VALUE_HOLDER__REGISTER) {
        PANIC(__FILE__, __LINE__, "This is not a register%c", 0);
    }

    switch (self->size) {
    case 8: return names_8[self->register_data.id];
    case 4: return names_4[self->register_data.id];
    case 2: return names_2[self->register_data.id];
    case 1: return names_1[self->register_data.id];
    default:
        PANIC(__FILE__, __LINE__, "Unsupported value size: %d", self->size);
    }
}

void value_holder__move_to_register(Value_Holder *self, int register_id, Context *context) {
    Value_Holder *other_value_holder = registers[register_id];
    if (other_value_holder != NULL) {
        for (int id = register_id - 1; id >= 0; id--) {
            if (registers[id] == NULL) {
                PANIC(__FILE__, __LINE__, "The specified register (%d) is already in use, but there is at least one that can be used instead.", register_id);
            }
        }
    }
    if (other_value_holder == NULL) {
        Value_Holder clone;
        clone.kind = self->kind;
        clone.type = self->type;
        clone.size = self->size;
        clone.register_data.id = self->register_data.id;
        registers[clone.register_data.id] = NULL;
        self->register_data.id = register_id;
        registers[register_id] = self;
        emitf("  mov %s, %s", value_holder__register_name(self), value_holder__register_name(&clone));
        return;
    }
    PANIC(__FILE__, __LINE__, "The specified register (%d) is already in use, and the are no other free registers either.", register_id);
}

void emit_load_literal(Context *context, Token *token, Value_Holder *value_holder) {
    switch (token->kind) {
    case TOKEN__CHARACTER: {
        value_holder__acquire_register(value_holder, context__get_int8_type(context), context);
        emitf("  mov %s, %d", value_holder__register_name(value_holder), token->integer_data.value);
        return;
    }
    case TOKEN__INTEGER: {
        value_holder__acquire_register(value_holder, context__get_int_type(context), context);
        emitf("  mov %s, %d", value_holder__register_name(value_holder), token->integer_data.value);
        return;
    }
    case TOKEN__KEYWORD: {
        if (string__equals(token->lexeme, "false")) {
            value_holder__acquire_register(value_holder, context__get_boolean_type(context), context);
            emitf("  mov %s, 0", value_holder__register_name(value_holder));
            return;
        } 
        if (string__equals(token->lexeme, "true")) {
            value_holder__acquire_register(value_holder, context__get_boolean_type(context), context);
            emitf("  mov %s, 1", value_holder__register_name(value_holder));
            return;
        } 
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported keyword: %s", token->location->line, token->location->line, token->lexeme->data);
    }
    case TOKEN__STRING: {
        int index = list__size(context->string_constants);
        list__append(context->string_constants, token);
        value_holder__acquire_register(value_holder, type__create_pointer(token->location, context__get_int8_type(context)), context);
        emitf("  lea %s, __data__%d__string__[rip]", value_holder__register_name(value_holder), index);
        return;
    }
    default:
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported token kind: %s", token->location->line, token->location->line, token__get_kind_name(token));
    }
}

void emit_expression(Context *context, Expression *expression, Value_Holder *result_value_holder);

void emit_arithmetic_expression(Context *context, Expression *expression, Value_Holder *result_value_holder) {
    emit_expression(context, expression->binary_data.left_expression, result_value_holder);
    Value_Holder right_value_holder = { .kind = VALUE_HOLDER__NEW };
    emit_expression(context, expression->binary_data.right_expression, &right_value_holder);
    Token *operator_token = expression->binary_data.operator_token;
    String *operator = operator_token->lexeme;
    if (result_value_holder->type->kind != TYPE__INT || right_value_holder.type->kind != TYPE__INT) {
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- You can \"%s\" only integer values", operator_token->location->line, operator_token->location->column, operator->data);
    }
    if (string__equals(operator, "+")) {
        emitf("  add %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&right_value_holder));
    } else if (string__equals(operator, "-")) {
        emitf("  sub %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&right_value_holder));
    } else if (string__equals(operator, "*")) {
        emitf("  imul %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&right_value_holder));
    } else if (string__equals(operator, "/")) {
        emitf("  mov rax, %s", value_holder__register_name(result_value_holder));
        emits("  cqto");
        emitf("  idiv %s", value_holder__register_name(&right_value_holder));
        emitf("  mov %s, rax", value_holder__register_name(result_value_holder));
    } else if (string__equals(operator, "//")) {
        emitf("  mov rax, %s", value_holder__register_name(result_value_holder));
        emits("  cqto");
        emitf("  idiv %s", value_holder__register_name(&right_value_holder));
        emitf("  mov %s, rdx", value_holder__register_name(result_value_holder));
    } else {
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported arithmetic expression operator: %s", operator_token->location->line, operator_token->location->column, operator->data);
    }
    value_holder__release_register(&right_value_holder);
}

void emit_comparison_expression(Context *context, Expression *expression, Value_Holder *result_value_holder) {
    emit_expression(context, expression->binary_data.left_expression, result_value_holder);
    Value_Holder right_value_holder = { .kind = VALUE_HOLDER__NEW };
    emit_expression(context, expression->binary_data.right_expression, &right_value_holder);
    Token *operator_token = expression->binary_data.operator_token;
    String *operator = operator_token->lexeme;
    if (string__equals(operator, "<") || string__equals(operator, "<=") || string__equals(operator, ">") || string__equals(operator, ">=")) {
        if (result_value_holder->type->kind != TYPE__INT || right_value_holder.type->kind != TYPE__INT) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- You can use \"%s\" only for integer values", operator_token->location->line, operator_token->location->column, operator->data);
        }
    } else if (string__equals(operator, "==") || string__equals(operator, "!=")) {
        if (!type__equals(result_value_holder->type, right_value_holder.type)) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- You can use \"%s\" only for same type values", operator_token->location->line, operator_token->location->column, operator->data);
        }
    }
    emitf("  cmp %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&right_value_holder));
    value_holder__release_register(result_value_holder);
    value_holder__release_register(&right_value_holder);
    value_holder__acquire_register(result_value_holder, context__get_boolean_type(context), context);
    if (string__equals(operator, "<")) {
        emitf("  setl %s", value_holder__register_name(result_value_holder));
    } else if (string__equals(operator, "<=")) {
        emitf("  setle %s", value_holder__register_name(result_value_holder));
    } else if (string__equals(operator, ">")) {
        emitf("  setg %s", value_holder__register_name(result_value_holder));
    } else if (string__equals(operator, ">=")) {
        emitf("  setge %s", value_holder__register_name(result_value_holder));
    } else if (string__equals(operator, "==")) {
        emitf("  sete %s", value_holder__register_name(result_value_holder));
    } else if (string__equals(operator, "!=")) {
        emitf("  setne %s", value_holder__register_name(result_value_holder));
    } else {
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported comparison expression operator: %s", operator_token->location->line, operator_token->location->column, operator->data);
    }
}

void emit_expression_address(Context *context, Expression *expression, Value_Holder *destination_value_holder) {
    switch (expression->kind) {
    case EXPRESSION__ARRAY_ITEM: {
        Expression *address_expression = expression->array_item_data.array;
        Value_Holder address_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression_address(context, address_expression, &address_value_holder);
        if (!(address_value_holder.type->kind == TYPE__POINTER && (address_value_holder.type->pointer_data.type->kind == TYPE__ARRAY || address_value_holder.type->pointer_data.type->kind == TYPE__POINTER))) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Not an array expression", address_expression->location->line, address_expression->location->column);
        }
        Expression *index_expression = expression->array_item_data.index;
        Value_Holder index_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression(context, index_expression, &index_value_holder);
        if (index_value_holder.type->kind != TYPE__INT) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Not an integer expression", index_expression->location->line, index_expression->location->column);
        }
        Type *item_type;
        if (address_value_holder.type->pointer_data.type->kind == TYPE__ARRAY) {
            item_type = address_value_holder.type->pointer_data.type->array_data.item_type;
        } else {
            item_type = address_value_holder.type->pointer_data.type->pointer_data.type;
        }
        int item_type_size = context__compute_type_size(context, item_type);
        switch (item_type_size) {
        case  1:
            break;
        case 2:
            emitf("  shl %s, 1", value_holder__register_name(&index_value_holder));
            break;
        case 4:
            emitf("  shl %s, 2", value_holder__register_name(&index_value_holder));
            break;
        case 8:
            emitf("  shl %s, 3", value_holder__register_name(&index_value_holder));
            break;
        default:
            emitf("  mov rax, %d", item_type_size);
            emitf("  mul %s", value_holder__register_name(&index_value_holder));
            emitf("  mov %s, rax", value_holder__register_name(&index_value_holder));
            break;
        }
        value_holder__acquire_register(destination_value_holder, type__create_pointer(address_expression->location, item_type), context);
        if (address_value_holder.type->pointer_data.type->kind == TYPE__ARRAY) {
            emitf("  mov %s, %s", value_holder__register_name(destination_value_holder), value_holder__register_name(&address_value_holder));
        } else {
            emitf("  mov %s, [%s]", value_holder__register_name(destination_value_holder), value_holder__register_name(&address_value_holder));
        }
        emitf("  add %s, %s", value_holder__register_name(destination_value_holder), value_holder__register_name(&index_value_holder));
        value_holder__release_register(&index_value_holder);
        value_holder__release_register(&address_value_holder);
        return;
    }
    case EXPRESSION__MEMBER: {
        Expression *object_expression = expression->member_data.object;
        Value_Holder object_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression_address(context, object_expression, &object_value_holder);
        if (object_value_holder.type->kind != TYPE__POINTER || object_value_holder.type->pointer_data.type->kind != TYPE__POINTER || object_value_holder.type->pointer_data.type->pointer_data.type->kind != TYPE__STRUCT) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Not a struct pointer expression", object_expression->location->line, object_expression->location->column);
        }
        Statement *struct_statement = object_value_holder.type->pointer_data.type->pointer_data.type->struct_data.statement;
        Token *member_name = expression->member_data.name;
        Member *member = NULL;
        for (List_Iterator struct_members = list__create_iterator(struct_statement->struct_data.members); list_iterator__has_next(&struct_members);) {
            Member *struct_member = list_iterator__next(&struct_members);
            if (string__equals(struct_member->name->lexeme, member_name->lexeme->data)) {
                member = struct_member;
                break;
            }
        }
        if (member == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- There is no such struct member: %s.%s", expression->location->line, expression->location->column, context__type_name(context, object_value_holder.type->pointer_data.type->pointer_data.type)->data, member_name->lexeme->data);
        }
        value_holder__acquire_register(destination_value_holder, type__create_pointer(object_expression->location, member->type), context);
        emitf("  mov %s, [%s]", value_holder__register_name(destination_value_holder), value_holder__register_name(&object_value_holder));
        if (member->struct_offset > 0) {
            emitf("  add %s, %d", value_holder__register_name(destination_value_holder), member->struct_offset);
        }
        value_holder__release_register(&object_value_holder);
        return;
    }
    case EXPRESSION__POINTED_VALUE: {
        Expression *pointer_expression = expression->pointed_value_data.expression;
        Value_Holder pointer_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression_address(context, pointer_expression, &pointer_value_holder);
        if (pointer_value_holder.type->kind != TYPE__POINTER || pointer_value_holder.type->pointer_data.type->kind != TYPE__POINTER) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Not a pointer expression", pointer_expression->location->line, pointer_expression->location->column);
        }
        Type *pointed_type = pointer_value_holder.type->pointer_data.type->pointer_data.type;
        value_holder__acquire_register(destination_value_holder, type__create_pointer(pointer_expression->location, pointed_type), context);
        emitf("  mov %s, [%s]", value_holder__register_name(destination_value_holder), value_holder__register_name(&pointer_value_holder));
        value_holder__release_register(&pointer_value_holder);
        return;
    }
    case EXPRESSION__VARIABLE: {
        String *variable_name = expression->variable_data.name->lexeme;
        Variable *variable = context__find_variable(context, variable_name);
        if (variable == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Undeclared variable: %s", expression->location->line, expression->location->column, variable_name->data);
        }
        value_holder__acquire_register(destination_value_holder, type__create_pointer(expression->location, variable->type), context);
        if (variable->is_global) {
            emitf("  lea %s, %s_%03d[rip]", value_holder__register_name(destination_value_holder), variable->name->data, variable->id);
        } else {
            emitf("  mov %s, rbp", value_holder__register_name(destination_value_holder));
            emitf("  sub %s, %d", value_holder__register_name(destination_value_holder), variable->locals_offset);
        }
        return;
    }
    default:
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported expression kind: %s", expression->location->line, expression->location->column, expression__get_kind_name(expression));
    }
}

void emit_expression(Context *context, Expression *expression, Value_Holder *result_value_holder) {
    switch (expression->kind) {
    case EXPRESSION__ARRAY_ITEM: {
        Value_Holder array_item_address_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression_address(context, expression, &array_item_address_value_holder);
        Type *array_item_type = array_item_address_value_holder.type->pointer_data.type;
        value_holder__acquire_register(result_value_holder, array_item_type, context);
        emitf("  mov %s, [%s]", value_holder__register_name(result_value_holder), value_holder__register_name(&array_item_address_value_holder));
        value_holder__release_register(&array_item_address_value_holder);
        return;
    }
    case EXPRESSION__BINARY: {
        Token *operator_token = expression->binary_data.operator_token;
        String *operator = operator_token->lexeme;
        if (string__equals(operator, "+") || string__equals(operator, "-") || string__equals(operator, "*") || string__equals(operator, "/") || string__equals(operator, "//")) {
            emit_arithmetic_expression(context, expression, result_value_holder);
            return;
        } else if (string__equals(operator, "<") || string__equals(operator, "<=") || string__equals(operator, ">") || string__equals(operator, ">=") || string__equals(operator, "==") || string__equals(operator, "!=")) {
            return emit_comparison_expression(context, expression, result_value_holder);
        } else {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported binary expression operator: %s", operator_token->location->line, operator_token->location->column, operator->data);
        }
    }
    case EXPRESSION__CALL: {
        Expression *callee = expression->call_data.callee;
        Argument_List *arguments = expression->call_data.arguments;
        if (callee->kind != EXPRESSION__VARIABLE) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Only simple function calls like \"example()\" are supported", expression->location->line, expression->location->column);
        }

        const int arguments_size = list__size(arguments);
        if (arguments_size > 4) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Function calls with %d arguments are not supported yet", expression->location->line, expression->location->column, arguments_size);
        }
        Value_Holder argument_value_holders[4] = {
            { .kind = VALUE_HOLDER__NEW },
            { .kind = VALUE_HOLDER__NEW },
            { .kind = VALUE_HOLDER__NEW },
            { .kind = VALUE_HOLDER__NEW },
        };
        int argument_register_ids[4] = {
            REGISTER__RDI,
            REGISTER__RSI,
            REGISTER__RDX,
            REGISTER__RCX,
        };
        int last_argument_register_id = REGISTERS_COUNT;
        for (int argument_index = 0; argument_index < arguments_size; argument_index++) {
            Argument *argument = list__get(arguments, argument_index);
            Value_Holder *argument_value_holder = &argument_value_holders[argument_index];
            emit_expression(context, argument->value, argument_value_holder);
            argument->inferred_type = argument_value_holder->type;
            value_holder__move_to_register(argument_value_holder, last_argument_register_id = argument_register_ids[argument_index], context);
        }

        String *function_name = callee->variable_data.name->lexeme;
        Statement *function = named_functions__get(context->named_functions, function_name, arguments);
        if (function == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unknown function: %s", expression->location->line, expression->location->column, function_name->data);
        }

        // TODO: Save used registers in the function frame
        for (int id = 0; id < last_argument_register_id; id++) {
            Value_Holder *value_holder = registers[id];
            if (value_holder != NULL) {
                emitf("  push %s", value_holder__register_name(value_holder));
            }
        }

        emitf("  call %s", function->function_data.unique_name->data);

        for (int id = last_argument_register_id - 1; id >= 0; id--) {
            Value_Holder *value_holder = registers[id];
            if (value_holder != NULL) {
                emitf("  pop %s", value_holder__register_name(value_holder));
            }
        }

        for (int argument_index = arguments_size - 1; argument_index >= 0; argument_index--) {
            value_holder__release_register(&argument_value_holders[argument_index]);
        }

        Type *function_return_type = function->function_data.return_type;
        switch (function_return_type->kind) {
        case TYPE__INT:
        case TYPE__INT64:
        case TYPE__POINTER: {
            value_holder__acquire_register(result_value_holder, function_return_type, context);
            emitf("  mov %s, rax", value_holder__register_name(result_value_holder));
            break;
        }
        case TYPE__INT32: {
            value_holder__acquire_register(result_value_holder, function_return_type, context);
            emitf("  mov %s, eax", value_holder__register_name(result_value_holder));
            break;
        }
        case TYPE__INT16: {
            value_holder__acquire_register(result_value_holder, function_return_type, context);
            emitf("  mov %s, ax", value_holder__register_name(result_value_holder));
            break;
        }
        case TYPE__INT8: {
            value_holder__acquire_register(result_value_holder, function_return_type, context);
            emitf("  mov %s, al", value_holder__register_name(result_value_holder));
            break;
        }
        case TYPE__NOTHING: {
            break;
        }
        default:
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported return type: %s", expression->location->line, expression->location->column, type__get_kind_name(function_return_type));
        }

        return;
    }
    case EXPRESSION__CAST: {
        Type *cast_type = expression->cast_data.type;
        context__resolve_type(context, cast_type);
        value_holder__acquire_register(result_value_holder, cast_type, context);
        Expression *cast_expression = expression->cast_data.expression;
        Value_Holder cast_expression_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression(context, cast_expression, &cast_expression_value_holder);
        Type *cast_expression_type = cast_expression_value_holder.type;
        switch (cast_expression_type->kind) {
        case TYPE__INT8:
            switch (cast_type->kind) {
            case TYPE__INT8:
                emitf("  mov %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                value_holder__release_register(&cast_expression_value_holder);
                WARNING(__FILE__, __LINE__, "(%04d:%04d) -- Redundand cast detected.", cast_type->location->line, cast_type->location->column);
                return;
            case TYPE__INT:
            case TYPE__INT16:
            case TYPE__INT32:
            case TYPE__INT64:
                emitf("  movsx %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                value_holder__release_register(&cast_expression_value_holder);
                return;
            }
            break;
        case TYPE__INT32:
            switch (cast_type->kind) {
            case TYPE__INT32:
                emitf("  mov %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                value_holder__release_register(&cast_expression_value_holder);
                WARNING(__FILE__, __LINE__, "(%04d:%04d) -- Redundand cast detected.", cast_type->location->line, cast_type->location->column);
                return;
            case TYPE__INT:
            case TYPE__INT64:
                emitf("  movsx %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                value_holder__release_register(&cast_expression_value_holder);
                return;
            }
            break;
        case TYPE__INT:
            switch (cast_type->kind) {
            case TYPE__INT:
                emitf("  mov %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                value_holder__release_register(&cast_expression_value_holder);
                WARNING(__FILE__, __LINE__, "(%04d:%04d) -- Redundand cast detected.", cast_type->location->line, cast_type->location->column);
                return;
            }
            break;
        }
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Casting %s to %s is not supported.", cast_expression->location->line, cast_expression->location->column, context__type_name(context, cast_expression_type)->data, context__type_name(context, cast_type)->data);
    }
    case EXPRESSION__LITERAL: {
        emit_load_literal(context, expression->literal_data.value, result_value_holder);
        return;
    }
    case EXPRESSION__MEMBER: {
        Value_Holder member_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression_address(context, expression, &member_value_holder);
        Type *value_type = member_value_holder.type->pointer_data.type;
        value_holder__acquire_register(result_value_holder, value_type, context);
        switch (value_type->kind) {
        case TYPE__BOOLEAN:
        case TYPE__INT:
        case TYPE__INT8:
            emitf("  mov %s, [%s]", value_holder__register_name(result_value_holder), value_holder__register_name(&member_value_holder));
            value_holder__release_register(&member_value_holder);
            return;
        default:
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported value type: %s", expression->pointed_value_data.expression->location->line, expression->pointed_value_data.expression->location->column, context__type_name(context, value_type)->data);
        }
    }
    case EXPRESSION__NEW: {
        Type *type = expression->new_data.type;
        context__resolve_type(context, type);
        Value_Holder type_size_value_holder = { .kind = VALUE_HOLDER__NEW };
        value_holder__acquire_register(&type_size_value_holder, context__get_int_type(context), context);
        emitf("  mov %s, %d", value_holder__register_name(&type_size_value_holder), context__compute_type_size(context, type));
        value_holder__move_to_register(&type_size_value_holder, REGISTER__RDI, context);
        emits("  call malloc");
        value_holder__acquire_register(result_value_holder, type__create_pointer(expression->location, type), context);
        emitf("  mov %s, rax", value_holder__register_name(result_value_holder));
        value_holder__release_register(&type_size_value_holder);
        return;
    }
    case EXPRESSION__POINTED_VALUE: {
        Value_Holder pointer_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression_address(context, expression, &pointer_value_holder);
        Type *value_type = pointer_value_holder.type->pointer_data.type;
        value_holder__acquire_register(result_value_holder, value_type, context);
        switch (value_type->kind) {
        case TYPE__BOOLEAN:
        case TYPE__INT:
        case TYPE__INT8:
            emitf("  mov %s, [%s]", value_holder__register_name(result_value_holder), value_holder__register_name(&pointer_value_holder));
            value_holder__release_register(&pointer_value_holder);
            return;
        default:
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported value type: %s", expression->pointed_value_data.expression->location->line, expression->pointed_value_data.expression->location->column, context__type_name(context, value_type)->data);
        }
    }
    case EXPRESSION__POINTER_TO: {
        emit_expression_address(context, expression->pointer_to_data.expression, result_value_holder);
        return;
    }
    case EXPRESSION__VARIABLE: {
        Value_Holder variable_address_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression_address(context, expression, &variable_address_value_holder);
        Type *variable_type = variable_address_value_holder.type->pointer_data.type;
        value_holder__acquire_register(result_value_holder, variable_type, context);
        switch (variable_type->kind) {
        case TYPE__BOOLEAN:
        case TYPE__INT:
        case TYPE__INT8:
        case TYPE__INT16:
        case TYPE__INT32:
        case TYPE__INT64:
        case TYPE__POINTER:
            emitf("  mov %s, [%s]", value_holder__register_name(result_value_holder), value_holder__register_name(&variable_address_value_holder));
            value_holder__release_register(&variable_address_value_holder);
            return;
        default:
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported type: %s", expression->variable_data.name->location->line, expression->variable_data.name->location->line, context__type_name(context, variable_type)->data);
        }
    }
    default:
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported expression kind: %s", expression->location->line, expression->location->column, expression__get_kind_name(expression));
    }
}

int compute_locals_size(Context *context, Statement_List *statements);

void update_locals_size(Context *context, int locals_size_min, int *locals_size_max, Statement *block_statement) {
    if (block_statement->kind == STATEMENT__BLOCK) {
        int block_locals_size = compute_locals_size(context, block_statement->block_data.statements);
        if (locals_size_min + block_locals_size > *locals_size_max) {
            *locals_size_max = locals_size_min + block_locals_size;
        }
    }
}

int compute_locals_size(Context *context, Statement_List *statements) {
    int locals_size_min = 0;
    int locals_size_max = 0;

    for (List_Iterator iterator = list__create_iterator(statements); list_iterator__has_next(&iterator);) {
        Statement *statement = list_iterator__next(&iterator);
        switch(statement->kind) {
        case STATEMENT__ASSIGNMENT:
        case STATEMENT__BREAK:
        case STATEMENT__EXPRESSION:
        case STATEMENT__RETURN:
            break;
        case STATEMENT__BLOCK: {
            update_locals_size(context, locals_size_min, &locals_size_max, statement);
            break;
        }
        case STATEMENT__IF: {
            update_locals_size(context, locals_size_min, &locals_size_max, statement->if_data.true_block);
            if (statement->if_data.false_block != NULL) {
                update_locals_size(context, locals_size_min, &locals_size_max, statement->if_data.false_block);
            }
            break;
        }
        case STATEMENT__LOOP: {
            update_locals_size(context, locals_size_min, &locals_size_max, statement->loop_data.block);
            break;
        }
        case STATEMENT__VARIABLE: {
            Type *variable_type = statement->variable_data.type;
            if (variable_type == NULL) {
                PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Type inference is not supported yet.", statement->location->line, statement->location->column);
            }
            context__resolve_type(context, variable_type);
            locals_size_min += context__compute_type_size(context, variable_type);
            if (locals_size_min > locals_size_max) {
                locals_size_max = locals_size_min;
            }
            break;
        }
        default:
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported statement kind: %s", statement->location->line, statement->location->column, statement__get_kind_name(statement));
        }
    }

    return locals_size_max;
}

Context *create_function_context(Context *parent_context) {
    Context *context = context__clone(parent_context);
    context->parent_context = parent_context;
    context->variables = variables__create();
    return context;
}

Context *create_block_context(Context *parent_context) {
    Context *context = context__clone(parent_context);
    context->parent_context = parent_context;
    context->variables = variables__create();
    return context;
}

Statement *statement__create_assignment(Source_Location *location, Expression *destination, Token *operator_token, Expression *value);

Expression *expression__create_variable(Token *name);

void emit_statement(Context *context, Statement *statement) {
    switch (statement->kind) {
    case STATEMENT__ASSIGNMENT: {
        Value_Holder destination_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression_address(context, statement->assignment_data.destination, &destination_value_holder);
        Type *destination_type = destination_value_holder.type->pointer_data.type;
        Value_Holder value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression(context, statement->assignment_data.value, &value_holder);
        Type *value_type = value_holder.type;
        if (!type__equals(destination_type, value_type)) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Destination type differs from value type. Expected %s but got %s instead.", statement->location->line, statement->location->column, context__type_name(context, destination_type)->data, context__type_name(context, value_type)->data);
        }
        switch (destination_type->kind) {
        case TYPE__BOOLEAN:
        case TYPE__INT:
        case TYPE__INT8:
        case TYPE__INT16:
        case TYPE__INT32:
        case TYPE__INT64:
        case TYPE__POINTER:
            emitf("  mov [%s], %s", value_holder__register_name(&destination_value_holder), value_holder__register_name(&value_holder));
            break;
        default:
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported variable type: %s.", statement->location->line, statement->location->column, context__type_name(context, destination_type)->data);
        }
        value_holder__release_register(&value_holder);
        value_holder__release_register(&destination_value_holder);
        return;
    }
    case STATEMENT__BLOCK: {
        context = create_block_context(context);

        for (List_Iterator iterator = list__create_iterator(statement->block_data.statements); list_iterator__has_next(&iterator);) {
            Statement *block_statement = list_iterator__next(&iterator);
            emit_statement(context, block_statement);
        }
        return;
    }
    case STATEMENT__BREAK: {
        Loop *loop = context->current_loop;
        if (loop == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- This break is not inside of a loop", statement->location->line, statement->location->column);
        }
        emitf("  jmp loop_%03d_end", loop->id);
        loop->has_exit = 1;
        return;
    }
    case STATEMENT__EXPRESSION: {
        Expression *expression = statement->expression_data.expression;
        Value_Holder value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression(context, expression, &value_holder);
        if (value_holder.kind != VALUE_HOLDER__NEW) {
            WARNING(__FILE__, __LINE__, "(%04d:%04d) -- The result of this expression is ignored", statement->location->line, statement->location->column);
            value_holder__release_register(&value_holder);
        }
        return;
    }
    case STATEMENT__FUNCTION: {
        if (!statement->function_data.is_declaration) {
            context = create_function_context(context);
            context->current_function = statement;

            String *function_unique_name = statement->function_data.unique_name;
            emits("  .text");
            emitf("  .globl %s", function_unique_name->data);
            emitf("%s:", function_unique_name->data);
            emits("  push rbp");
            emits("  mov rbp, rsp");

            int parameter_register_ids[4] = {
                REGISTER__RDI,
                REGISTER__RSI,
                REGISTER__RDX,
                REGISTER__RCX,
            };
            Parameter_List *function_parameters = statement->function_data.parameters;
            int function_parameters_size = list__size(function_parameters);
            for (int parameter_index = 0; parameter_index < function_parameters_size; parameter_index++) {
                Parameter *parameter = list__get(function_parameters, parameter_index);
                Variable *variable = context__create_variable(context, parameter->name->location, parameter->name->lexeme, parameter->type);

                Value_Holder parameter_value_holder = { .kind = VALUE_HOLDER__NEW };
                value_holder__acquire_register(&parameter_value_holder, parameter->type, context);
                int register_id = parameter_value_holder.register_data.id;
                parameter_value_holder.register_data.id = parameter_register_ids[parameter_index];
                emitf("  mov [rbp-%d], %s", variable->locals_offset, value_holder__register_name(&parameter_value_holder));
                parameter_value_holder.register_data.id = register_id;
                value_holder__release_register(&parameter_value_holder);
            }

            int locals_size = compute_locals_size(context, statement->function_data.statements);
            if (function_parameters_size > 0) {
                Variable *variable = list__last(context->variables);
                locals_size += variable->locals_offset;
            }
            if (locals_size > 0) {
                emitf("  sub rsp, %d", (locals_size + 15) & ~15);
            }

            for (List_Iterator iterator = list__create_iterator(statement->function_data.statements); list_iterator__has_next(&iterator);) {
                Statement *body_statement = list_iterator__next(&iterator);
                emit_statement(context, body_statement);
            }

            emitf("%s__end:", function_unique_name->data);
            emits("  mov rsp, rbp");
            emits("  pop rbp");
            emits("  ret");
        }
        return;
    }
    case STATEMENT__IF: {
        int label = counter__inc(context->counter);
        emitf("if_%03d_cond:", label);
        Expression *condition_expression = statement->if_data.condition;
        Value_Holder condition_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression(context, statement->if_data.condition, &condition_value_holder);
        Type *condition_expression_type = condition_value_holder.type;
        if (condition_expression_type->kind != TYPE__BOOLEAN) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Not a boolean expression", condition_expression->location->line, condition_expression->location->column);
        }
        emitf("  dec %s", value_holder__register_name(&condition_value_holder));
        value_holder__release_register(&condition_value_holder);
        emitf("  jnz if_%03d_false", label);
        emitf("if_%03d_true:", label);
        emit_statement(context, statement->if_data.true_block);
        if (statement->if_data.false_block) {
            emitf("  jmp if_%03d_end", label);
        }
        emitf("if_%03d_false:", label);
        if (statement->if_data.false_block) {
            emit_statement(context, statement->if_data.false_block);
        }
        emitf("if_%03d_end:", label);
        break;
    }
    case STATEMENT__LOOP: {
        int label = counter__inc(context->counter);
        emitf("loop_%03d_start:", label);
        context->current_loop = loop__create(label, context->current_loop);
        emit_statement(context, statement->loop_data.block);
        if (!context->current_loop->has_exit) {
            WARNING(__FILE__, __LINE__, "(%04d:%04d) -- Infinite loop detected.", statement->location->line, statement->location->column);
        }
        context->current_loop = context->current_loop->parent;
        emitf("  jmp loop_%03d_start", label);
        emitf("loop_%03d_end:", label);
        break;
    }
    case STATEMENT__RETURN: {
        Statement *function = context->current_function;
        if (function == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Found return statement outside of a function.", statement->location->line, statement->location->column);
        }
        Type *function_return_type = function->function_data.return_type;
        if (statement->return_data.expression != NULL) {
            Expression *return_expression = statement->return_data.expression;
            Value_Holder value_holder = { .kind = VALUE_HOLDER__NEW };
            emit_expression(context, return_expression, &value_holder);
            Type *return_expression_type = value_holder.type;
            if (!type__equals(function_return_type, return_expression_type)) {
                PANIC(__FILE__, __LINE__, "(%04d:%04d) -- The return expression must be of type %s, got %s instead.", return_expression->location->line, return_expression->location->column, context__type_name(context, function_return_type)->data, context__type_name(context, return_expression_type)->data);
            }
            emitf("  mov rax, %s", value_holder__register_name(&value_holder));
            value_holder__release_register(&value_holder);
        } else if (function_return_type->kind != TYPE__NOTHING) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Expected return expression", statement->location->line, statement->location->column);
        }
        if (context->current_loop) {
            context->current_loop->has_exit = 1;
        }
        emitf("  jmp %s__end", function->function_data.unique_name->data);
        return;
    }
    case STATEMENT__STRUCT:
        return;
    case STATEMENT__VARIABLE: {
        Token *variable_name = statement->variable_data.name;
        if (statement->variable_data.is_external) {
            Type *variable_type = statement->variable_data.type;
            if (variable_type == NULL) {
                PANIC(__FILE__, __LINE__, "(%04d:%04d) -- External variables must have an explicit type.", statement->location->line, statement->location->column);
            }
            context__create_variable(context, variable_name->location, variable_name->lexeme, variable_type);
        } else {
            Type *variable_type = statement->variable_data.type;
            if (variable_type == NULL) {
                PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Type inference for global variables is not supported yet", statement->location->line, statement->location->column);
            }
            Variable *variable = context__create_variable(context, variable_name->location, variable_name->lexeme, variable_type);
            if (variable->is_global) {
                emits("  .bss");
                switch (variable_type->kind) {
                case TYPE__ARRAY: {
                    int variable_size = context__compute_type_size(context, variable_type);
                    if (variable_size == 0) {
                        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Missing array size", variable_type->location->line, variable_type->location->column);
                    }
                    emitf("%s_%03d: .zero %d", variable_name->lexeme->data, variable->id, variable_size);
                    break;
                }
                case TYPE__BOOLEAN:
                case TYPE__INT8:
                    emitf("%s_%03d: .byte 0", variable_name->lexeme->data, variable->id);
                    break;
                case TYPE__INT:
                case TYPE__POINTER:
                    emitf("%s_%03d: .quad 0", variable_name->lexeme->data, variable->id);
                    break;
                default:
                    PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported variable type: %s", statement->location->line, statement->location->column, type__get_kind_name(variable_type));
                }
            } else {
                Expression *variable_value = statement->variable_data.value;
                if (variable_value) {
                    static Statement *assignment_statement = NULL;
                    if (assignment_statement == NULL) {
                        Source_Location *location = source_location__create(variable_name->location->source);
                        Token *operator_token = token__create_other(location, string__create("="));
                        assignment_statement = statement__create_assignment(location, NULL, operator_token, NULL);
                    }
                    static Expression *assignment_destination = NULL;
                    if (assignment_destination == NULL) {
                        assignment_destination = expression__create_variable(variable_name);
                        assignment_statement->assignment_data.destination = assignment_destination;
                    } else {
                        assignment_destination->variable_data.name = variable_name;
                    }
                    assignment_statement->assignment_data.value = variable_value;
                    emit_statement(context, assignment_statement);
                }
            }
        }
        return;
    }
    default:
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported statement kind: %s", statement->location->line, statement->location->column, statement__get_kind_name(statement));
    }
}

void generate(char *file, Compilation_Unit *compilation_unit) {
    Context *context = context__create(fopen(file, "w"), compilation_unit->named_functions, compilation_unit->named_types);
    emits("  .intel_syntax noprefix");

    for (List_Iterator iterator = list__create_iterator(compilation_unit->statements); list_iterator__has_next(&iterator);) {
        Statement *statement = list_iterator__next(&iterator);
        switch (statement->kind) {
        case STATEMENT__FUNCTION:
            context__resolve_type(context, statement->function_data.return_type);
            for (List_Iterator parameters = list__create_iterator(statement->function_data.parameters); list_iterator__has_next(&parameters);) {
                Parameter *parameter = list_iterator__next(&parameters);
                context__resolve_type(context, parameter->type);
            }
            break;
        case STATEMENT__STRUCT: {
            if (statement->struct_data.members) {
                for (List_Iterator members = list__create_iterator(statement->struct_data.members); list_iterator__has_next(&members);) {
                    Member *member = list_iterator__next(&members);
                    context__resolve_type(context, member->type);
                }
            }
            break;
        }
        case STATEMENT__VARIABLE:
            context__resolve_type(context, statement->variable_data.type);
            break;
        }
    }

    for (List_Iterator iterator = list__create_iterator(compilation_unit->statements); list_iterator__has_next(&iterator);) {
        Statement *statement = list_iterator__next(&iterator);
        emits("");
        emit_statement(context, statement);

        for (int id = 0; id < REGISTERS_COUNT; id++) {
            if (registers[id] != NULL) {
                PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unrelease register found: %s", statement->location->line, statement->location->column, value_holder__register_name(registers[id]));
            }
        }
    }

    for (int index = 0; index < list__size(context->string_constants); index++) {
        Token *string_constant = list__get(context->string_constants, index);
        emits("");
        emits("  .data");
        emitf("__data__%d__string__: .string %s", index, string_constant->lexeme->data);
    }

    fclose(context->file);
}
