#include "graph.h"
#include "path.h"
#include "stack.h"

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH_MAX 4096
typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
    uint32_t *prev_vertices;
} Path;

void print_help(void) {
    fprintf(stdout, "Usage: tsp [options]\n\n");

    fprintf(stdout,
        "-i infile    Specify the input file path containing the cities and edge\n             of "
        "a graph. If not specified, the default input should be\n             set as stdin.\n\n");
    fprintf(stdout, "-o outfile   Specify the output file path to print to. If not specified,\n    "
                    "         the default output should be set as stdout.\n\n");
    fprintf(stdout, "-d           Specifies the graph to be directed.\n\n");
    fprintf(stdout,
        "-h           Prints out a help message describing the purpose of the\n             graph "
        "and the command-line options it accepts, exiting the\n             program afterwards.\n");
}

Graph *graph_read_from_file(FILE *infile, bool directed) {
    if (infile == NULL) {
        fprintf(stderr, "Error: input file is NULL\n");
        exit(1);
    }

    uint32_t num_vertices;
    if (fscanf(infile, "%u\n", &num_vertices) != 1) {
        fprintf(stderr, "Error reading number of vertices\n");
        fclose(infile);
        exit(1);
    }

    Graph *g = graph_create(num_vertices, directed);

    if (g == NULL) {
        fprintf(stderr, "Error creating graph\n");
        fclose(infile);
        exit(1);
    }

    char name[PATH_MAX];

    for (uint32_t i = 0; i < num_vertices; ++i) {
        if (fgets(name, PATH_MAX, infile) == NULL) {
            fprintf(stderr, "Error reading vertex name\n");
            graph_free(&g);
            fclose(infile);
            exit(1);
        }
        name[strcspn(name, "\n")] = '\0'; // replace newline with terminating 0
        graph_add_vertex(g, name, i);
    }

    uint32_t num_edges;
    if (fscanf(infile, "%u\n", &num_edges) != 1) {
        fprintf(stderr, "Error reading number of edges\n");
        graph_free(&g);
        fclose(infile);
        exit(1);
    }

    for (uint32_t i = 0; i < num_edges; i++) {
        uint32_t from, to, weight;
        if (fscanf(infile, "%u %u %u\n", &from, &to, &weight) != 3) {
            fprintf(stderr, "Error reading edge\n");
            graph_free(&g);
            fclose(infile);
            exit(1);
        }
        graph_add_edge(g, from, to, weight);
        if (!directed) {
            graph_add_edge(g, to, from, weight);
        }
    }

    return g;
}

void dfs(Graph *g, Path *current_path, Path *shortest_path, bool *visited, uint32_t current_vertex,
    uint32_t start_vertex, bool *found_cycle) {
    visited[current_vertex] = true;
    path_add(current_path, current_vertex, g);

    if (path_vertices(current_path) == graph_vertices(g)
        && graph_get_weight(g, current_vertex, start_vertex) > 0) {
        path_add(current_path, start_vertex, g); // Complete the cycle by returning to start vertex
        *found_cycle = true;
        if (path_distance(current_path) < path_distance(shortest_path)
            || path_distance(shortest_path) == 0) {
            path_copy(shortest_path, current_path);
        }
        path_remove(current_path, g); // Remove start vertex to continue exploring other paths
    } else {
        // Create an array of vertices to sort by weight
        uint32_t vertices[graph_vertices(g)];
        for (uint32_t i = 0; i < graph_vertices(g); ++i) {
            vertices[i] = i;
        }

        // Sort vertices by weight to ensure we explore the shortest paths first
        for (uint32_t i = 0; i < graph_vertices(g); ++i) {
            for (uint32_t j = i + 1; j < graph_vertices(g); ++j) {
                if (graph_get_weight(g, current_vertex, vertices[i])
                    > graph_get_weight(g, current_vertex, vertices[j])) {
                    uint32_t temp = vertices[i];
                    vertices[i] = vertices[j];
                    vertices[j] = temp;
                }
            }
        }

        for (uint32_t i = 0; i < graph_vertices(g); ++i) {
            uint32_t next_vertex = vertices[i];
            if (!visited[next_vertex] && graph_get_weight(g, current_vertex, next_vertex) > 0) {
                dfs(g, current_path, shortest_path, visited, next_vertex, start_vertex,
                    found_cycle);
            }
        }
    }

    path_remove(current_path, g);
    visited[current_vertex] = false;
}

void path_print_reverse(const Path *p, FILE *outfile, const Graph *g) {
    if (p == NULL || outfile == NULL || g == NULL) {
        return;
    }

    Stack *reversed_stack = stack_create(stack_size(p->vertices));
    Stack *temp_stack = stack_create(stack_size(p->vertices));
    uint32_t val;

    // Pop elements from the original stack and push them onto the reversed stack
    while (!stack_empty(p->vertices)) {
        stack_pop(p->vertices, &val);
        stack_push(temp_stack, val); // Use a temp stack to restore original stack
        stack_push(reversed_stack, val);
    }

    // Restore the original stack
    while (!stack_empty(temp_stack)) {
        stack_pop(temp_stack, &val);
        stack_push(p->vertices, val);
    }

    // Print the reversed stack
    while (!stack_empty(reversed_stack)) {
        stack_pop(reversed_stack, &val);
        fprintf(outfile, "%s\n", g->names[val]);
    }

    stack_free(&reversed_stack);
    stack_free(&temp_stack);
}

int main(int argc, char *argv[]) {
    bool directed = false;
    char *input_filename = NULL;
    char *output_filename = NULL;
    FILE *outfile = stdout;
    int opt;

    while ((opt = getopt(argc, argv, "i:o:dh")) != -1) {
        switch (opt) {
        case 'i': input_filename = optarg; break;
        case 'o': output_filename = optarg; break;
        case 'd': directed = true; break;
        case 'h': print_help(); exit(0);
        }
    }

    FILE *infile = stdin;
    if (input_filename != NULL) {
        infile = fopen(input_filename, "r");
        if (infile == NULL) {
            fprintf(stderr, "Error opening input file: %s\n", input_filename);
            exit(1);
        }
    }

    if (output_filename != NULL) {
        outfile = fopen(output_filename, "w");
        if (outfile == NULL) {
            fprintf(stderr, "Error opening output file: %s\n", output_filename);
            exit(1);
        }
    }

    Graph *g = graph_read_from_file(infile, directed);

    bool *visited = calloc(graph_vertices(g), sizeof(bool));
    Path *current_path
        = path_create(graph_vertices(g) + 1); // +1 to include the start vertex at the end
    Path *shortest_path = path_create(graph_vertices(g) + 1);
    bool found_cycle = false;

    dfs(g, current_path, shortest_path, visited, 0, 0, &found_cycle);

    if (found_cycle) {
        fprintf(outfile, "Alissa starts at:\n");
        path_print_reverse(shortest_path, outfile, g);
        fprintf(outfile, "Total Distance: %u\n", path_distance(shortest_path));
    } else {
        fprintf(stdout, "No path found! Alissa is lost!\n");
    }

    graph_free(&g);
    free(visited);
    path_free(&current_path);
    path_free(&shortest_path);

    if (input_filename != NULL) {
        fclose(infile);
    }

    if (outfile != stdout) {
        fclose(outfile);
    }
    return 0;
}
