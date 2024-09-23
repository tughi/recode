/* Copyright (C) 2024 Stefan Selariu */

#include "Checked_Source.h"

Checked_Type *Checked_Type__create_kind(Checked_Type_Kind kind, size_t kind_size, Source_Location *location) {
    Checked_Type *type = (Checked_Type *)malloc(kind_size);
    type->kind = kind;
    type->location = location;
    type->next_type = NULL;
    return type;
}

void Checked_Type__expect_same_type(Checked_Type *self, Checked_Type *other_type, Source_Location *location) {
    if (self->kind == CHECKED_TYPE_KIND__POINTER && other_type->kind == CHECKED_TYPE_KIND__NULL) {
        return;
    }
    if (!Checked_Type__equals(self, other_type)) {
        String *message = String__create_from("Unexpected type. Got \"");
        String__append_checked_type(message, other_type);
        String__append_cstring(message, "\" instead of \"");
        String__append_checked_type(message, self);
        String__append_char(message, '"');
        Source_Location__error(location, message);
        panic();
    }
}

bool Checked_Type__is_scalar_type(Checked_Type *self) {
    if (self->kind == CHECKED_TYPE_KIND__I16) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__I32) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__I64) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__I8) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__ISIZE) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__U16) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__U32) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__U64) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__U8) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__ENUM) {
        return true;
    }
    return false;
}

void Checked_Type__expect_scalar_type(Checked_Type *self, Source_Location *location) {
    if (!Checked_Type__is_scalar_type(self)) {
        String *message = String__create_from("Type \"");
        String__append_checked_type(message, self);
        String__append_cstring(message, "\" is not a scalar type");
        Source_Location__error(location, message);
        panic();
    }
}

Checked_Named_Type *Checked_Named_Type__create_kind(Checked_Type_Kind kind, size_t kind_size, Source_Location *location, String *name) {
    Checked_Named_Type *type = (Checked_Named_Type *)Checked_Type__create_kind(kind, kind_size, location);
    type->name = name;
    return type;
}

Checked_Enum_Member *Checked_Enum_Member__create(Source_Location *location, String *name) {
    Checked_Enum_Member *member = (Checked_Enum_Member *)malloc(sizeof(Checked_Enum_Member));
    member->location = location;
    member->name = name;
    member->next_member = NULL;
    return member;
}

Checked_Enum_Type *Checked_Enum_Type__create(Source_Location *location, String *name) {
    Checked_Enum_Type *type = (Checked_Enum_Type *)Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__ENUM, sizeof(Checked_Enum_Type), location, name);
    type->first_member = NULL;
    return type;
}

Checked_Enum_Member *Checked_Enum_Type__find_member(Checked_Enum_Type *self, String *name) {
    Checked_Enum_Member *member = self->first_member;
    while (member != NULL) {
        if (String__equals_string(name, member->name)) {
            break;
        }
        member = member->next_member;
    }
    return member;
}

Checked_External_Type *Checked_External_Type__create(Source_Location *location, String *name) {
    Checked_External_Type *type = (Checked_External_Type *)Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__EXTERNAL, sizeof(Checked_External_Type), location, name);
    return type;
}

Checked_Function_Parameter *Checked_Function_Parameter__create(Source_Location *location, String *name, Checked_Type *type) {
    Checked_Function_Parameter *parameter = (Checked_Function_Parameter *)malloc(sizeof(Checked_Function_Parameter));
    parameter->location = location;
    parameter->name = name;
    parameter->type = type;
    parameter->next_parameter = NULL;
    return parameter;
}

Checked_Function_Type *Checked_Function_Type__create(Source_Location *location, Checked_Function_Parameter *first_parameter, Checked_Type *return_type) {
    Checked_Function_Type *type = (Checked_Function_Type *)Checked_Type__create_kind(CHECKED_TYPE_KIND__FUNCTION, sizeof(Checked_Function_Type), location);
    type->first_parameter = first_parameter;
    type->return_type = return_type;
    return type;
}

