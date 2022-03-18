// Max length of a word
#define MAX_WORD_LENGTH 100
// Max length of a page id
#define MAX_ID_LENGTH 10
// Max length of a record in the index file
#define MAX_RECORD_LENGTH 1000
// Max length of a file path
#define MAX_PATH_LENGTH 100

void count(Node *[], char *, int);

int count_page(Node *[], int);

void save_dict(Node *[]);

Node **load_dict();
