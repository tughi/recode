#ifndef __CDECL_H__
#define __CDECL_H__

#include "Checked_Code.h"

typedef struct CDECL_Name {
    void (*write)(struct CDECL_Name *name, Writer *writer);
} CDECL_Name;

void String__append_cdecl(String *self, CDECL_Name *name, Checked_Type *type);

void pWriter__write__cdecl(Writer *writer, CDECL_Name *name, Checked_Type *type);

typedef struct CDECL_Local_Name {
    CDECL_Name super;
    String *name;
} CDECL_Local_Name;

CDECL_Local_Name CDECL_Local_Name__create(String *name);

typedef struct CDECL_Procedure_Name {
    CDECL_Name super;
    Checked_Procedure_Symbol *procedure_symbol;
} CDECL_Procedure_Name;

CDECL_Procedure_Name CDECL_Procedure_Name__create(Checked_Procedure_Symbol *procedure_symbol);

typedef struct CDECL_Variable_Name {
    CDECL_Name super;
    Checked_Variable_Symbol *variable_symbol;
} CDECL_Variable_Name;

CDECL_Variable_Name CDECL_Variable_Name__create(Checked_Variable_Symbol *variable_symbol);

#endif