bool Checked_Function_Type__equals(Checked_Function_Type *self, Checked_Type *other_type) {
    if (other_type->kind != self->super.kind) {
        return false;
    }
    Checked_Function_Type *function_type = (Checked_Function_Type *)other_type;
    if (!Checked_Type__equals(self->return_type, function_type->return_type)) {
        return false;
    }
    Checked_Function_Parameter *self_parameter = self->first_parameter;
    Checked_Function_Parameter *function_parameter = function_type->first_parameter;
    while (self_parameter != NULL && function_parameter != NULL) {
        if (!Checked_Type__equals(self_parameter->type, function_parameter->type)) {
            return false;
        }
        self_parameter = self_parameter->next_parameter;
        function_parameter = function_parameter->next_parameter;
    }
    if (self_parameter != NULL || function_parameter != NULL) {
        return false;
    }
    return true;
}

Checked_Pointer_Type *Checked_Pointer_Type__create(Source_Location *location, Checked_Type *other_type) {
    Checked_Pointer_Type *type = (Checked_Pointer_Type *)Checked_Type__create_kind(CHECKED_TYPE_KIND__POINTER, sizeof(Checked_Pointer_Type), location);
    type->other_type = other_type;
    return type;
}

bool Checked_Pointer_Type__equals(Checked_Pointer_Type *self, Checked_Type *other_type) {
    if (other_type->kind != self->super.kind) {
        return false;
    }
    return Checked_Type__equals(self->other_type, ((Checked_Pointer_Type *)other_type)->other_type);
}

Checked_Struct_Member *Checked_Struct_Member__create(Source_Location *location, String *name, Checked_Type *type) {
    Checked_Struct_Member *member = (Checked_Struct_Member *)malloc(sizeof(Checked_Struct_Member));
    member->location = location;
    member->name = name;
    member->type = type;
    member->next_member = NULL;
    return member;
}

Checked_Struct_Type *Checked_Struct_Type__create(Source_Location *location, String *name) {
    Checked_Struct_Type *type = (Checked_Struct_Type *)Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__STRUCT, sizeof(Checked_Struct_Type), location, name);
    type->first_member = NULL;
    return type;
}

Checked_Struct_Member *Checked_Struct_Type__find_member(Checked_Struct_Type *self, String *name) {
    Checked_Struct_Member *member = self->first_member;
    while (member != NULL) {
        if (String__equals_string(name, member->name)) {
            break;
        }
        member = member->next_member;
    }
    return member;
}

bool Checked_Struct_Type__equals(Checked_Struct_Type *self, Checked_Type *other_type) {
    if (self->super.super.kind != other_type->kind) {
        return false;
    }
    return String__equals_string(self->super.name, ((Checked_Struct_Type *)other_type)->super.name);
}

bool Checked_Type__equals(Checked_Type *self, Checked_Type *other_type) {
    if (self == other_type) {
        return true;
    }
    if (self->kind != other_type->kind) {
        return false;
    }
    if (self->kind == CHECKED_TYPE_KIND__FUNCTION) {
        return Checked_Function_Type__equals((Checked_Function_Type *)self, other_type);
    }
    if (self->kind == CHECKED_TYPE_KIND__POINTER) {
        return Checked_Pointer_Type__equals((Checked_Pointer_Type *)self, other_type);
    }
    if (self->kind == CHECKED_TYPE_KIND__STRUCT) {
        return Checked_Struct_Type__equals((Checked_Struct_Type *)self, other_type);
    }
    error(String__create_from("TODO: Compare unsupported type"));
    panic();
}

