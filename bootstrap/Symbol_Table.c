#include "Symbol_Table.h"

#include <stdlib.h>

Symbol_Table *symbol_table__create() {
    return list__create();
}

Symbol_Table_Item *symbol_table__find_item(Symbol_Table *self, String *name) {
    for (List_Iterator iterator = list__create_iterator(self); list_iterator__has_next(&iterator);) {
        Symbol_Table_Item *item = list_iterator__next(&iterator);
        if (string__equals(name, item->name->data)) {
            return item;
        }
    }
    return NULL;
}

static Symbol_Table_Item *symbol_table_item__create(String *name) {
    Symbol_Table_Item *self = malloc(sizeof(Symbol_Table_Item));
    self->name = name;
    return self;
}

Symbol_Table_Item *symbol_table__add_item(Symbol_Table *self, String *name) {
    Symbol_Table_Item *item = symbol_table_item__create(name);
    list__append(self, item);
    return item;
}
