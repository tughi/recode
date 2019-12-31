#include "List.h"

#include <stdlib.h>

typedef struct List_Item {
    void *data;
    struct List_Item *next;
    struct List_Item *prev;
} List_Item;

typedef struct List {
    List_Item *first;
    List_Item *last;
} List;

typedef struct List_Iterator {
    List_Item *current;
    List_Item *next;
    List_Item *saved_current;
    List_Item *saved_next;
} List_Iterator;

List *list__create() {
    List *self = malloc(sizeof(List));
    self->first = NULL;
    self->last = NULL;
    return self;
}

void list__append(List *self, void *data) {
    List_Item *item = malloc(sizeof(List_Item));
    item->data = data;
    item->next = NULL;
    if (self->first == NULL) {
        item->prev = NULL;
        self->first = item;
    } else {
        item->prev = self->first;
        self->last->next = item;
    }
    self->last = item;
}

List_Iterator *list__create_iterator(List *self) {
    List_Iterator *iterator = malloc(sizeof(List_Iterator));
    iterator->current = NULL;
    iterator->next = self->first;
    list_iterator__save_state(iterator);
    return iterator;
}

void *list_iterator__current(List_Iterator *self) {
    if (self->current == NULL) {
        return NULL;
    }
    return self->current->data;
}

void *list_iterator__next(List_Iterator *self) {
    if (self->next == NULL) {
        return NULL;
    }
    self->current = self->next;
    self->next = self->next->next;
    return self->current->data;
}

void list_iterator__save_state(List_Iterator *self) {
    self->saved_current = self->current;
    self->saved_next = self->next;
}

void list_iterator__restore_state(List_Iterator *self) {
    self->current = self->saved_current;
    self->next = self->saved_next;
}