String *String__append_checked_type(String *self, Checked_Type *type) {
    if (type->kind <= CHECKED_TYPE_KIND__NULL) {
        Checked_Named_Type *named_type = (Checked_Named_Type *)type;
        String__append_string(self, named_type->name);
    } else if (type->kind == CHECKED_TYPE_KIND__STRUCT) {
        Checked_Struct_Type *struct_type = (Checked_Struct_Type *)type;
        String__append_cstring(self, "struct ");
        String__append_string(self, struct_type->super.name);
    } else if (type->kind == CHECKED_TYPE_KIND__FUNCTION) {
        Checked_Function_Type *function_type = (Checked_Function_Type *)type;
        String__append_checked_type(self, function_type->return_type);
        String__append_char(self, ' ');
        String__append_char(self, '(');
        Checked_Function_Parameter *function_parameter = function_type->first_parameter;
        while (function_parameter != NULL) {
            String__append_checked_type(self, function_parameter->type);
            String__append_char(self, ' ');
            String__append_string(self, function_parameter->name);
            function_parameter = function_parameter->next_parameter;
            if (function_parameter != NULL) {
                String__append_cstring(self, ", ");
            }
        }
        String__append_char(self, ')');
    } else if (type->kind == CHECKED_TYPE_KIND__ENUM) {
        Checked_Enum_Type *enum_type = (Checked_Enum_Type *)type;
        String__append_cstring(self, "enum ");
        String__append_string(self, enum_type->super.name);
    } else if (type->kind == CHECKED_TYPE_KIND__POINTER) {
        Checked_Pointer_Type *pointer_type = (Checked_Pointer_Type *)type;
        String__append_checked_type(self, pointer_type->other_type);
        String__append_char(self, '*');
    } else {
        Source_Location__error(type->location, String__create_from("Unsupported type"));
        panic();
    }
    return self;
}

void pWriter__write__checked_function_parameter(Writer *writer, Checked_Function_Parameter *parameter) {
    if (parameter->type->kind == CHECKED_TYPE_KIND__POINTER && ((Checked_Pointer_Type *)parameter->type)->other_type->kind == CHECKED_TYPE_KIND__FUNCTION) {
        Checked_Function_Type *function_type = (Checked_Function_Type *)((Checked_Pointer_Type *)parameter->type)->other_type;
        pWriter__write__checked_type(writer, function_type->return_type);
        pWriter__write__cstring(writer, " (*");
        pWriter__write__string(writer, parameter->name);
        pWriter__write__cstring(writer, ")(");
        Checked_Function_Parameter *function_parameter = function_type->first_parameter;
        while (function_parameter != NULL) {
            pWriter__write__checked_function_parameter(writer, function_parameter);
            function_parameter = function_parameter->next_parameter;
            if (function_parameter != NULL) {
                pWriter__write__cstring(writer, ", ");
            }
        }
        pWriter__write__char(writer, ')');
    } else {
        pWriter__write__checked_type(writer, parameter->type);
        pWriter__write__char(writer, ' ');
        pWriter__write__string(writer, parameter->name);
    }
}

void pWriter__write__checked_type(Writer *self, Checked_Type *type) {
    if (type == NULL) {
        pWriter__write__cstring(self, "null");
    } else if (type->kind <= CHECKED_TYPE_KIND__NULL) {
        Checked_Named_Type *named_type = (Checked_Named_Type *)type;
        pWriter__write__string(self, named_type->name);
    } else if (type->kind == CHECKED_TYPE_KIND__STRUCT) {
        Checked_Struct_Type *struct_type = (Checked_Struct_Type *)type;
        pWriter__write__cstring(self, "struct ");
        pWriter__write__string(self, struct_type->super.name);
    } else if (type->kind == CHECKED_TYPE_KIND__FUNCTION) {
        Checked_Function_Type *function_type = (Checked_Function_Type *)type;
        pWriter__write__checked_type(self, function_type->return_type);
        pWriter__write__char(self, ' ');
        pWriter__write__char(self, '(');
        Checked_Function_Parameter *function_parameter = function_type->first_parameter;
        while (function_parameter != NULL) {
            pWriter__write__checked_function_parameter(self, function_parameter);
            function_parameter = function_parameter->next_parameter;
            if (function_parameter != NULL) {
                pWriter__write__cstring(self, ", ");
            }
        }
        pWriter__write__char(self, ')');
    } else if (type->kind == CHECKED_TYPE_KIND__ENUM) {
        Checked_Enum_Type *enum_type = (Checked_Enum_Type *)type;
        pWriter__write__cstring(self, "enum ");
        pWriter__write__string(self, enum_type->super.name);
    } else if (type->kind == CHECKED_TYPE_KIND__POINTER) {
        Checked_Pointer_Type *pointer_type = (Checked_Pointer_Type *)type;
        pWriter__write__checked_type(self, pointer_type->other_type);
        if (pointer_type->other_type->kind != CHECKED_TYPE_KIND__POINTER) {
            pWriter__write__cstring(self, " *");
        } else {
            pWriter__write__char(self, '*');
        }
    } else {
        Source_Location__error(type->location, String__create_from("Unsupported type"));
        panic();
    }
}

