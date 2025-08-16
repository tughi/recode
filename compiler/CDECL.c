#include "CDECL.h"
#include "File.h"

typedef struct CDECL {
    String *left;
    String *right;
    String *type;
} CDECL;

CDECL *CDECL__create() {
    CDECL *cdecl = malloc(sizeof(CDECL));
    cdecl->type = NULL;
    cdecl->left = NULL;
    cdecl->right = NULL;
    return cdecl;
}

void declare(CDECL *cdecl, Checked_Type *symbol_type);

void String__append_cdecl(String *self, CDECL_Name *name, Checked_Type *type) {
    Writer *writer = String__create_writer(self);
    pWriter__write__cdecl(writer, name, type);
    pWriter__destroy(writer);
}

void pWriter__write__cdecl(Writer *writer, CDECL_Name *name, Checked_Type *type) {
    CDECL cdecl = {NULL, NULL, NULL};
    declare(&cdecl, type);
    pWriter__write__string(writer, cdecl.type);
    String__delete(cdecl.type);
    if (cdecl.left != NULL || name != NULL) {
        pWriter__write__char(writer, ' ');
    }
    if (cdecl.left != NULL) {
        pWriter__write__string(writer, cdecl.left);
        String__delete(cdecl.left);
    }
    if (name != NULL) {
        name->write(name, writer);
    }
    if (cdecl.right != NULL) {
        pWriter__write__string(writer, cdecl.right);
        String__delete(cdecl.right);
    }
}

void declare_array(CDECL *cdecl, Checked_Array_Type *array_type) {
    todo("Declare checked array");
}

void declare_procedure(CDECL *cdecl, Checked_Procedure_Type *procedure_type) {
    CDECL return_cdecl = {NULL, NULL, NULL};
    declare(&return_cdecl, procedure_type->return_type);
    cdecl->type = return_cdecl.type;
    cdecl->left = return_cdecl.left;
    cdecl->right = String__create();
    String__append_char(cdecl->right, '(');
    Checked_Procedure_Parameter *parameter = procedure_type->first_parameter;
    while (parameter != NULL) {
        CDECL_Local_Name parameter_name = CDECL_Local_Name__create(parameter->name);
        String__append_cdecl(cdecl->right, (CDECL_Name *)&parameter_name, parameter->type);
        parameter = parameter->next_parameter;
        if (parameter != NULL) {
            String__append_cstring(cdecl->right, ", ");
        }
    }
    String__append_char(cdecl->right, ')');
    if (return_cdecl.right != NULL) {
        String__append_string(cdecl->right, return_cdecl.right);
        String__delete(return_cdecl.right);
    }
}

void declare_procedure_pointer(CDECL *cdecl, Checked_Procedure_Pointer_Type *procedure_pointer_type) {
    CDECL procedure_cdecl = {NULL, NULL, NULL};
    declare_procedure(&procedure_cdecl, procedure_pointer_type->procedure_type);
    cdecl->type = procedure_cdecl.type;
    cdecl->left = String__create_from("(*");
    if (procedure_cdecl.left != NULL) {
        panic();
    }
    cdecl->right = String__create_from(")");
    String__append_string(cdecl->right, procedure_cdecl.right);
    String__delete(procedure_cdecl.right);
}

void declare_multi_pointer(CDECL *cdecl, Checked_Multi_Pointer_Type *multi_pointer_type) {
    CDECL type_cdecl = {NULL, NULL, NULL};
    declare(&type_cdecl, multi_pointer_type->item_type);
    cdecl->type = type_cdecl.type;
    cdecl->left = String__create();
    if (type_cdecl.left != NULL) {
        String__append_string(cdecl->left, type_cdecl.left);
        String__delete(type_cdecl.left);
    }
    bool needs_parentheses = multi_pointer_type->item_type->kind == CHECKED_TYPE_KIND__ARRAY || multi_pointer_type->item_type->kind == CHECKED_TYPE_KIND__PROCEDURE;
    if (needs_parentheses) {
        String__append_char(cdecl->left, '(');
    }
    String__append_char(cdecl->left, '*');
    cdecl->right = String__create();
    if (needs_parentheses) {
        String__append_char(cdecl->right, ')');
    }
    if (type_cdecl.right != NULL) {
        String__append_string(cdecl->right, type_cdecl.right);
        String__delete(type_cdecl.right);
    }
}

void declare_pointer(CDECL *cdecl, Checked_Pointer_Type *pointer_type) {
    CDECL type_cdecl = {NULL, NULL, NULL};
    declare(&type_cdecl, pointer_type->other_type);
    cdecl->type = type_cdecl.type;
    cdecl->left = String__create();
    if (type_cdecl.left != NULL) {
        String__append_string(cdecl->left, type_cdecl.left);
        String__delete(type_cdecl.left);
    }
    bool needs_parentheses = pointer_type->other_type->kind == CHECKED_TYPE_KIND__ARRAY || pointer_type->other_type->kind == CHECKED_TYPE_KIND__PROCEDURE;
    if (needs_parentheses) {
        String__append_char(cdecl->left, '(');
    }
    String__append_char(cdecl->left, '*');
    cdecl->right = String__create();
    if (needs_parentheses) {
        String__append_char(cdecl->right, ')');
    }
    if (type_cdecl.right != NULL) {
        String__append_string(cdecl->right, type_cdecl.right);
        String__delete(type_cdecl.right);
    }
}

