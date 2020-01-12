#include "List.h"

#include <stdlib.h>

List *list__create() {
    List *self = malloc(sizeof(List));
    self->first = NULL;
    self->last = NULL;
    self->size = 0;
    return self;
}

int list__size(List *self) {
    return self->size;
}

void *list__get(List *self, int index) {
    List_Item *item = self->first;
    int item_index = 0;
    while (item_index < index && item != NULL) {
        item = item->next;
        item_index += 1;
    }
    return item != NULL ? item->data : NULL;
}

void list__append(List *self, void *data) {
    List_Item *item = malloc(sizeof(List_Item));
    item->data = data;
    item->next = NULL;
    if (self->first == NULL) {
        item->prev = NULL;
        self->first = item;
    } else {
        item->prev = self->last;
        self->last->next = item;
    }
    self->last = item;
    self->size += 1;
}

List_Iterator list__create_iterator(List *self) {
    List_Iterator iterator;
    iterator.reversed = 0;
    iterator.current = NULL;
    iterator.next = self->first;
    list_iterator__save_state(&iterator);
    return iterator;
}

List_Iterator list__create_reversed_iterator(List *self) {
    List_Iterator iterator;
    iterator.reversed = 1;
    iterator.current = NULL;
    iterator.next = self->last;
    list_iterator__save_state(&iterator);
    return iterator;
}

int list_iterator__has_next(List_Iterator *self) {
    return self->next != NULL;
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
    self->next = self->reversed ? self->current->prev : self->current->next;
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