Checked_Symbol *Checked_Symbol__create_kind(Checked_Symbol_Kind kind, size_t kind_size, Source_Location *location, String *name, Checked_Type *type) {
    Checked_Symbol *symbol = (Checked_Symbol *)malloc(kind_size);
    symbol->kind = kind;
    symbol->location = location;
    symbol->name = name;
    symbol->type = type;
    symbol->prev_symbol = NULL;
    symbol->next_symbol = NULL;
    return symbol;
}

Checked_Enum_Member_Symbol *Checked_Enum_Member_Symbol__create(Source_Location *location, String *name, Checked_Type *type) {
    return (Checked_Enum_Member_Symbol *)Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__ENUM_MEMBER, sizeof(Checked_Enum_Member_Symbol), location, name, type);
}

Checked_Function_Symbol *Checked_Function_Symbol__create(Source_Location *location, String *name, Checked_Function_Type *function_type) {
    Checked_Function_Symbol *symbol = (Checked_Function_Symbol *)Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__FUNCTION, sizeof(Checked_Function_Symbol), location, name, (Checked_Type *)Checked_Pointer_Type__create(function_type->super.location, (Checked_Type *)function_type));
    symbol->function_type = function_type;
    symbol->checked_statements = NULL;
    return symbol;
}

Checked_Function_Parameter_Symbol *Checked_Function_Parameter_Symbol__create(Source_Location *location, String *name, Checked_Type *type) {
    return (Checked_Function_Parameter_Symbol *)Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__FUNCTION_PARAMETER, sizeof(Checked_Function_Parameter_Symbol), location, name, type);
}

Checked_Type_Symbol *Checked_Type_Symbol__create(Source_Location *location, String *name, Checked_Named_Type *named_type) {
    Checked_Type_Symbol *symbol = (Checked_Type_Symbol *)Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__TYPE, sizeof(Checked_Type_Symbol), location, name, NULL);
    symbol->named_type = named_type;
    return symbol;
}

Checked_Variable_Symbol *Checked_Variable__create(Source_Location *location, String *name, Checked_Type *type) {
    return (Checked_Variable_Symbol *)Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__VARIABLE, sizeof(Checked_Variable_Symbol), location, name, type);
}

Checked_Symbols *Checked_Symbols__create(Checked_Symbols *parent) {
    Checked_Symbols *symbols = (Checked_Symbols *)malloc(sizeof(Checked_Symbols));
    symbols->parent = parent;
    symbols->first_symbol = NULL;
    symbols->last_symbol = NULL;
    return symbols;
}

Checked_Symbol *Checked_Symbols__find_sibling_symbol(Checked_Symbols *self, String *name) {
    Checked_Symbol *symbol = self->first_symbol;
    while (symbol != NULL) {
        if (String__equals_string(name, symbol->name)) {
            return symbol;
        }
        symbol = symbol->next_symbol;
    }
    return NULL;
}

void Checked_Symbols__append_symbol(Checked_Symbols *self, Checked_Symbol *symbol) {
    if (Checked_Symbols__find_sibling_symbol(self, symbol->name) != NULL) {
        error(String__create_from("TODO: Report symbol redeclaration"));
        panic();
    }

    if (self->last_symbol == NULL) {
        self->first_symbol = symbol;
    } else {
        self->last_symbol->next_symbol = symbol;
        symbol->prev_symbol = self->last_symbol;
    }
    self->last_symbol = symbol;
}

