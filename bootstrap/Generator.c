#include "Generator.h"
#include "Logging.h"

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
// #define emitf(line, ...) fprintf(context->file, line " ;# %s:%d" "\n", __VA_ARGS__, __FILE__, __LINE__)
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

int context__add_string_constant(Context *self, Token *string_token) {
    int index = 0;
    for (List_Iterator iterator = list__create_iterator(self->string_constants); list_iterator__has_next(&iterator); index++) {
        Token *other_string_token = list_iterator__next(&iterator);
        if (string__equals(other_string_token->string_data.value, string_token->string_data.value->data)) {
            return index;
        }
    }
    list__append(self->string_constants, string_token);
    return index;
}

Statement *context__find_variable(Context *self, String *name) {
    for (List_Iterator iterator = list__create_reversed_iterator(self->variables); list_iterator__has_next(&iterator);) {
        Statement *variable_statement = list_iterator__next(&iterator);
        if (string__equals(name, variable_statement->variable_data.name->lexeme->data)) {
            return variable_statement;
        }
    }
    if (self == self->global_context) {
        return NULL;
    }
    return context__find_variable(self->parent_context, name);
}

int context__compute_type_size(Context *self, Type *type);

Statement *context__last_local_variable(Context *self) {
    if (self->global_context == self) {
        return NULL;
    }
    Statement *variable_statement = list__last(self->variables);
    if (variable_statement != NULL) {
        return variable_statement;
    }
    return context__last_local_variable(self->parent_context);
}

Statement *context__add_variable(Context *self, Statement *variable_statement) {
    String *unique_name = string__create(variable_statement->variable_data.name->lexeme->data);
    string__append_char(unique_name, '_');
    int count = counter__inc(self->counter);
    if (count < 1000) string__append_char(unique_name, '0');
    if (count < 100) string__append_char(unique_name, '0');
    string__append_int(unique_name, count);
    variable_statement->variable_data.unique_name = unique_name;
    variable_statement->variable_data.is_global = self->current_function == NULL;

    Statement *previous_variable_statement = context__last_local_variable(self);
    variable_statement->variable_data.locals_offset = (previous_variable_statement != NULL ? previous_variable_statement->variable_data.locals_offset : 0) + context__compute_type_size(self, variable_statement->variable_data.type);

    list__append(self->variables, variable_statement);

    return variable_statement;
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
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported type kind: %s", SOURCE(type->location), type__get_kind_name(type));
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
        case TYPE__INT:
        case TYPE__INT8:
        case TYPE__INT16:
        case TYPE__INT32:
        case TYPE__INT64: {
            return;
        }
        case TYPE__NAMED: {
            String *type_name = type->named_data.name->lexeme;
            Type *named_type = context__find_type(self, type_name);
            if (named_type == NULL) {
                PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unknown type: %s", SOURCE(type->location), type_name->data);
            }
            type__convert(type, named_type);
            return;
        }
        case TYPE__POINTER: {
            context__resolve_type(self, type->pointer_data.type);
            return;
        }
        case TYPE__STRUCT: {
            return;
        }
        default:
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported type kind: %s", SOURCE(type->location), type__get_kind_name(type));
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
    case TYPE__NULL:
    case TYPE__POINTER:
        return 1;
    default:
        return 0;
    }
}

