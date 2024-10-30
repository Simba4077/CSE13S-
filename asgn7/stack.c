#include "stack.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack {
    uint32_t capacity;
    uint32_t top;
    uint32_t *items;
} Stack;

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->capacity = capacity;
    s->top = 0;
    s->items = calloc(s->capacity, sizeof(uint32_t));
    return s;
}
bool stack_full(const Stack *s) {
    if (s == NULL) {
        return false;
    }
    return s->top == s->capacity;
    //returns true if the stack is false, otherwise false
    //stack is full when the number of elements is equal to the capacity
}

void stack_free(Stack **sp) {
    if (sp != NULL && *sp != NULL) {
        if ((*sp)->items) {
            free((*sp)->items);
            (*sp)->items = NULL;
        }
        free(*sp);
    }
    if (sp != NULL) {
        *sp = NULL;
    }
}

bool stack_push(Stack *s, uint32_t val) {
    if (stack_full(s)) {
        return false;
    }

    s->items[s->top] = val;
    s->top++;
    return true;
}

bool stack_pop(Stack *s, uint32_t *val) {
    if (s == NULL || s->top == 0) {
        return false;
    }

    *val = s->items[s->top - 1];
    s->top--;

    return true;
    //sets integer pointed to by val to last item on stack and removes the last item on stack
    //returns true if successful, otherwise false
    //stack->top is not the index of the top value of the stack
}

bool stack_peek(const Stack *s, uint32_t *val) {
    if (s == NULL || s->top == 0) {
        return false;
    }

    *val = s->items[s->top - 1];
    return true;
    //sets integer pointed to by val to last item on the stack but does not modify the stack
    //returns true if successful, otherwise false
    //stack->top is not the index of the top value of the stack
}

bool stack_empty(const Stack *s) {
    if (s == NULL) {
        return false;
    }

    return s->top == 0;
    //returns true if stack is empty, otherwise false
}

uint32_t stack_size(const Stack *s) {
    if (s == NULL) {
        return 0;
    }

    return s->top;
    //returns number of elements in the stack, an empty stack contains zero elements
}

void stack_copy(Stack *dst, const Stack *src) {
    if (dst == NULL || src == NULL) {
        return;
    }
    assert(dst->capacity >= src->top);

    for (uint32_t i = 0; i < src->top; i++) {
        dst->items[i] = src->items[i];
    }

    dst->top = src->top;
    return;
    //overwrites dst with all items from src
    //update dst->top to know how many items are now in the stack
    //dst may not have a large enough capacity to store every item from src, so use assert to make sure that this is not the case
}

void stack_print(const Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s\n", cities[s->items[i]]);
    }
    return;
}
