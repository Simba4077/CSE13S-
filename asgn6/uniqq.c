#include "badhash.c"
#include "badhash.h"
#include "hash.c"
#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    Hashtable *table = hash_create();
    char line[255];
    int count = 0;
    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = '\0';
        if (hash_get(table, line) == NULL) {
            hash_put(table, line, 1);
            count++;
        }
    }

    printf("%d\n", count);

    hash_destroy(&table);
    return 0;
}
