#define MAX_WORD_LENGTH 100
#define MAX_ID_LENGTH 10
#define MAX_INDEX_LENGTH 1000

void count(Node *[], char *, int);
int count_page(Node *[], int);
void save_dict(Node *[]);
Node **load_dict();
