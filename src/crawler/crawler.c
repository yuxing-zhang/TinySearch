#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "html.h"
#include "hash.h"
#include "dict.h"
#include "crawler.h"

// Recursively visit a html page. Running DFS with a maximum depth.
void visit(Node *dict[], const char *url, int dep, int *id) {
    printf("visiting %d %d\n", dep, *id);
    char *key = malloc(sizeof(char) * MAX_URL_LENGTH);
    strcpy(key, url);
    add_key(dict, key, NULL);
    // Calling the shell to download the webpage
    char cmd[1000];
    memset(cmd, 0, sizeof cmd);
    char pth[20];
    sprintf(pth, "../../data/%d.html", *id);
    sprintf(cmd, "curl %s -o %s", url, pth);
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
    return;
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

int main() {
    system("rm -r ../../data; mkdir ../../data");
    char *seed = "https://web.cs.dartmouth.edu/";
    Node *dict[MAX_SLOT];
    for (int i = 0; i < MAX_SLOT; i++)
        dict[i] = NULL;
    int id = 0;
    visit(dict, seed, 0, &id);
    free_dict(dict);
}
