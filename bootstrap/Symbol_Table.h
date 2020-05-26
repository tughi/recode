#ifndef __recode__symbol_table_h__
#define __recode__symbol_table_h__

#include "AST.h"

typedef List Symbol_Table;

typedef struct Symbol {
    String *name;
    Type *type;
} Symbol;

Symbol_Table *symbol_table__create();

Symbol *symbol_table__find(Symbol_Table *self, String *name);
Symbol *symbol_table__add(Symbol_Table *self, String *name, Type *type);

#endif