void declare(CDECL *cdecl, Checked_Type *symbol_type) {
    switch (symbol_type->kind) {
    case CHECKED_TYPE_KIND__BOOL:
        cdecl->type = String__create_from("bool");
        break;
    case CHECKED_TYPE_KIND__I16:
        cdecl->type = String__create_from("int16_t");
        break;
    case CHECKED_TYPE_KIND__I32:
        cdecl->type = String__create_from("int32_t");
        break;
    case CHECKED_TYPE_KIND__I64:
        cdecl->type = String__create_from("int64_t");
        break;
    case CHECKED_TYPE_KIND__I8:
        cdecl->type = String__create_from("int8_t");
        break;
    case CHECKED_TYPE_KIND__ISIZE:
        cdecl->type = String__create_from("intmax_t");
        break;
    case CHECKED_TYPE_KIND__U16:
        cdecl->type = String__create_from("uint16_t");
        break;
    case CHECKED_TYPE_KIND__U32:
        cdecl->type = String__create_from("uint32_t");
        break;
    case CHECKED_TYPE_KIND__U64:
        cdecl->type = String__create_from("uint64_t");
        break;
    case CHECKED_TYPE_KIND__U8:
        cdecl->type = String__create_from("uint8_t");
        break;
    case CHECKED_TYPE_KIND__USIZE:
        cdecl->type = String__create_from("uintmax_t");
        break;
    case CHECKED_TYPE_KIND__ANY:
    case CHECKED_TYPE_KIND__NOTHING:
        cdecl->type = String__create_from("void");
        break;
    case CHECKED_TYPE_KIND__ARRAY:
        declare_array(cdecl, (Checked_Array_Type *)symbol_type);
        break;
    case CHECKED_TYPE_KIND__PROCEDURE:
        declare_procedure(cdecl, (Checked_Procedure_Type *)symbol_type);
        break;
    case CHECKED_TYPE_KIND__PROCEDURE_POINTER:
        declare_procedure_pointer(cdecl, (Checked_Procedure_Pointer_Type *)symbol_type);
        break;
    case CHECKED_TYPE_KIND__STR:
        cdecl->type = String__create_from("struct String");
        break;
    case CHECKED_TYPE_KIND__EXTERNAL:
    case CHECKED_TYPE_KIND__STRUCT:
    case CHECKED_TYPE_KIND__RESULT:
    case CHECKED_TYPE_KIND__TRAIT:
    case CHECKED_TYPE_KIND__VARIANT: {
        Checked_Named_Type *named_type = (Checked_Named_Type *)symbol_type;
        cdecl->type = String__create_from("struct ");
        if (named_type->module != NULL) {
            String__append_string(cdecl->type, named_type->module->name);
            String__append_char(cdecl->type, '_');
        }
        if (named_type->generic_type != NULL) {
            String__append_string(cdecl->type, named_type->generic_type->super.name);
            Checked_Type_Argument *type_argument = named_type->first_type_argument;
            while (type_argument != NULL) {
                String__append_cstring(cdecl->type, "__");
                String__append_mangled_type_name(cdecl->type, type_argument->type);
                type_argument = type_argument->next_type_argument;
            }
        } else {
            String__append_string(cdecl->type, named_type->name);
        }
        break;
    }
    case CHECKED_TYPE_KIND__MULTI_POINTER:
        declare_multi_pointer(cdecl, (Checked_Multi_Pointer_Type *)symbol_type);
        break;
    case CHECKED_TYPE_KIND__POINTER:
        declare_pointer(cdecl, (Checked_Pointer_Type *)symbol_type);
        break;
    default:
        todo("Handle unexpected Checked_Type_Kind");
    }
}

void CDECL_Local_Name__write(CDECL_Local_Name *self, Writer *writer) {
    pWriter__write__string(writer, self->name);
}

CDECL_Local_Name CDECL_Local_Name__create(String *name) {
    CDECL_Local_Name local_name;
    local_name.super.write = (void (*)(CDECL_Name *, Writer *))CDECL_Local_Name__write;
    local_name.name = name;
    return local_name;
}

void CDECL_Procedure_Name__write(CDECL_Procedure_Name *self, Writer *writer) {
    if (self->procedure_symbol->external_name != NULL) {
        pWriter__write__string(writer, self->procedure_symbol->external_name);
        return;
    }
    if (self->procedure_symbol->super.is_global && self->procedure_symbol->checked_block_statement != NULL && self->procedure_symbol->receiver_type == NULL) {
        pWriter__write__string(writer, self->procedure_symbol->super.module->name);
        pWriter__write__cstring(writer, "__");
    }
    pWriter__write__string(writer, self->procedure_symbol->super.name);
}

CDECL_Procedure_Name CDECL_Procedure_Name__create(Checked_Procedure_Symbol *procedure_symbol) {
    CDECL_Procedure_Name procedure_name;
    procedure_name.super.write = (void (*)(CDECL_Name *, Writer *))CDECL_Procedure_Name__write;
    procedure_name.procedure_symbol = procedure_symbol;
    return procedure_name;
}

void CDECL_Variable_Name__write(CDECL_Variable_Name *self, Writer *writer) {
    if (self->variable_symbol->statement->is_external) {
        if (self->variable_symbol->external_name != NULL) {
            pWriter__write__string(writer, self->variable_symbol->external_name);
            return;
        }
    } else if (self->variable_symbol->super.is_global) {
        pWriter__write__string(writer, self->variable_symbol->super.module->name);
        pWriter__write__cstring(writer, "__");
    }
    pWriter__write__string(writer, self->variable_symbol->super.name);
}

CDECL_Variable_Name CDECL_Variable_Name__create(Checked_Variable_Symbol *variable_symbol) {
    CDECL_Variable_Name variable_name;
    variable_name.super.write = (void (*)(CDECL_Name *, Writer *))CDECL_Variable_Name__write;
    variable_name.variable_symbol = variable_symbol;
    return variable_name;
}
