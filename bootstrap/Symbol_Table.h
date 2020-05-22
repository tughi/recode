#ifndef __recode__symbol_table_h__
#define __recode__symbol_table_h__

#include "List.h"
#include "String.h"

typedef List Symbol_Table;

typedef struct Symbol_Table_Item {
    String *name;
} Symbol_Table_Item;

Symbol_Table *symbol_table__create();

Symbol_Table_Item *symbol_table__find_item(Symbol_Table *self, String *name);
void symbol_table__add_item(Symbol_Table *self, Symbol_Table_Item *item);

#endif
