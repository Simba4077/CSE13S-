#include "hash.h"

#include "badhash.h"
#include "ll.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create a new hash table
Hashtable *hash_create(void) {
    int size = 9000000;
    Hashtable *table = (Hashtable *) malloc(sizeof(Hashtable));
    if (table == NULL) {
        fprintf(stderr, "Failed to allocate memory for hash table\n");
        return NULL;
    }
    table->size = size;
    table->buckets = (LL *) malloc((unsigned long) size * sizeof(LL));
    if (table->buckets == NULL) {
        fprintf(stderr, "Failed to allocate memory for hash table buckets\n");
        free(table);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        table->buckets[i].head = NULL;
        table->buckets[i].tail = NULL;
    }
    return table;
}

// Function to insert a key-value pair into the hash table
bool hash_put(Hashtable *table, char *key, int value) {
    if (key == NULL || table == NULL) {
        fprintf(stderr, "Invalid input to hash_put\n");
        return false;
    }
    size_t index = hash(key) % (unsigned long) table->size; // Ensure index is within bounds
    Node *node = (Node *) malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Failed to allocate memory for node\n");
        return false;
    }
    node->key = strdup(key); // Allocate memory and copy the key
    if (node->key == NULL) {
        fprintf(stderr, "Failed to duplicate key\n");
        free(node);
        return false;
    }
    node->value = (int *) malloc(sizeof(int));
    if (node->value == NULL) {
        fprintf(stderr, "Failed to allocate memory for node value\n");
        free(node->key);
        free(node);
        return false;
    }
    *node->value = value;
    node->next = NULL;

    if (table->buckets[index].head == NULL) {
        table->buckets[index].head = node;
        table->buckets[index].tail = node;
    } else {
        table->buckets[index].tail->next = node;
        table->buckets[index].tail = node;
    }
    return true;
}

// Function to retrieve a value from the hash table
int *hash_get(Hashtable *table, char *key) {
    if (table == NULL || key == NULL) {
        fprintf(stderr, "Invalid input to hash_get\n");
        return NULL;
    }
    size_t index = hash(key) % (unsigned long) table->size; // Ensure index is within bounds
    Node *node = table->buckets[index].head;
    while (node != NULL) {
        if (node->key != NULL && strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

// Function to destroy the hash table and free memory
void hash_destroy(Hashtable **table) {
    if (table == NULL || *table == NULL) {
        return;
    }
    for (int i = 0; i < (*table)->size; i++) {
        Node *node = (*table)->buckets[i].head;
        while (node != NULL) {
            Node *temp = node;
            node = node->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free((*table)->buckets);
    free(*table);
    *table = NULL;
}
