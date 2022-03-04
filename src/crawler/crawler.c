#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "html.h"
#include "hash.h"
#include "dict.h"
#include "crawler.h"

// Recursively visit a html page. Running DFS with a maximum depth.
void visit(Node *dict[], const char *url, int dep, int *id) {
    printf("visiting page %d at depth %d\nurl = %s\n", *id, dep, url);
    char *key = malloc(sizeof(char) * MAX_URL_LENGTH);
    strcpy(key, url);
    add_key(dict, key, NULL);
    // Calling the shell to download the webpage
    char cmd[1000];
    memset(cmd, 0, sizeof cmd);
    char pth[20];
    sprintf(pth, "../../data/%d.html", *id);
    // CAVEAT: put url into ''
    sprintf(cmd, "echo '%s' > %s; curl -sS '%s' >> %s", url, pth, url, pth);
    if (system(cmd)) {
        --*id;
        return;
    }
    if (dep == MAX_DEPTH)
        return;
   // Run DFS on this webpage
    char *html = load_html(url, pth);
    int pos = 0;
    char next[MAX_URL_LENGTH];
    while ((pos = get_next_url(html, url, next, pos)) != -1)
        if (!has_key(dict, next)) {
            ++*id;
            visit(dict, next, dep+1, id);
        }
    free(html);
}

char *load_html(const char *url, const char *pth) {
    FILE *f = fopen(pth, "r");
    char *html = malloc(sizeof(char) * MAX_PAGE_LENGTH);
    memset(html, 0, sizeof(char) * MAX_PAGE_LENGTH);
    char line[MAX_LINE_LENGTH];
    while (!feof(f)) {
        fgets(line, sizeof(line), f);
        strcat(html, line);
    }
    return html; 
}

int main(int argc, char *argv[]) {
    system("rm -r ../../data; mkdir ../../data");
    if (argc > 2) {
        puts("usage: ./crawler [URL]");
        exit(1);
    }
    char seed[MAX_URL_LENGTH] = "https://web.cs.dartmouth.edu/";
    if (argc == 2) {
        if (strcmp(argv[1], "-h") && strcmp(argv[1], "--help"))
            strcpy(seed, argv[1]);
        else {
            puts("usage: ./crawler [URL]");
            exit(0);
        }
    }
    Node *dict[MAX_SLOT];
    for (int i = 0; i < MAX_SLOT; i++)
        dict[i] = NULL;
    int id = 0;
    visit(dict, seed, 0, &id);
    free_dict(dict);
}
