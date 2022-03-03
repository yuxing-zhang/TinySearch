#define MAX_SLOT 10000

// Linked list node
typedef struct Node {
    const char *key;
    void *value;
    struct Node *next;
} Node;

Node *create_node(const char *, void *, Node *);

int has_key(Node *[], const char *);

void add_key(Node *[], const char *, void *);

void update_key(Node *[], const char *, void *);

void free_node(Node *);

void free_list(Node *);

void free_dict(Node *[]);