Checked_Symbol *Checked_Symbols__find_symbol(Checked_Symbols *self, String *name) {
    Checked_Symbol *symbol = self->last_symbol;
    while (symbol != NULL) {
        if (String__equals_string(name, symbol->name)) {
            return symbol;
        }
        symbol = symbol->prev_symbol;
    }
    if (self->parent != NULL) {
        return Checked_Symbols__find_symbol(self->parent, name);
    }
    return NULL;
}

Checked_Expression *Checked_Expression__create_kind(Checked_Expression_Kind kind, size_t kind_size, Source_Location *location, Checked_Type *type) {
    Checked_Expression *expression = (Checked_Expression *)malloc(kind_size);
    expression->kind = kind;
    expression->location = location;
    expression->type = type;
    return expression;
}

Checked_Binary_Expression *Checked_Binary_Expression__create_kind(Checked_Expression_Kind kind, Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    Checked_Binary_Expression *expression = (Checked_Binary_Expression *)Checked_Expression__create_kind(kind, sizeof(Checked_Binary_Expression), location, type);
    expression->left_expression = left_expression;
    expression->right_expression = right_expression;
    return expression;
}

Checked_Unary_Expression *Checked_Unary_Expression__create_kind(Checked_Expression_Kind kind, size_t kind_size, Source_Location *location, Checked_Type *type, Checked_Expression *other_expression) {
    Checked_Unary_Expression *expression = (Checked_Unary_Expression *)Checked_Expression__create_kind(kind, kind_size, location, type);
    expression->other_expression = other_expression;
    return expression;
}

Checked_Add_Expression *Checked_Add_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Add_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__ADD, location, type, left_expression, right_expression);
}

Checked_Address_Of_Expression *Checked_Address_Of_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *other_expression) {
    return (Checked_Address_Of_Expression *)Checked_Unary_Expression__create_kind(CHECKED_EXPRESSION_KIND__ADDRESS_OF, sizeof(Checked_Address_Of_Expression), location, type, other_expression);
}

Checked_Array_Access_Expression *Checked_Array_Access_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *array_expression, Checked_Expression *index_expression) {
    Checked_Array_Access_Expression *expression = (Checked_Array_Access_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__ARRAY_ACCESS, sizeof(Checked_Array_Access_Expression), location, type);
    expression->array_expression = array_expression;
    expression->index_expression = index_expression;
    return expression;
}

Checked_Bool_Expression *Checked_Bool_Expression__create(Source_Location *location, Checked_Type *type, bool value) {
    Checked_Bool_Expression *expression = (Checked_Bool_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__BOOL, sizeof(Checked_Bool_Expression), location, type);
    expression->value = value;
    return expression;
}

Checked_Call_Argument *Checked_Call_Argument__create(Checked_Expression *expression) {
    Checked_Call_Argument *argument = (Checked_Call_Argument *)malloc(sizeof(Checked_Call_Argument));
    argument->expression = expression;
    argument->next_argument = NULL;
    return argument;
}

Checked_Call_Expression *Checked_Call_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *callee_expression, Checked_Call_Argument *first_argument) {
    Checked_Call_Expression *expression = (Checked_Call_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__CALL, sizeof(Checked_Call_Expression), location, type);
    expression->callee_expression = callee_expression;
    expression->first_argument = first_argument;
    return expression;
}

Checked_Cast_Expression *Checked_Cast_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *other_expression) {
    Checked_Cast_Expression *expression = (Checked_Cast_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__CAST, sizeof(Checked_Cast_Expression), location, type);
    expression->other_expression = other_expression;
    return expression;
}

Checked_Character_Expression *Checked_Character_Expression__create(Source_Location *location, Checked_Type *type, char value) {
    Checked_Character_Expression *expression = (Checked_Character_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__CHARACTER, sizeof(Checked_Character_Expression), location, type);
    expression->value = value;
    return expression;
}

Checked_Dereference_Expression *Checked_Dereference_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *other_expression) {
    return (Checked_Dereference_Expression *)Checked_Unary_Expression__create_kind(CHECKED_EXPRESSION_KIND__DEREFERENCE, sizeof(Checked_Dereference_Expression), location, type, other_expression);
}

Checked_Divide_Expression *Checked_Divide_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Divide_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__DIVIDE, location, type, left_expression, right_expression);
}

