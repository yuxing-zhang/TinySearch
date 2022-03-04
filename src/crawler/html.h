// Maximal length of webpages
#define MAX_PAGE_LENGTH 1000000
// Maximal length of a line in pages
#define MAX_LINE_LENGTH 1000
// Maximal url length
#define MAX_URL_LENGTH 1000

int get_next_url(char *, const char *, char *, int);
void remove_white_space(char *);
int normalize_url(char *);
void lower(char *);
