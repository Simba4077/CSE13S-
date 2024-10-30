#include "ll.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

LL *list_create(void) {
    LL *l = (LL *) malloc(sizeof(LL));
    if (l == NULL) {
        return NULL;
    }
    l->head = NULL;
    l->tail = NULL;
    return l;
}

bool list_add(LL *l, item *i) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n == NULL) {
        return false;
    }
    n->data = *i;
    n->next = NULL;
    if (l->head == NULL) {
        l->head = n;
        l->tail = n;

    } else {
        l->tail->next = n;
        l->tail = n;
    }
    return true;
}

item *list_find(LL *l, bool (*cmpfn)(item *, item *), item *i) {
    Node *n = l->head;
    while (n != NULL) {
        if (cmpfn(&n->data, i)) {
            return &n->data;
        }
        n = n->next;
    }
    return NULL;
}

void list_destroy(LL **ll) {
    if (ll == NULL || *ll == NULL) {
        return;
    }
    Node *current = (*ll)->head;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(*ll);
    *ll = NULL;
}

void list_remove(LL *ll, bool (*cmpfn)(item *, item *), item *iptr) {
    if (ll == NULL || ll->head == NULL) {
        return;
    }

    if (cmpfn(&ll->head->data, iptr)) {
        Node *next = ll->head->next;
        free(ll->head);
        ll->head = next;
        if (ll->head == NULL) {
            ll->tail = NULL;
        }
        return;
    }

    Node *current = ll->head;
    Node *previous = NULL;

    while (current != NULL && !cmpfn(&current->data, iptr)) {
        previous = current;
        current = current->next;
    }

    if (current != NULL) {

        previous->next = current->next;
        if (current->next == NULL) {
            ll->tail = previous;
        }
        free(current);
    }
}