Checked_Equals_Expression *Checked_Equals_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Equals_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__EQUALS, location, type, left_expression, right_expression);
}

Checked_Greater_Expression *Checked_Greater_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Greater_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__GREATER, location, type, left_expression, right_expression);
}

Checked_Greater_Or_Equals_Expression *Checked_Greater_Or_Equals_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Greater_Or_Equals_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__GREATER_OR_EQUALS, location, type, left_expression, right_expression);
}

Checked_Group_Expression *Checked_Group_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *other_expression) {
    Checked_Group_Expression *expression = (Checked_Group_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__GROUP, sizeof(Checked_Group_Expression), location, type);
    expression->other_expression = other_expression;
    return expression;
}

Checked_Integer_Expression *Checked_Integer_Expression__create(Source_Location *location, Checked_Type *type, uint64_t value) {
    Checked_Integer_Expression *expression = (Checked_Integer_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__INTEGER, sizeof(Checked_Integer_Expression), location, type);
    expression->value = value;
    return expression;
}

Checked_Less_Expression *Checked_Less_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Less_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__LESS, location, type, left_expression, right_expression);
}

Checked_Less_Or_Equals_Expression *Checked_Less_Or_Equals_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Less_Or_Equals_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__LESS_OR_EQUALS, location, type, left_expression, right_expression);
}

Checked_Logic_And_Expression *Checked_Logic_And_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Logic_And_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__LOGIC_AND, location, type, left_expression, right_expression);
}

Checked_Logic_Or_Expression *Checked_Logic_Or_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Logic_Or_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__LOGIC_OR, location, type, left_expression, right_expression);
}

Checked_Member_Access_Expression *Checked_Member_Access_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *object_expression, Checked_Struct_Member *member) {
    Checked_Member_Access_Expression *expression = (Checked_Member_Access_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__MEMBER_ACCESS, sizeof(Checked_Member_Access_Expression), location, type);
    expression->object_expression = object_expression;
    expression->member = member;
    return expression;
}

Checked_Minus_Expression *Checked_Minus_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *other_expression) {
    return (Checked_Minus_Expression *)Checked_Unary_Expression__create_kind(CHECKED_EXPRESSION_KIND__MINUS, sizeof(Checked_Minus_Expression), location, type, other_expression);
}

Checked_Modulo_Expression *Checked_Modulo_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Modulo_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__MODULO, location, type, left_expression, right_expression);
}

Checked_Multiply_Expression *Checked_Multiply_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Multiply_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__MULTIPLY, location, type, left_expression, right_expression);
}

Checked_Not_Expression *Checked_Not_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *other_expression) {
    return (Checked_Not_Expression *)Checked_Unary_Expression__create_kind(CHECKED_EXPRESSION_KIND__NOT, sizeof(Checked_Not_Expression), location, type, other_expression);
}

Checked_Not_Equals_Expression *Checked_Not_Equals_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Not_Equals_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__NOT_EQUALS, location, type, left_expression, right_expression);
}

Checked_Null_Expression *Checked_Null_Expression__create(Source_Location *location, Checked_Type *type) {
    return (Checked_Null_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__NULL, sizeof(Checked_Null_Expression), location, type);
}

Checked_Sizeof_Expression *Checked_Sizeof_Expression__create(Source_Location *location, Checked_Type *type, Checked_Type *sized_type) {
    Checked_Sizeof_Expression *expression = (Checked_Sizeof_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__SIZEOF, sizeof(Checked_Sizeof_Expression), location, type);
    expression->sized_type = sized_type;
    return expression;
}

Checked_String_Expression *Checked_String_Expression__create(Source_Location *location, Checked_Type *type, String *value) {
    Checked_String_Expression *expression = (Checked_String_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__STRING, sizeof(Checked_String_Expression), location, type);
    expression->value = value;
    return expression;
}

Checked_Substract_Expression *Checked_Substract_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Substract_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__SUBSTRACT, location, type, left_expression, right_expression);
}

