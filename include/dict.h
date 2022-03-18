// Size of the array in a hash table
#define MAX_SLOT 10000

// Linked list node
typedef struct Node {
    char *key;
    void *value;
    struct Node *next;
} Node;

Node *create_node(char *, void *, Node *);

Node **create_dict();

int has_key(Node *[], const char *);

void *get_value(Node *[], const char *);

void add_key(Node *[], char *, void *);

void update_key(Node *[], const char *, void *);

void del_key(Node *[], const char *);

void free_node(Node *, int);

void free_list(Node *, int);

void free_dict(Node *[], int);