int context__is_object_type(Context *self, Type *type) {
    if (type->kind != TYPE__STRUCT) {
        return 0;
    }
    if (string__equals(context__type_name(self, type), "Object")) {
        return 1;
    }
    Type *struct_base_type = type->struct_data.statement->struct_data.base_type;
    if (struct_base_type == NULL) {
        return 0;
    }
    return context__is_object_type(self, struct_base_type);
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

Type *context__get_null_type(Context *self) {
    static String *type_name = NULL;
    if (type_name == NULL) {
        type_name = string__create("null");
    }
    return context__find_type(self, type_name);
}

Type *context__get_string_type(Context *self) {
    static String *type_name = NULL;
    if (type_name == NULL) {
        type_name = string__create("String");
    }
    return context__find_type(self, type_name);
}

Type *context__get_type_type(Context *self) {
    static String *type_name = NULL;
    if (type_name == NULL) {
        type_name = string__create("Type");
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
        return 8;
    case TYPE__NOTHING:
        return 0;
    case TYPE__NULL:
        return 8;
    case TYPE__NAMED: {
        String *type_name = type->named_data.name->lexeme;
        Type *named_type = context__find_type(self, type_name);
        if (named_type == NULL) {
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unknown type: %s", SOURCE(type->location), type_name->data);
        }
        return context__compute_type_size(self, named_type);
    }
    case TYPE__POINTER: {
        context__compute_type_size(self, type->pointer_data.type);
        return 8;
    }
    case TYPE__STRUCT: {
        Statement *struct_statement = type->struct_data.statement;
        int struct_size = struct_statement->struct_data.size;
        if (struct_statement->struct_data.has_computed_size == 0) {
            type->struct_data.statement->struct_data.has_computed_size = 1;
            if (struct_statement->struct_data.base_type != NULL) {
                struct_size = context__compute_type_size(self, struct_statement->struct_data.base_type);
            }
            if (struct_statement->struct_data.members != NULL) {
                for (List_Iterator members = list__create_iterator(struct_statement->struct_data.members); list_iterator__has_next(&members);) {
                    Member *struct_member = list_iterator__next(&members);
                    struct_member->struct_offset = struct_size;
                    struct_size += context__compute_type_size(self, struct_member->type);
                }
            }
            type->struct_data.statement->struct_data.size = struct_size;
        }
        return struct_size;
    }
    default:
        PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported type kind: %s", SOURCE(type->location), type__get_kind_name(type));
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

void panic__unknown_function(Context *context, Token *function_name, Type_List *argument_types) {
    for (List_Iterator functions = list__create_iterator(context->named_functions); list_iterator__has_next(&functions);) {
        Statement *statement = list_iterator__next(&functions);
        if (string__equals(function_name->lexeme, statement->function_data.name->lexeme->data)) {
            String *function_signature = string__create(statement->function_data.name->lexeme->data);
            string__append_chars(function_signature, " :: (", 5);
            for (List_Iterator parameters = list__create_iterator(statement->function_data.parameters); list_iterator__has_next(&parameters);) {
                Parameter *parameter = list_iterator__next(&parameters);
                string__append_string(function_signature, parameter->name->lexeme);
                string__append_chars(function_signature, ": ", 2);
                string__append_string(function_signature, context__type_name(context, parameter->type));
                if (list_iterator__has_next(&parameters)) {
                    string__append_chars(function_signature, ", ", 2);
                }
            }
            string__append_chars(function_signature, ") -> ", 5);
            string__append_string(function_signature, context__type_name(context, statement->function_data.return_type));
            WARNING(__FILE__, __LINE__, SOURCE_LOCATION "%s", SOURCE(statement->location), function_signature->data);
        }
    }
    String *function_signature = string__create(function_name->lexeme->data);
    string__append_chars(function_signature, " :: (", 5);
    for (List_Iterator iterator = list__create_iterator(argument_types); list_iterator__has_next(&iterator);) {
        Type *argument_type = list_iterator__next(&iterator);
        string__append_chars(function_signature, "_: ", 3);
        string__append_string(function_signature, context__type_name(context, argument_type));
        if (list_iterator__has_next(&iterator)) {
            string__append_chars(function_signature, ", ", 2);
        }
    }
    string__append_chars(function_signature, ") -> Any", 8);
    PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unknown function: %s", SOURCE(function_name->location), function_signature->data);
}

Member *context__get_struct_type_member(Context *self, Type *struct_type, Token *member_name) {
    Type *type = struct_type;
    while (type != NULL) {
        for (List_Iterator members = list__create_iterator(type->struct_data.statement->struct_data.members); list_iterator__has_next(&members);) {
            Member *member = list_iterator__next(&members);
            if (string__equals(member->name->lexeme, member_name->lexeme->data)) {
                return member;
            }
        }
        type = type->struct_data.statement->struct_data.base_type;
    }
    PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Type '%s' has no '%s' member.", SOURCE(member_name->location), context__type_name(self, struct_type)->data, member_name->lexeme->data);
}

void infer_expression_type(Context *context, Expression *expression) {
    if (expression->inferred_type != NULL) {
        return;
    }
    switch (expression->kind) {
        case EXPRESSION__ARRAY_ITEM: {
            Expression *array = expression->array_item_data.array;
            infer_expression_type(context, array);
            switch (array->inferred_type->kind) {
                case TYPE__POINTER: {
                    expression->inferred_type = array->inferred_type->pointer_data.type;
                    return;
                }
                default:
                    PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Cannot infer item type from type kind: %s.", SOURCE(expression->location), type__get_kind_name(array->inferred_type));
            }
        }
        case EXPRESSION__BINARY: {
            infer_expression_type(context, expression->binary_data.left_expression);
            infer_expression_type(context, expression->binary_data.right_expression);
            Type *left_expression_type = expression->binary_data.left_expression->inferred_type;
            Type *right_expression_type = expression->binary_data.right_expression->inferred_type;
            if (!type__equals(left_expression_type, right_expression_type)) {
                PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Left expression type %s doesn't match the right expression type %s.", SOURCE(expression->binary_data.operator_token->location), context__type_name(context, left_expression_type)->data, context__type_name(context, right_expression_type)->data);
            }
            String *operator = expression->binary_data.operator_token->lexeme;
            if (string__equals(operator, "+") || string__equals(operator, "-") || string__equals(operator, "*") || string__equals(operator, "/") || string__equals(operator, "//")) {
                expression->inferred_type = left_expression_type;
                return;
            }
            if (string__equals(operator, "==")) {
                expression->inferred_type = context__get_boolean_type(context);
                return;
            }
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Cannot infer type from \"%s\" expression.", SOURCE(expression->binary_data.operator_token->location), operator->data);
        }
        case EXPRESSION__CALL: {
            Argument_List *arguments = expression->call_data.arguments;
            Type_List *argument_types = list__create();
            for (List_Iterator iterator = list__create_iterator(arguments); list_iterator__has_next(&iterator);) {
                Argument *argument = list_iterator__next(&iterator);
                infer_expression_type(context, argument->value);
                Type *argument_type = argument->value->inferred_type;
                if (argument_type->kind == TYPE__STRUCT) {
                    argument_type = type__create_pointer(argument->value->location, argument_type);
                }
                list__append(argument_types, argument_type);
            }
            Expression *callee = expression->call_data.callee;
            switch (callee->kind) {
                case EXPRESSION__VARIABLE: {
                    Token *function_name = callee->variable_data.name;
                    Statement *function = named_functions__get(context->named_functions, function_name, argument_types);
                    if (function == NULL) {
                        panic__unknown_function(context, function_name, argument_types);
                    }
                    expression->inferred_type = function->function_data.return_type;
                    return;
                }
                default:
                    PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported callee expression kind: %s", SOURCE(callee->location), expression__get_kind_name(callee));
            }
        }
        case EXPRESSION__CAST: {
            infer_expression_type(context, expression->cast_data.expression);
            context__resolve_type(context, expression->cast_data.type);
            expression->inferred_type = expression->cast_data.type;
            return;
        }
        case EXPRESSION__LITERAL: {
            switch (expression->literal_data.value->kind) {
                case TOKEN__CHARACTER:
                    expression->inferred_type = context__get_int8_type(context);
                    return;
                case TOKEN__INTEGER:
                    expression->inferred_type = context__get_int_type(context);
                    return;
                case TOKEN__KEYWORD:
                    if (string__equals(expression->literal_data.value->lexeme, "true") || string__equals(expression->literal_data.value->lexeme, "false")) {
                        expression->inferred_type = context__get_boolean_type(context);
                        return;
                    }
                    if (string__equals(expression->literal_data.value->lexeme, "null")) {
                        expression->inferred_type = context__get_null_type(context);
                        return;
                    }
                    PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Cannot infer type of '%s' yet.", SOURCE(expression->location), expression->literal_data.value->lexeme->data);
                case TOKEN__STRING:
                    expression->inferred_type = type__create_pointer(expression->literal_data.value->location, context__get_string_type(context));
                    return;
            }
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Cannot infer type of %s literals yet.", SOURCE(expression->location), token__get_kind_name(expression->literal_data.value));
        }
        case EXPRESSION__MEMBER: {
            Expression *object = expression->member_data.object;
            infer_expression_type(context, object);
            Type *object_type = object->inferred_type;
            switch (object_type->kind) {
                case TYPE__POINTER: {
                    Type *pointed_type = object_type->pointer_data.type;
                    if (pointed_type->kind == TYPE__STRUCT) {
                        Token *member_name = expression->member_data.name;
                        Member *member = context__get_struct_type_member(context, pointed_type, member_name);
                        expression->inferred_type = member->type;
                        return;
                    }
                    break;
                }
                case TYPE__STRUCT: {
                    Token *member_name = expression->member_data.name; 
                    for (List_Iterator members = list__create_iterator(object_type->struct_data.statement->struct_data.members); list_iterator__has_next(&members);) {
                        Member *member = list_iterator__next(&members);
                        if (string__equals(member->name->lexeme, member_name->lexeme->data)) {
                            expression->inferred_type = member->type;
                            return;
                        }
                    }
                    PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Type %s has no '%s' member.", SOURCE(member_name->location), context__type_name(context, object_type)->data, member_name->lexeme->data);
                }
            }
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Cannot infer member type from type kind: %s.", SOURCE(object->location), type__get_kind_name(object_type));
        }
        case EXPRESSION__VARIABLE: {
            String *variable_name = expression->variable_data.name->lexeme;
            Statement *variable_statement = context__find_variable(context, variable_name);
            if (variable_statement == NULL) {
                PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Undeclared variable: %s", SOURCE(expression->location), variable_name->data);
            }
            expression->inferred_type = variable_statement->variable_data.type;
            context__resolve_type(context, expression->inferred_type);
            return;
        }
    }
    PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Cannot infer type of %s expressions yet.", SOURCE(expression->location), expression__get_kind_name(expression));
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
        if (string__equals(token->lexeme, "null")) {
            value_holder__acquire_register(value_holder, context__get_null_type(context), context);
            emitf("  xor %s, %s", value_holder__register_name(value_holder), value_holder__register_name(value_holder));
            return;
        } 
        PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported keyword: %s", SOURCE(token->location), token->lexeme->data);
    }
    case TOKEN__STRING: {
        int index = context__add_string_constant(context, token);
        value_holder__acquire_register(value_holder, type__create_pointer(token->location, context__get_string_type(context)), context);
        emitf("  lea %s, L%03d_STRING[rip]", value_holder__register_name(value_holder), index);
        return;
    }
    default:
        PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported token kind: %s", SOURCE(token->location), token__get_kind_name(token));
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
        PANIC(__FILE__, __LINE__, SOURCE_LOCATION "You can \"%s\" only integer values", SOURCE(operator_token->location), operator->data);
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
        PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported arithmetic expression operator: %s", SOURCE(operator_token->location), operator->data);
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
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "You can use \"%s\" only for integer values", SOURCE(operator_token->location), operator->data);
        }
    } else if (string__equals(operator, "==") || string__equals(operator, "!=")) {
        if (!type__equals(result_value_holder->type, right_value_holder.type) && result_value_holder->type->kind != TYPE__POINTER && right_value_holder.type->kind != TYPE__NULL) {
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "You cannot use \"%s\" to compare %s with %s values", SOURCE(operator_token->location), operator->data, context__type_name(context, result_value_holder->type)->data, context__type_name(context, right_value_holder.type)->data);
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
        PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported comparison expression operator: %s", SOURCE(operator_token->location), operator->data);
    }
}