Checked_Symbol_Expression *Checked_Symbol_Expression__create(Source_Location *location, Checked_Type *type, Checked_Symbol *symbol) {
    Checked_Symbol_Expression *expression = (Checked_Symbol_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__SYMBOL, sizeof(Checked_Symbol_Expression), location, type);
    expression->symbol = symbol;
    return expression;
}

Checked_Statement *Checked_Statement__create_kind(Checked_Statement_Kind kind, size_t kind_size, Source_Location *location) {
    Checked_Statement *statement = (Checked_Statement *)malloc(kind_size);
    statement->kind = kind;
    statement->location = location;
    statement->next_statement = NULL;
    return statement;
}

Checked_Assignment_Statement *Checked_Assignment_Statement__create(Source_Location *location, Checked_Expression *object_expression, Checked_Expression *value_expression) {
    Checked_Assignment_Statement *statement = (Checked_Assignment_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__ASSIGNMENT, sizeof(Checked_Assignment_Statement), location);
    statement->object_expression = object_expression;
    statement->value_expression = value_expression;
    return statement;
}

Checked_Block_Statement *Checked_Block_Statement__create(Source_Location *location, Checked_Statements *statements) {
    Checked_Block_Statement *statement = (Checked_Block_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__BLOCK, sizeof(Checked_Block_Statement), location);
    statement->statements = statements;
    return statement;
}

Checked_Break_Statement *Checked_Break_Statement__create(Source_Location *location) {
    return (Checked_Break_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__BREAK, sizeof(Checked_Break_Statement), location);
}

Checked_Expression_Statement *Checked_Expression_Statement__create(Source_Location *location, Checked_Expression *expression) {
    Checked_Expression_Statement *statement = (Checked_Expression_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__EXPRESSION, sizeof(Checked_Expression_Statement), location);
    statement->expression = expression;
    return statement;
}

Checked_If_Statement *Checked_If_Statement__create(Source_Location *location, Checked_Expression *condition_expression, Checked_Statement *true_statement, Checked_Statement *false_statement) {
    Checked_If_Statement *statement = (Checked_If_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__IF, sizeof(Checked_If_Statement), location);
    statement->condition_expression = condition_expression;
    statement->true_statement = true_statement;
    statement->false_statement = false_statement;
    return statement;
}

Checked_Loop_Statement *Checked_Loop_Statement__create(Source_Location *location, Checked_Statement *body_statement) {
    Checked_Loop_Statement *statement = (Checked_Loop_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__LOOP, sizeof(Checked_Loop_Statement), location);
    statement->body_statement = body_statement;
    return statement;
}

Checked_Return_Statement *Checked_Return_Statement__create(Source_Location *location, Checked_Expression *expression) {
    Checked_Return_Statement *statement = (Checked_Return_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__RETURN, sizeof(Checked_Return_Statement), location);
    statement->expression = expression;
    return statement;
}

Checked_Variable_Statement *Checked_Variable_Statement__create(Source_Location *location, Checked_Variable_Symbol *variable, Checked_Expression *expression, bool is_external) {
    Checked_Variable_Statement *statement = (Checked_Variable_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__VARIABLE, sizeof(Checked_Variable_Statement), location);
    statement->variable = variable;
    statement->expression = expression;
    statement->is_external = is_external;
    return statement;
}

Checked_While_Statement *Checked_While_Statement__create(Source_Location *location, Checked_Expression *condition_expression, Checked_Statement *body_statement) {
    Checked_While_Statement *statement = (Checked_While_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__WHILE, sizeof(Checked_While_Statement), location);
    statement->condition_expression = condition_expression;
    statement->body_statement = body_statement;
    return statement;
}

Checked_Statements *Checked_Statements__create() {
    Checked_Statements *statements = (Checked_Statements *)malloc(sizeof(Checked_Statements));
    statements->first_statement = NULL;
    statements->last_statement = NULL;
    return statements;
}

void Checked_Statements__append(Checked_Statements *self, Checked_Statement *statement) {
    if (self->first_statement == NULL) {
        self->first_statement = statement;
    } else {
        self->last_statement->next_statement = statement;
    }
    self->last_statement = statement;
}
