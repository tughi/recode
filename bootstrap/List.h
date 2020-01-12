#ifndef __recode__list_h__
#define __recode__list_h__

typedef struct List_Item {
    void *data;
    struct List_Item *next;
    struct List_Item *prev;
} List_Item;

typedef struct List {
    List_Item *first;
    List_Item *last;
    int size;
} List;

typedef struct List_Iterator {
    int reversed;
    List_Item *current;
    List_Item *next;
    List_Item *saved_current;
    List_Item *saved_next;
} List_Iterator;

List *list__create();

int list__size(List *list);

void *list__get(List *list, int index);

void list__append(List *self, void *item);

List_Iterator list__create_iterator(List *self);

List_Iterator list__create_reversed_iterator(List *self);

int list_iterator__has_next(List_Iterator *self);

void *list_iterator__current(List_Iterator *self);

void *list_iterator__next(List_Iterator *self);

void list_iterator__save_state(List_Iterator *self);

void list_iterator__restore_state(List_Iterator *self);

#endif
