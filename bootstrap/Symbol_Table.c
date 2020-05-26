#include "Symbol_Table.h"

#include <stdlib.h>

Symbol_Table *symbol_table__create() {
    return list__create();
}

Symbol *symbol_table__find(Symbol_Table *self, String *name) {
    for (List_Iterator iterator = list__create_iterator(self); list_iterator__has_next(&iterator);) {
        Symbol *item = list_iterator__next(&iterator);
        if (string__equals(name, item->name->data)) {
            return item;
        }
    }
    return NULL;
}

static Symbol *symbol_table_item__create(String *name, Type *type) {
    Symbol *self = malloc(sizeof(Symbol));
    self->name = name;
    self->type = type;
    return self;
}

Symbol *symbol_table__add(Symbol_Table *self, String *name, Type *type) {
    Symbol *item = symbol_table_item__create(name, type);
    list__append(self, item);
    return item;
}
