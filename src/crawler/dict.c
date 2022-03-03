/* A general hash table implementation that will be used in each of the three
 * components.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "dict.h"

// Helper function to create a node
Node *create_node(char *key, void *value, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->next = next;
    return node;
}
// Check uniqueness of a given key
int has_key(Node *dict[], const char *key) {
    int k = hash(key) % MAX_SLOT;
    if (!dict[k])
        return 0;
    for (Node *p = dict[k]; p; p = p->next)
        if (!strcmp(p->key, key))
            return 1;
    return 0;
}

// Add a key-value pair. Always use after uniqueness check
void add_key(Node *dict[], char *key, void *value) {
    int k = hash(key) % MAX_SLOT;
    Node *node = create_node(key, value, dict[k]);
    dict[k] = node;
}

// Change the value of an existent key.
void update_key(Node *dict[], const char *key, void *value) {
    int k = hash(key) % MAX_SLOT;
    Node *p;
    for (p = dict[k]; strcmp(p->key, key); p = p->next) {}
    p->value = value;
}

// Clean a node
void free_node(Node *p) {
    free(p->key);
    free(p->value);
    free(p);
}

// Clean a linked list
void free_list(Node *p) {
    if (!p) return;
    if (p->next) {
        free_list(p->next);
        p->next = NULL;
    }
    free_node(p);
}

// Clean a dictionary
void free_dict(Node *dict[]) {
    for (int i = 0; i < MAX_SLOT; i++)
        free_list(dict[i]);
}
