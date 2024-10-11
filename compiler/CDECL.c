/* Copyright (C) 2024 Stefan Selariu */

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

void String__append_cdecl(String *self, String *name, Checked_Type *type) {
    CDECL cdecl = {NULL, NULL, NULL};
    declare(&cdecl, type);
    String__append_string(self, cdecl.type);
    String__delete(cdecl.type);
    String__append_char(self, ' ');
    if (cdecl.left != NULL) {
        String__append_string(self, cdecl.left);
        String__delete(cdecl.left);
    }
    if (name != NULL) {
        String__append_string(self, name);
    }
    if (cdecl.right != NULL) {
        String__append_string(self, cdecl.right);
        String__delete(cdecl.right);
    }
}

void pWriter__write__cdecl(Writer *writer, String *name, Checked_Type *type) {
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
        pWriter__write__string(writer, name);
    }
    if (cdecl.right != NULL) {
        pWriter__write__string(writer, cdecl.right);
        String__delete(cdecl.right);
    }
}

void declare_array(CDECL *cdecl, Checked_Array_Type *array_type) {
    if (array_type->is_checked) {
        pWriter__begin_location_message(stderr_writer, array_type->super.location, WRITER_STYLE__TODO);
        pWriter__write__cstring(stderr_writer, "TODO: Add support for checked arrays");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    CDECL type_cdecl = {NULL, NULL, NULL};
    declare(&type_cdecl, array_type->item_type);
    cdecl->type = type_cdecl.type;
    cdecl->left = String__create();
    if (type_cdecl.left != NULL) {
        String__append_string(cdecl->left, type_cdecl.left);
        String__delete(type_cdecl.left);
    }
    if (array_type->item_type->kind == CHECKED_TYPE_KIND__ARRAY && ((Checked_Array_Type *)array_type->item_type)->is_checked || array_type->item_type->kind == CHECKED_TYPE_KIND__FUNCTION) {
        String__append_char(cdecl->left, '(');
    }
    String__append_char(cdecl->left, '*');
    cdecl->right = String__create();
    if (array_type->item_type->kind == CHECKED_TYPE_KIND__ARRAY && ((Checked_Array_Type *)array_type->item_type)->is_checked || array_type->item_type->kind == CHECKED_TYPE_KIND__FUNCTION) {
        String__append_char(cdecl->right, ')');
    }
    if (type_cdecl.right != NULL) {
        String__append_string(cdecl->right, type_cdecl.right);
        String__delete(type_cdecl.right);
    }
}

void declare_function(CDECL *cdecl, Checked_Function_Type *function_type) {
    CDECL return_cdecl = {NULL, NULL, NULL};
    declare(&return_cdecl, function_type->return_type);
    cdecl->type = return_cdecl.type;
    cdecl->left = return_cdecl.left;
    cdecl->right = String__create();
    String__append_char(cdecl->right, '(');
    Checked_Function_Parameter *parameter = function_type->first_parameter;
    while (parameter != NULL) {
        String__append_cdecl(cdecl->right, parameter->name, parameter->type);
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

void declare_function_pointer(CDECL *cdecl, Checked_Function_Pointer_Type *function_pointer_type) {
    CDECL function_cdecl = {NULL, NULL, NULL};
    declare_function(&function_cdecl, function_pointer_type->function_type);
    cdecl->type = function_cdecl.type;
    cdecl->left = String__create_from("(*");
    if (function_cdecl.left != NULL) {
        panic();
    }
    cdecl->right = String__create_from(")");
    String__append_string(cdecl->right, function_cdecl.right);
    String__delete(function_cdecl.right);
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
    if (pointer_type->other_type->kind == CHECKED_TYPE_KIND__ARRAY && ((Checked_Array_Type *)pointer_type->other_type)->is_checked || pointer_type->other_type->kind == CHECKED_TYPE_KIND__FUNCTION) {
        String__append_char(cdecl->left, '(');
    }
    String__append_char(cdecl->left, '*');
    cdecl->right = String__create();
    if (pointer_type->other_type->kind == CHECKED_TYPE_KIND__ARRAY && ((Checked_Array_Type *)pointer_type->other_type)->is_checked || pointer_type->other_type->kind == CHECKED_TYPE_KIND__FUNCTION) {
        String__append_char(cdecl->right, ')');
    }
    if (type_cdecl.right != NULL) {
        String__append_string(cdecl->right, type_cdecl.right);
        String__delete(type_cdecl.right);
    }
}

void declare(CDECL *cdecl, Checked_Type *symbol_type) {
    if (symbol_type->kind == CHECKED_TYPE_KIND__BOOL) {
        cdecl->type = String__create_from("bool");
    } else if (symbol_type->kind == CHECKED_TYPE_KIND__I16) {
        cdecl->type = String__create_from("int16_t");
    } else if (symbol_type->kind == CHECKED_TYPE_KIND__I32) {
        cdecl->type = String__create_from("int32_t");
    } else if (symbol_type->kind == CHECKED_TYPE_KIND__I64) {
        cdecl->type = String__create_from("int64_t");
    } else if (symbol_type->kind == CHECKED_TYPE_KIND__I8) {
        cdecl->type = String__create_from("int8_t");
    } else if (symbol_type->kind == CHECKED_TYPE_KIND__U16) {
        cdecl->type = String__create_from("uint16_t");
    } else if (symbol_type->kind == CHECKED_TYPE_KIND__U32) {
        cdecl->type = String__create_from("uint32_t");
    } else if (symbol_type->kind == CHECKED_TYPE_KIND__U64) {
        cdecl->type = String__create_from("uint64_t");
    } else if (symbol_type->kind == CHECKED_TYPE_KIND__U8) {
        cdecl->type = String__create_from("uint8_t");
    } else if (symbol_type->kind == CHECKED_TYPE_KIND__ANY) {
        cdecl->type = String__create_from("void");
    } else if (symbol_type->kind == CHECKED_TYPE_KIND__NOTHING) {
        cdecl->type = String__create_from("void");
    } else if (symbol_type->kind == CHECKED_TYPE_KIND__ARRAY) {
        declare_array(cdecl, (Checked_Array_Type *)symbol_type);
    } else if (symbol_type->kind == CHECKED_TYPE_KIND__EXTERNAL) {
        cdecl->type = String__create_copy(((Checked_External_Type *)symbol_type)->super.name);
    } else if (symbol_type->kind == CHECKED_TYPE_KIND__FUNCTION) {
        declare_function(cdecl, (Checked_Function_Type *)symbol_type);
    } else if (symbol_type->kind == CHECKED_TYPE_KIND__FUNCTION_POINTER) {
        declare_function_pointer(cdecl, (Checked_Function_Pointer_Type *)symbol_type);
    } else if (symbol_type->kind == CHECKED_TYPE_KIND__STRUCT) {
        cdecl->type = String__create_from("struct ");
        String__append_string(cdecl->type, ((Checked_Named_Type *)symbol_type)->name);
    } else if (symbol_type->kind == CHECKED_TYPE_KIND__POINTER) {
        declare_pointer(cdecl, (Checked_Pointer_Type *)symbol_type);
    } else {
        pWriter__begin_location_message(stderr_writer, symbol_type->location, WRITER_STYLE__TODO);
        pWriter__write__cstring(stderr_writer, "TODO: Add support for checked type kind: ");
        pWriter__write__int64(stderr_writer, symbol_type->kind);
        pWriter__end_location_message(stderr_writer);
        panic();
    }
}