void emit_logical_expression(Context *context, Expression *expression, Value_Holder *result_value_holder) {
    int count = counter__inc(context->counter);
    Token *operator_token = expression->binary_data.operator_token;
    emit_expression(context, expression->binary_data.left_expression, result_value_holder);
    if (result_value_holder->type->kind != TYPE__BOOLEAN) {
        PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Left expression of \"%s\" is not a boolean expression.", SOURCE(operator_token->location), operator_token->lexeme->data);
    }
    emitf("  dec %s", value_holder__register_name(result_value_holder));
    if (string__equals(operator_token->lexeme, "&&")) {
        emitf("  jnz .L_and_%03d_false", count);

        Value_Holder right_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression(context, expression->binary_data.right_expression, &right_value_holder);
        emitf("  dec %s", value_holder__register_name(&right_value_holder));
        value_holder__release_register(&right_value_holder);
        emitf("  jz .L_and_%03d_true", count);

        emitf(".L_and_%03d_false:", count);
        emitf("  mov %s, 0", value_holder__register_name(result_value_holder));
        emitf("  jmp .L_and_%03d_end", count);
        emitf(".L_and_%03d_true:", count);
        emitf("  mov %s, 1", value_holder__register_name(result_value_holder));
        emitf(".L_and_%03d_end:", count);
    } else if (string__equals(operator_token->lexeme, "||")) {
        emitf("  jz .L_or_%03d_true", count);

        Value_Holder right_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression(context, expression->binary_data.right_expression, &right_value_holder);
        emitf("  dec %s", value_holder__register_name(&right_value_holder));
        value_holder__release_register(&right_value_holder);
        emitf("  jz .L_or_%03d_true", count);

        emitf(".L_or_%03d_false:", count);
        emitf("  mov %s, 0", value_holder__register_name(result_value_holder));
        emitf("  jmp .L_or_%03d_end", count);
        emitf(".L_or_%03d_true:", count);
        emitf("  mov %s, 1", value_holder__register_name(result_value_holder));
        emitf(".L_or_%03d_end:", count);
    } else {
        PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported logical expression operator: %s", SOURCE(operator_token->location), operator_token->lexeme->data);
    }
}

