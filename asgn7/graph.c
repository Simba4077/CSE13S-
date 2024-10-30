#include "graph.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Graph *graph_create(uint32_t vertices, bool directed) {
    Graph *g = calloc(1, sizeof(Graph));
    g->vertices = vertices;
    g->directed = directed;

    g->visited = calloc(vertices, sizeof(bool));
    g->names = calloc(vertices, sizeof(char *));

    g->weights = calloc(vertices, sizeof(g->weights[0]));

    for (uint32_t i = 0; i < vertices; ++i) {
        g->weights[i] = calloc(vertices, sizeof(g->weights[0][0]));
    }
    return g;
}

void graph_free(Graph **gp) {
    if (!gp || !*gp) {
        return;
    }
    Graph *g = *gp;

    for (uint32_t i = 0; i < g->vertices; ++i) {
        free(g->weights[i]);
        free(g->names[i]);
    }

    free(g->names);
    free(g->weights);
    free(g->visited);
    free(g);
    *gp = NULL;
    //frees all memory used by the graph
    //set graph pointer to null
}

uint32_t graph_vertices(const Graph *g) {
    if (!g) {
        return 0;
    }
    return g->vertices;
    //finds the number of vertices in a graph
}

void graph_add_vertex(Graph *g, const char *name, uint32_t v) {
    if (g->names[v])
        free(g->names[v]);
    g->names[v] = strdup(name);
}

const char *graph_get_vertex_name(const Graph *g, uint32_t v) {
    if (!g || v >= g->vertices) {
        return NULL;
    }
    return g->names[v];
    //gets name of city with vertex v from the array of city names
    //does not allocate a new string, just returns the one stored in graph
}

char **graph_get_names(const Graph *g) {
    if (!g) {
        return NULL;
    }
    char **names_array = malloc(g->vertices * sizeof(char *));
    if (!names_array)
        return NULL;

    for (uint32_t i = 0; i < g->vertices; ++i) {
        names_array[i] = strdup(g->names[i]);
        if (!names_array[i]) {
            for (uint32_t j = 0; j < i; ++j) {
                free(names_array[j]);
            }
            free(names_array);
            return NULL;
        }
    }
    return names_array;
    //get names of every city in an array, returns a double pointer (the array of strings)
}

void graph_add_edge(Graph *g, uint32_t start, uint32_t end, uint32_t weight) {
    if (!g || start >= g->vertices || end >= g->vertices)
        return;

    if (!g->weights) {
        g->weights = malloc(g->vertices * sizeof(uint32_t *));
        for (uint32_t i = 0; i < g->vertices; ++i) {
            g->weights[i] = calloc(g->vertices, sizeof(uint32_t));
        }
    }

    g->weights[start][end] = weight;
    if (!g->directed) {
        g->weights[end][start] = weight;
    }
    //adds an edge between start and end with weight weight to the adjacency matrix of the graph
}

uint32_t graph_get_weight(const Graph *g, uint32_t start, uint32_t end) {
    if (start >= g->vertices || end >= g->vertices) {
        return 0;
    }

    uint32_t weight = g->weights[start][end];

    if (g->directed && weight == 0) {
        return 0;
    }

    if (!g->directed && weight == 0) {
        weight = g->weights[end][start];
    }
    return weight;
    //looks up weight of the edge between start and end and returns it
}

void graph_visit_vertex(Graph *g, uint32_t v) {
    if (v >= g->vertices) {
        return;
    }

    g->visited[v] = true;
    //adds a vertex v to the list of visted vertices
}

void graph_unvisit_vertex(Graph *g, uint32_t v) {
    if (v >= g->vertices) {
        return;
    }
    g->visited[v] = false;
    //Removes vertex v from list of visited vertices
}

bool graph_visited(const Graph *g, uint32_t v) {
    if (v >= g->vertices) {
        return false;
    }

    return g->visited[v];
    //returns true if vertex v is visited in graph g, false otherwise
}

void graph_print(const Graph *g) {
    printf("Number of Vertices: %d\n", g->vertices);
    printf("Directed: %s\n", g->directed ? "true" : "false");

    // Print the names of the vertices
    printf("Vertex Names:\n");
    for (uint32_t i = 0; i < g->vertices; i++) {
        printf("%d: %s\n", i, g->names[i]);
    }

    // Print the visited status of each vertex
    printf("Visited Status:\n");
    for (uint32_t i = 0; i < g->vertices; i++) {
        printf("Vertex %d: %d\n", i, g->visited[i]);
    }

    // Print the weights of the edges
    printf("Edge Weights:\n");
    for (uint32_t i = 0; i < g->vertices; i++) {
        for (uint32_t j = 0; j < g->vertices; j++) {
            if (g->weights[i][j] != 0) {
                printf("Edge (%s, %s): %d\n", g->names[i], g->names[j], g->weights[i][j]);
            }
        }
    } //prints human_readable representation of a graph
    return;
}
