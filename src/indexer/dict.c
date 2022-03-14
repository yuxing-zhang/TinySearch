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

Node **create_dict() {
    Node **dict = malloc(sizeof(Node *) * MAX_SLOT);
    memset(dict, 0, sizeof(Node *) * MAX_SLOT);
    return dict;
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

void *get_value(Node *dict[], const char *key) {
    int k = hash(key) % MAX_SLOT;
    Node *p;
    for (p = dict[k]; strcmp(p->key, key); p = p->next) {}
    return p->value;
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

// The below are cleaning routines, wherein parameter l indicates
// the current layer in case the dictionary is nested.

// Clean a node
void free_node(Node *p, int l) {
    free(p->key);
    if (l == 0)
        free(p->value);
    else
        free_dict(p->value, l);
    free(p);
}

// Clean a linked list
void free_list(Node *p, int l) {
    if (!p) return;
    if (p->next) {
        free_list(p->next, l);
        p->next = NULL;
    }
    free_node(p, l);
}

// Clean a dictionary
void free_dict(Node *dict[], int l) {
    for (int i = 0; i < MAX_SLOT; i++)
        free_list(dict[i], l-1);
    free(dict);
}
