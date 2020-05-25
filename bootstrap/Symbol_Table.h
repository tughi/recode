#ifndef __recode__symbol_table_h__
#define __recode__symbol_table_h__

#include "AST.h"

typedef List Symbol_Table;

typedef struct Symbol_Table_Item {
    String *name;
    Composite_Type *type;
} Symbol_Table_Item;

Symbol_Table *symbol_table__create();

Symbol_Table_Item *symbol_table__find_item(Symbol_Table *self, String *name);
Symbol_Table_Item *symbol_table__add_item(Symbol_Table *self, String *name, Composite_Type *type);

#endif
