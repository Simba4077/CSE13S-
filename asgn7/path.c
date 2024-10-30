#include "graph.h"
#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct path {
    uint32_t total_weight;

    Stack *vertices;
} Path;

Path *path_create(uint32_t capacity) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p == NULL) {
        return NULL;
    }

    p->total_weight = 0;
    p->vertices = stack_create(capacity);
    if (p->vertices == NULL) {
        free(p);
        return NULL;
    }
    return p;
    //creates a path data structure, containing a Stack and a weight of zero
}

void path_free(Path **pp) {
    if (pp == NULL || *pp == NULL) {
        return;
    }

    Path *p = *pp;
    stack_free(&p->vertices);
    free(p);
    *pp = NULL;
    //frees a path and all associated memory
}

uint32_t path_vertices(const Path *p) {
    if (p == NULL) {
        return 0;
    }

    return stack_size(p->vertices);
    //finds number of vertices in a path
}

uint32_t path_distance(const Path *p) {
    if (p == NULL) {
        return 0;
    }

    return p->total_weight;

    //finds distance covered by a path
}

void path_add(Path *p, uint32_t val, const Graph *g) {
    if (p == NULL || g == NULL) {
        return;
    }

    uint32_t prev_vertex;
    //printf("The stack_size is: %u\n", stack_size(p->vertices));
    if (stack_size(p->vertices) > 0) {
        if (stack_peek(p->vertices, &prev_vertex)) {
            uint32_t weight = g->weights[prev_vertex][val];
            //    printf("Adding edge (%u, %u) with weight %u\n", prev_vertex, val,
            //          weight); // Debug statement
            if (weight > 0) {
                p->total_weight += weight;
            }
        }
    }

    stack_push(p->vertices, val);
    //printf("Pushed vertex: %u\n", val); // Debug statement
}

//Adds a vertex val from graph g to the path
//Update the distance and length of path
//Adding vertex to an empty path means distance remains zero
//Otherise lok upPath *path_create(uint32_t capacity){
//creates a path data structure, containing a Stack and a weight of zero

//distance can only be non-zero when there are at least two cities in the path

uint32_t path_remove(Path *p, const Graph *g) {
    if (p == NULL || g == NULL || stack_size(p->vertices) == 0) {
        printf("Path or graph is null, or stack is empty. Returning 0.\n");
        return 0; // Return 0 if path or graph is null or stack is empty
    }

    uint32_t removed_vertex;
    if (!stack_pop(p->vertices, &removed_vertex)) {
        printf("Failed to pop vertex from the stack. Returning 0.\n");
        return 0; // Return 0 if there is an issue with popping from the stack
    }

    // Debug statement

    if (stack_size(p->vertices) > 0) {
        uint32_t prev_vertex;
        if (stack_peek(p->vertices, &prev_vertex)) {
            uint32_t weight = g->weights[prev_vertex][removed_vertex];
            //        printf("Removing edge (%u, %u) with weight %u\n", prev_vertex, removed_vertex,
            //          weight); // Debug statement
            if (weight > 0) {
                p->total_weight -= weight;
            }
        }
    } else {
        p->total_weight = 0; // Reset total weight if no vertices are left in the path
    }

    //printf("Removed vertex: %u\n", removed_vertex); // Debug statement
    return removed_vertex;
}

//Removes most recently added vertex from the path
//Update the distance and length of the path based on the adjacency matrix in the graph pointed to by g
//Removing last vertex from path, distance should become zero
//Distance can only be non-zero when there are at least two cities in the path
//Return the index of the removed  flow better intovertex}

void path_copy(Path *dst, const Path *src) {
    if (dst == NULL || src == NULL) {
        return;
    }

    stack_free(&dst->vertices);

    uint32_t size = stack_size(src->vertices);
    dst->vertices = stack_create(size);
    if (dst->vertices == NULL) {
        return;
    }

    Stack *temp_stack = stack_create(size);

    // Copy elements from src stack to dst stack using a temporary stack
    while (!stack_empty(src->vertices)) {
        uint32_t val;
        if (!stack_pop(src->vertices, &val)) {
            stack_free(&temp_stack);
            return;
        }
        stack_push(temp_stack, val); // Push to temporary stack
    }

    // Restore src stack and copy to dst stack
    while (!stack_empty(temp_stack)) {
        uint32_t val;
        if (!stack_pop(temp_stack, &val)) {
            stack_free(&temp_stack);
            return;
        }
        stack_push(src->vertices, val); // Restore src stack
        stack_push(dst->vertices, val); // Copy to dst stack
    }

    stack_free(&temp_stack);

    dst->total_weight = src->total_weight;
}
//Copies a path from src to dst
//
//
//
void path_print(const Path *p, FILE *outfile, const Graph *g) {
    if (p == NULL || outfile == NULL || g == NULL) {
        return;
    }

    Stack *temp_stack = stack_create(stack_size(p->vertices));
    uint32_t top;

    // Copy the elements to a temporary stack to avoid modifying the original stack
    while (!stack_empty(p->vertices)) {
        stack_pop(p->vertices, &top);
        fprintf(outfile, "%s\n", g->names[top]);
        stack_push(temp_stack, top);
    }

    // Restore the original stack
    while (!stack_empty(temp_stack)) {
        stack_pop(temp_stack, &top);
        stack_push(p->vertices, top);
    }

    stack_free(&temp_stack);
}

//prints the path stored, using vertex names from g to the file outfile
//should only print the names of the vertices}