void emit_expression_address(Context *context, Expression *expression, Value_Holder *destination_value_holder) {
    switch (expression->kind) {
    case EXPRESSION__ARRAY_ITEM: {
        Expression *address_expression = expression->array_item_data.array;
        Value_Holder address_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression_address(context, address_expression, &address_value_holder);
        if (!(address_value_holder.type->kind == TYPE__POINTER && (address_value_holder.type->pointer_data.type->kind == TYPE__ARRAY || address_value_holder.type->pointer_data.type->kind == TYPE__POINTER))) {
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Not an array expression", SOURCE(address_expression->location));
        }
        Expression *index_expression = expression->array_item_data.index;
        Value_Holder index_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression(context, index_expression, &index_value_holder);
        if (index_value_holder.type->kind != TYPE__INT) {
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Not an integer expression", SOURCE(index_expression->location));
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
    case EXPRESSION__LITERAL: {
        Token *value_token = expression->literal_data.value;
        if (value_token->kind == TOKEN__STRING) {
            int index = context__add_string_constant(context, value_token);
            value_holder__acquire_register(destination_value_holder, type__create_pointer(value_token->location, type__create_pointer(value_token->location, context__get_string_type(context))), context);
            emitf("  lea %s, L%03d_STRING_PTR[rip]", value_holder__register_name(destination_value_holder), index);
            return;
        }
        PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported literal kind: %s", SOURCE(value_token->location), token__get_kind_name(value_token));
    }
    case EXPRESSION__MEMBER: {
        Expression *object_expression = expression->member_data.object;
        Value_Holder object_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression_address(context, object_expression, &object_value_holder);
        if (object_value_holder.type->kind != TYPE__POINTER || object_value_holder.type->pointer_data.type->kind != TYPE__POINTER || object_value_holder.type->pointer_data.type->pointer_data.type->kind != TYPE__STRUCT) {
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Not a struct pointer expression", SOURCE(object_expression->location));
        }
        Statement *struct_statement = object_value_holder.type->pointer_data.type->pointer_data.type->struct_data.statement;
        Token *member_name = expression->member_data.name;
        Member *member = context__get_struct_type_member(context, object_value_holder.type->pointer_data.type->pointer_data.type, member_name);
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
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Not a pointer expression", SOURCE(pointer_expression->location));
        }
        Type *pointed_type = pointer_value_holder.type->pointer_data.type->pointer_data.type;
        value_holder__acquire_register(destination_value_holder, type__create_pointer(pointer_expression->location, pointed_type), context);
        emitf("  mov %s, [%s]", value_holder__register_name(destination_value_holder), value_holder__register_name(&pointer_value_holder));
        value_holder__release_register(&pointer_value_holder);
        return;
    }
    case EXPRESSION__VARIABLE: {
        String *variable_name = expression->variable_data.name->lexeme;
        Statement *variable_statement = context__find_variable(context, variable_name);
        if (variable_statement == NULL) {
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Undeclared variable: %s", SOURCE(expression->location), variable_name->data);
        }
        value_holder__acquire_register(destination_value_holder, type__create_pointer(expression->location, variable_statement->variable_data.type), context);
        if (variable_statement->variable_data.is_global) {
            emitf("  lea %s, %s[rip]", value_holder__register_name(destination_value_holder), variable_statement->variable_data.unique_name->data);
        } else {
            emitf("  mov %s, rbp", value_holder__register_name(destination_value_holder));
            emitf("  sub %s, %d", value_holder__register_name(destination_value_holder), variable_statement->variable_data.locals_offset);
        }
        return;
    }
    default:
        PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported expression kind: %s", SOURCE(expression->location), expression__get_kind_name(expression));
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
        } else if (string__equals(operator, "&&") || string__equals(operator, "||")) {
            return emit_logical_expression(context, expression, result_value_holder);
        } else {
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported binary expression operator: %s", SOURCE(operator_token->location), operator->data);
        }
    }
    case EXPRESSION__CALL: {
        Token *function_name;

        Expression *callee = expression->call_data.callee;
        switch (callee->kind) {
        case EXPRESSION__VARIABLE:
            function_name = callee->variable_data.name;
            break;
        default:
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Only simple function calls like \"example()\" are supported", SOURCE(expression->location));
        }

        Argument_List *arguments = expression->call_data.arguments;
        const int arguments_size = list__size(arguments);
        if (arguments_size > 4) {
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Function calls with %d arguments are not supported yet", SOURCE(expression->location), arguments_size);
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
        Type_List *argument_types = list__create();
        for (int argument_index = 0; argument_index < arguments_size; argument_index++) {
            Argument *argument = list__get(arguments, argument_index);
            infer_expression_type(context, argument->value);
            Value_Holder *argument_value_holder = &argument_value_holders[argument_index];
            if (argument->value->inferred_type->kind == TYPE__STRUCT) {
                emit_expression_address(context, argument->value, argument_value_holder);
            } else {
                emit_expression(context, argument->value, argument_value_holder);
            }
            list__append(argument_types, argument_value_holder->type);
        }

        int last_argument_register_id = REGISTERS_COUNT;
        for (int index = 0; index < 4; index++) {
            Value_Holder *argument_value_holder = &argument_value_holders[index];
            if (argument_value_holder->kind != VALUE_HOLDER__NEW) {
                value_holder__move_to_register(argument_value_holder, argument_register_ids[index], context);
                last_argument_register_id = argument_value_holder->register_data.id;
            }
        }

        Statement *function = named_functions__get(context->named_functions, function_name, argument_types);
        if (function == NULL) {
            panic__unknown_function(context, function_name, argument_types);
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

        for (int index = 0; index < 4; index++) {
            if (argument_value_holders[index].kind != VALUE_HOLDER__NEW) {
                value_holder__release_register(&argument_value_holders[index]);
            }
        }

        Type *function_return_type = function->function_data.return_type;
        switch (function_return_type->kind) {
        case TYPE__BOOLEAN:
        case TYPE__INT8: {
            value_holder__acquire_register(result_value_holder, function_return_type, context);
            emitf("  mov %s, al", value_holder__register_name(result_value_holder));
            break;
        }
        case TYPE__INT16: {
            value_holder__acquire_register(result_value_holder, function_return_type, context);
            emitf("  mov %s, ax", value_holder__register_name(result_value_holder));
            break;
        }
        case TYPE__INT32: {
            value_holder__acquire_register(result_value_holder, function_return_type, context);
            emitf("  mov %s, eax", value_holder__register_name(result_value_holder));
            break;
        }
        case TYPE__INT:
        case TYPE__INT64:
        case TYPE__POINTER: {
            value_holder__acquire_register(result_value_holder, function_return_type, context);
            emitf("  mov %s, rax", value_holder__register_name(result_value_holder));
            break;
        }
        case TYPE__NOTHING: {
            break;
        }
        default:
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported return type: %s", SOURCE(expression->location), type__get_kind_name(function_return_type));
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
            case TYPE__INT:
                switch (cast_type->kind) {
                case TYPE__INT:
                    emitf("  mov %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                    value_holder__release_register(&cast_expression_value_holder);
                    WARNING(__FILE__, __LINE__, SOURCE_LOCATION "Redundand cast detected.", SOURCE(cast_type->location));
                    return;
                case TYPE__INT8:
                    cast_expression_value_holder.size = 1;
                    emitf("  mov %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                    value_holder__release_register(&cast_expression_value_holder);
                    return;
                case TYPE__INT32:
                    cast_expression_value_holder.size = 4;
                    emitf("  mov %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                    value_holder__release_register(&cast_expression_value_holder);
                    return;
                case TYPE__INT64:
                    emitf("  mov %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                    value_holder__release_register(&cast_expression_value_holder);
                    return;
                }
                break;
            case TYPE__INT8:
                switch (cast_type->kind) {
                case TYPE__INT8:
                    emitf("  mov %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                    value_holder__release_register(&cast_expression_value_holder);
                    WARNING(__FILE__, __LINE__, SOURCE_LOCATION "Redundand cast detected.", SOURCE(cast_type->location));
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
            case TYPE__INT16:
                switch (cast_type->kind) {
                case TYPE__INT16:
                    emitf("  mov %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                    value_holder__release_register(&cast_expression_value_holder);
                    WARNING(__FILE__, __LINE__, SOURCE_LOCATION "Redundand cast detected.", SOURCE(cast_type->location));
                    return;
                case TYPE__INT:
                case TYPE__INT32:
                case TYPE__INT64:
                    emitf("  movsx %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                    value_holder__release_register(&cast_expression_value_holder);
                    return;
                }
                break;
            case TYPE__INT32:
                switch (cast_type->kind) {
                case TYPE__INT8:
                    cast_expression_value_holder.size = 1;
                    emitf("  mov %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                    value_holder__release_register(&cast_expression_value_holder);
                    return;
                case TYPE__INT32:
                    emitf("  mov %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                    value_holder__release_register(&cast_expression_value_holder);
                    WARNING(__FILE__, __LINE__, SOURCE_LOCATION "Redundand cast detected.", SOURCE(cast_type->location));
                    return;
                case TYPE__INT:
                case TYPE__INT64:
                    emitf("  movsx %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                    value_holder__release_register(&cast_expression_value_holder);
                    return;
                }
                break;
            case TYPE__INT64:
                switch (cast_type->kind) {
                case TYPE__INT:
                    emitf("  mov %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                    value_holder__release_register(&cast_expression_value_holder);
                    return;
                case TYPE__INT64:
                    emitf("  mov %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                    value_holder__release_register(&cast_expression_value_holder);
                    WARNING(__FILE__, __LINE__, SOURCE_LOCATION "Redundand cast detected.", SOURCE(cast_type->location));
                    return;
                }
                break;
            case TYPE__NULL: {
                if (cast_type->kind == TYPE__POINTER) {
                    emitf("  mov %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                    value_holder__release_register(&cast_expression_value_holder);
                    return;
                }
                break;
            }
            case TYPE__POINTER: {
                if (cast_type->kind == TYPE__POINTER) {
                    // TODO: make sure pointed type are compatible
                    emitf("  mov %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(&cast_expression_value_holder));
                    value_holder__release_register(&cast_expression_value_holder);
                    return;
                }
                break;
            }
        }
        PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Casting %s to %s is not supported.", SOURCE(cast_expression->location), context__type_name(context, cast_expression_type)->data, context__type_name(context, cast_type)->data);
    }
    case EXPRESSION__IS: {
        Expression *is_expression = expression->is_data.expression;
        Value_Holder is_expression_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression(context, is_expression, &is_expression_value_holder);
        Type *is_expression_type = is_expression_value_holder.type;
        if (is_expression_type->kind != TYPE__POINTER || !context__is_object_type(context, is_expression_type->pointer_data.type)) {
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "The checked value is not a pointer to an object type.", SOURCE(is_expression->location));
        }
        Type *is_type = expression->is_data.type;
        context__resolve_type(context, is_type);
        if (!context__is_object_type(context, is_type)) {
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "'%s' is not an object type.", SOURCE(is_type->location), context__type_name(context, is_type)->data);
        }
        Type *base_type = is_expression_type->pointer_data.type;
        Type *type = is_type;
        while (type != NULL && !type__equals(type, base_type)) {
            type = type->struct_data.statement->struct_data.base_type;
        }
        if (type == NULL) {
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "'%s' is not a sub-type of '%s'.", SOURCE(is_type->location), context__type_name(context, is_type)->data, context__type_name(context, base_type)->data);
        }
        int is_count = counter__inc(context->counter);
        value_holder__acquire_register(result_value_holder, context__get_boolean_type(context), context);
        emitf(".L_is_%03d:", is_count);
        emitf("  xor %s, %s", value_holder__register_name(result_value_holder), value_holder__register_name(result_value_holder));
        emitf(".L_is_%03d_loop:", is_count);
        emitf("  mov rax, %s[rip]", context__find_variable(context, is_type->name)->variable_data.unique_name->data);
        emitf("  cmp rax, [%s]", value_holder__register_name(&is_expression_value_holder));
        emitf("  jz .L_is_%03d_true", is_count);
        emitf("  mov %s, [%s]", value_holder__register_name(&is_expression_value_holder), value_holder__register_name(&is_expression_value_holder));
        emitf("  add %s, 8", value_holder__register_name(&is_expression_value_holder));
        emitf("  mov rax, [%s]", value_holder__register_name(&is_expression_value_holder));
        emits("  test rax, rax");
        emitf("  jz .L_is_%03d_end", is_count);
        emitf("  jmp .L_is_%03d_loop", is_count);
        emitf(".L_is_%03d_true:", is_count);
        emitf("  inc %s", value_holder__register_name(result_value_holder));
        emitf(".L_is_%03d_end:", is_count);
        value_holder__release_register(&is_expression_value_holder);
        return;
    }
    case EXPRESSION__LITERAL: {
        emit_load_literal(context, expression->literal_data.value, result_value_holder);
        return;
    }
    case EXPRESSION__MEMBER: {
        Value_Holder member_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression_address(context, expression, &member_value_holder);
        Type *value_type = member_value_holder.type->pointer_data.type;
        switch (value_type->kind) {
        case TYPE__BOOLEAN:
        case TYPE__INT:
        case TYPE__INT8:
        case TYPE__INT16:
        case TYPE__INT32:
        case TYPE__INT64:
        case TYPE__POINTER:
            value_holder__acquire_register(result_value_holder, value_type, context);
            emitf("  mov %s, [%s]", value_holder__register_name(result_value_holder), value_holder__register_name(&member_value_holder));
            value_holder__release_register(&member_value_holder);
            return;
        default:
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported value type: %s", SOURCE(expression->pointed_value_data.expression->location), context__type_name(context, value_type)->data);
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
        if (type->kind == TYPE__STRUCT && context__is_object_type(context, type)) {
            Statement *variable_statement = context__find_variable(context, context__type_name(context, type));
            emitf("  lea rax, %s_TYPE[rip]", variable_statement->variable_data.unique_name->data);
            emitf("  mov [%s], rax", value_holder__register_name(result_value_holder));
        }
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
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported value type: %s", SOURCE(expression->pointed_value_data.expression->location), context__type_name(context, value_type)->data);
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
        switch (variable_type->kind) {
        case TYPE__BOOLEAN:
        case TYPE__INT:
        case TYPE__INT8:
        case TYPE__INT16:
        case TYPE__INT32:
        case TYPE__INT64:
        case TYPE__POINTER:
            value_holder__acquire_register(result_value_holder, variable_type, context);
            emitf("  mov %s, [%s]", value_holder__register_name(result_value_holder), value_holder__register_name(&variable_address_value_holder));
            value_holder__release_register(&variable_address_value_holder);
            return;
        default:
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported type: %s", SOURCE(expression->variable_data.name->location), context__type_name(context, variable_type)->data);
        }
    }
    default:
        PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported expression kind: %s", SOURCE(expression->location), expression__get_kind_name(expression));
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
                PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Type inference is not supported yet.", SOURCE(statement->location));
            }
            context__resolve_type(context, variable_type);
            locals_size_min += context__compute_type_size(context, variable_type);
            if (locals_size_min > locals_size_max) {
                locals_size_max = locals_size_min;
            }
            break;
        }
        case STATEMENT__WHILE: {
            update_locals_size(context, locals_size_min, &locals_size_max, statement->while_data.block);
            break;
        }
        default:
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported statement kind: %s", SOURCE(statement->location), statement__get_kind_name(statement));
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

Statement *statement__create_variable(Source_Location *location, Token *name, Type *type, Expression *value, int is_external);

void emit_statement(Context *context, Statement *statement) {
    emitf("  .loc 1 %d %d", statement->location->line, statement->location->column);
    switch (statement->kind) {
    case STATEMENT__ASSIGNMENT: {
        Value_Holder destination_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression_address(context, statement->assignment_data.destination, &destination_value_holder);
        Type *destination_type = destination_value_holder.type->pointer_data.type;
        Value_Holder value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression(context, statement->assignment_data.value, &value_holder);
        Type *value_type = value_holder.type;
        if (!type__equals(destination_type, value_type) && destination_type->kind != TYPE__POINTER && value_type->kind != TYPE__NULL) {
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Destination type differs from value type. Expected %s but got %s instead.", SOURCE(statement->location), context__type_name(context, destination_type)->data, context__type_name(context, value_type)->data);
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
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported variable type: %s.", SOURCE(statement->location), context__type_name(context, destination_type)->data);
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
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "This break is not inside of a loop", SOURCE(statement->location));
        }
        emitf("  jmp .L_loop_%03d_end", loop->id);
        loop->has_exit = 1;
        return;
    }
    case STATEMENT__EXPRESSION: {
        Expression *expression = statement->expression_data.expression;
        Value_Holder value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression(context, expression, &value_holder);
        if (value_holder.kind != VALUE_HOLDER__NEW) {
            // TODO: WARNING(__FILE__, __LINE__, SOURCE_LOCATION "The result of this expression is ignored", SOURCE(statement->location));
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
                Statement *variable_statement = statement__create_variable(parameter->name->location, parameter->name, parameter->type, NULL, 0);
                context__add_variable(context, variable_statement);

                Value_Holder parameter_value_holder = { .kind = VALUE_HOLDER__NEW };
                value_holder__acquire_register(&parameter_value_holder, parameter->type, context);
                int register_id = parameter_value_holder.register_data.id;
                parameter_value_holder.register_data.id = parameter_register_ids[parameter_index];
                emitf("  mov [rbp-%d], %s", variable_statement->variable_data.locals_offset, value_holder__register_name(&parameter_value_holder));
                parameter_value_holder.register_data.id = register_id;
                value_holder__release_register(&parameter_value_holder);
            }

            int locals_size = compute_locals_size(context, statement->function_data.statements);
            if (function_parameters_size > 0) {
                Statement *variable_statement = list__last(context->variables);
                locals_size += variable_statement->variable_data.locals_offset;
            }
            if (locals_size > 0) {
                emitf("  sub rsp, %d", (locals_size + 15) & ~15);
            }

            for (List_Iterator iterator = list__create_iterator(statement->function_data.statements); list_iterator__has_next(&iterator);) {
                Statement *body_statement = list_iterator__next(&iterator);
                emit_statement(context, body_statement);
            }

            emitf(".L_%s__end:", function_unique_name->data);
            if (string__equals(function_unique_name, "main") && statement->function_data.return_type->kind == TYPE__NOTHING) {
                emits("  xor rax, rax");
            }
            emits("  mov rsp, rbp");
            emits("  pop rbp");
            emits("  ret");
        }
        return;
    }
    case STATEMENT__IF: {
        int label = counter__inc(context->counter);
        emitf(".L_if_%03d_cond:", label);
        Expression *condition_expression = statement->if_data.condition;
        Value_Holder condition_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression(context, condition_expression, &condition_value_holder);
        Type *condition_expression_type = condition_value_holder.type;
        if (condition_expression_type->kind != TYPE__BOOLEAN) {
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Not a boolean expression", SOURCE(condition_expression->location));
        }
        emitf("  dec %s", value_holder__register_name(&condition_value_holder));
        value_holder__release_register(&condition_value_holder);
        emitf("  jnz .L_if_%03d_false", label);
        emitf(".L_if_%03d_true:", label);
        emit_statement(context, statement->if_data.true_block);
        if (statement->if_data.false_block) {
            emitf("  jmp .L_if_%03d_end", label);
        }
        emitf(".L_if_%03d_false:", label);
        if (statement->if_data.false_block) {
            emit_statement(context, statement->if_data.false_block);
        }
        emitf(".L_if_%03d_end:", label);
        break;
    }
    case STATEMENT__LOOP: {
        int label = counter__inc(context->counter);
        emitf(".L_loop_%03d_start:", label);
        context->current_loop = loop__create(label, context->current_loop);
        emit_statement(context, statement->loop_data.block);
        if (!context->current_loop->has_exit) {
            WARNING(__FILE__, __LINE__, SOURCE_LOCATION "Infinite loop detected.", SOURCE(statement->location));
        }
        context->current_loop = context->current_loop->parent;
        emitf("  jmp .L_loop_%03d_start", label);
        emitf(".L_loop_%03d_end:", label);
        break;
    }
    case STATEMENT__RETURN: {
        Statement *function = context->current_function;
        if (function == NULL) {
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Found return statement outside of a function.", SOURCE(statement->location));
        }
        Type *function_return_type = function->function_data.return_type;
        if (statement->return_data.expression != NULL) {
            Expression *return_expression = statement->return_data.expression;
            Value_Holder value_holder = { .kind = VALUE_HOLDER__NEW };
            emit_expression(context, return_expression, &value_holder);
            Type *return_expression_type = value_holder.type;
            if (!type__equals(function_return_type, return_expression_type) && function_return_type->kind != TYPE__POINTER && return_expression_type->kind != TYPE__NULL) {
                PANIC(__FILE__, __LINE__, SOURCE_LOCATION "The return expression must be of type %s, got %s instead.", SOURCE(return_expression->location), context__type_name(context, function_return_type)->data, context__type_name(context, return_expression_type)->data);
            }
            switch (return_expression_type->kind) {
            case TYPE__BOOLEAN:
            case TYPE__INT8: {
                emitf("  mov al, %s", value_holder__register_name(&value_holder));
                break;
            }
            case TYPE__INT16: {
                emitf("  mov ax, %s", value_holder__register_name(&value_holder));
                break;
            }
            case TYPE__INT32: {
                emitf("  mov eax, %s", value_holder__register_name(&value_holder));
                break;
            }
            case TYPE__INT:
            case TYPE__INT64:
            case TYPE__NULL:
            case TYPE__POINTER: {
                emitf("  mov rax, %s", value_holder__register_name(&value_holder));
                break;
            }
            default:
                PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported return type: %s", SOURCE(return_expression->location), context__type_name(context, return_expression_type)->data);
            }
            value_holder__release_register(&value_holder);
        } else if (function_return_type->kind != TYPE__NOTHING) {
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Expected return expression", SOURCE(statement->location));
        }
        if (context->current_loop) {
            context->current_loop->has_exit = 1;
        }
        emitf("  jmp .L_%s__end", function->function_data.unique_name->data);
        return;
    }
    case STATEMENT__STRUCT: {
        Type *struct_type = context__find_type(context, statement->struct_data.name->lexeme);
        if (context__is_object_type(context, struct_type)) {
            Statement *variable_statement = context__find_variable(context, context__type_name(context, struct_type));
            emits("  .section .rodata");
            emits("  .align 8");
            emitf("%s: .quad %s_TYPE", variable_statement->variable_data.unique_name->data, variable_statement->variable_data.unique_name->data);
            emitf("%s_TYPE:", variable_statement->variable_data.unique_name->data);
            emitf("  .quad %d", statement->struct_data.object_type_id);
            Type *struct_base_type = struct_type->struct_data.statement->struct_data.base_type;
            if (struct_base_type != NULL) {
                Statement *variable_statement = context__find_variable(context, context__type_name(context, struct_base_type));
                emitf("  .quad %s_TYPE", variable_statement->variable_data.unique_name->data);
            } else {
                emits("  .quad 0");
            }            
        }
        return;
    }
    case STATEMENT__VARIABLE: {
        Token *variable_name = statement->variable_data.name;
        if (statement->variable_data.is_external) {
            if (!statement->variable_data.is_global) {
                PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Local variables cannot be external.", SOURCE(statement->location));
            }
            Type *variable_type = statement->variable_data.type;
            if (variable_type == NULL) {
                PANIC(__FILE__, __LINE__, SOURCE_LOCATION "External variables must have an explicit type.", SOURCE(statement->location));
            }
        } else {
            Type *variable_type = statement->variable_data.type;
            if (variable_type == NULL) {
                PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Type inference is not supported yet", SOURCE(statement->location));
            }
            if (statement->variable_data.is_global) {
                emits("  .bss");
                switch (variable_type->kind) {
                case TYPE__ARRAY: {
                    int variable_size = context__compute_type_size(context, variable_type);
                    if (variable_size == 0) {
                        PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Missing array size", SOURCE(variable_type->location));
                    }
                    emitf("%s: .zero %d", statement->variable_data.unique_name->data, variable_size);
                    break;
                }
                case TYPE__BOOLEAN:
                case TYPE__INT8:
                    emitf("%s: .byte 0", statement->variable_data.unique_name->data);
                    break;
                case TYPE__INT:
                case TYPE__POINTER:
                    emitf("%s: .quad 0", statement->variable_data.unique_name->data);
                    break;
                default:
                    PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported variable type: %s", SOURCE(statement->location), type__get_kind_name(variable_type));
                }
            } else {
                Expression *variable_value = statement->variable_data.value;
                if (variable_value) {
                    Value_Holder variable_value_holder = { .kind = VALUE_HOLDER__NEW };
                    emit_expression(context, variable_value, &variable_value_holder);
                    Type *variable_value_type = variable_value_holder.type;
                    context__add_variable(context, statement);
                    static Expression *assignment_destination = NULL;
                    if (assignment_destination == NULL) {
                        assignment_destination = expression__create_variable(variable_name);
                    } else {
                        assignment_destination->variable_data.name = variable_name;
                    }
                    Value_Holder variable_address_holder = { .kind = VALUE_HOLDER__NEW };
                    emit_expression_address(context, assignment_destination, &variable_address_holder);
                    Type *variable_type = variable_address_holder.type->pointer_data.type;
                    if (!type__equals(variable_type, variable_value_type) && variable_type->kind != TYPE__POINTER && variable_value_type->kind != TYPE__NULL) {
                        PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Destination type differs from value type. Expected %s but got %s instead.", SOURCE(statement->location), context__type_name(context, variable_type)->data, context__type_name(context, variable_value_type)->data);
                    }
                    switch (variable_type->kind) {
                    case TYPE__BOOLEAN:
                    case TYPE__INT:
                    case TYPE__INT8:
                    case TYPE__INT16:
                    case TYPE__INT32:
                    case TYPE__INT64:
                    case TYPE__POINTER:
                        emitf("  mov [%s], %s", value_holder__register_name(&variable_address_holder), value_holder__register_name(&variable_value_holder));
                        break;
                    default:
                        PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported variable type: %s.", SOURCE(statement->location), context__type_name(context, variable_type)->data);
                    }
                    value_holder__release_register(&variable_value_holder);
                    value_holder__release_register(&variable_address_holder);
                } else {
                    context__add_variable(context, statement);
                }
            }
        }
        return;
    }
    case STATEMENT__WHILE: {
        int label = counter__inc(context->counter);
        emitf(".L_while_%03d_start:", label);
        context->current_loop = loop__create(label, context->current_loop);
        Expression *condition_expression = statement->while_data.condition;
        Value_Holder condition_value_holder = { .kind = VALUE_HOLDER__NEW };
        emit_expression(context, condition_expression, &condition_value_holder);
        Type *condition_expression_type = condition_value_holder.type;
        if (condition_expression_type->kind != TYPE__BOOLEAN) {
            PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Not a boolean expression", SOURCE(condition_expression->location));
        }
        emitf("  dec %s", value_holder__register_name(&condition_value_holder));
        value_holder__release_register(&condition_value_holder);
        emitf("  jnz .L_while_%03d_end", label);
        emit_statement(context, statement->while_data.block);
        context->current_loop = context->current_loop->parent;
        emitf("  jmp .L_while_%03d_start", label);
        emitf(".L_loop_%03d_end:", label);
        emitf(".L_while_%03d_end:", label);
        break;
    }
    default:
        PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported statement kind: %s", SOURCE(statement->location), statement__get_kind_name(statement));
    }
}

void generate(char *file, Compilation_Unit *compilation_unit) {
    Context *context = context__create(fopen(file, "w"), compilation_unit->named_functions, compilation_unit->named_types);

    emitf("  .file 1 \"%s\"", compilation_unit->source->file_name);
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
            Type *struct_base_type = statement->struct_data.base_type;
            if (struct_base_type != NULL) {
                context__resolve_type(context, struct_base_type);
                if (struct_base_type->kind != TYPE__STRUCT) {
                    PANIC(__FILE__, __LINE__, "'%s' is not a struct type.", context__type_name(context, struct_base_type)->data);
                }
            }
            if (statement->struct_data.members) {
                for (List_Iterator members = list__create_iterator(statement->struct_data.members); list_iterator__has_next(&members);) {
                    Member *member = list_iterator__next(&members);
                    context__resolve_type(context, member->type);
                }
            }
            if (context__is_object_type(context, context__find_type(context, statement->struct_data.name->lexeme))) {
                statement->struct_data.object_type_id = counter__inc(context->counter);
                Token *struct_name = statement->struct_data.name;
                Statement *variable_statement = statement__create_variable(struct_name->location, struct_name, type__create_pointer(struct_name->location, context__get_type_type(context)), NULL, 0);
                context__add_variable(context, variable_statement);
            }
            break;
        }
        case STATEMENT__VARIABLE:
            context__resolve_type(context, statement->variable_data.type);
            context__add_variable(context, statement);
            if (statement->variable_data.is_external) {
                statement->variable_data.unique_name = statement->variable_data.name->lexeme;
            }
            break;
        }
    }

    for (List_Iterator iterator = list__create_iterator(compilation_unit->statements); list_iterator__has_next(&iterator);) {
        Statement *statement = list_iterator__next(&iterator);
        emits("");
        emit_statement(context, statement);

        for (int id = 0; id < REGISTERS_COUNT; id++) {
            if (registers[id] != NULL) {
                PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unrelease register found: %s", SOURCE(statement->location), value_holder__register_name(registers[id]));
            }
        }
    }

    for (int index = 0; index < list__size(context->string_constants); index++) {
        Token *string_constant = list__get(context->string_constants, index);
        emits("");
        emits("  .section .rodata");
        emits("  .align 8");
        emitf("L%03d_STRING_PTR: .quad L%03d_STRING", index, index);
        emitf("L%03d_STRING:", index);
        emitf("  .quad L%03d_STRING_DATA", index);
        emitf("  .quad %d", string_constant->string_data.value->length + 1);
        emitf("  .quad %d", string_constant->string_data.value->length);
        emitf("L%03d_STRING_DATA: .string %s", index, string_constant->lexeme->data);
    }

    fclose(context->file);
}
