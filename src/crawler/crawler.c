#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "../utils/html.h"
#include "../utils/dict.h"
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
    char pth[100];
    sprintf(pth, "../data/html/%d.html", *id);
    // CAVEAT: put url into ''
    sprintf(cmd, "echo '%s' > %s; curl -sS '%s' >> %s", url, pth, url, pth);
    if (system(cmd)) {
        --*id;
        return;
    }
    if (dep == MAX_DEPTH)
        return;
   // Run DFS on this webpage
    char *html = load_html(pth);
    int pos = 0;
    char next[MAX_URL_LENGTH];
    while ((pos = get_next_url(html, url, next, pos)) != -1)
        if (!has_key(dict, next)) {
            ++*id;
            visit(dict, next, dep+1, id);
        }
    free(html);
}

int main(int argc, char *argv[]) {
    DIR *d;
    if ((d = opendir("../data/html")))
        system("rm -r ../data/html; mkdir ../data/html");
    else
        system("mkdir ../data/html");
    closedir(d);
    if (argc > 2) {
        puts("usage: ./crawler [(-h | --help) | URL]");
        exit(1);
    }
    char seed[MAX_URL_LENGTH] = "https://web.cs.dartmouth.edu/";
    if (argc == 2) {
        if (strcmp(argv[1], "-h") && strcmp(argv[1], "--help"))
            strcpy(seed, argv[1]);
        else {
            puts("usage: ./crawler [(-h | --help) | URL]");
            exit(0);
        }
    }
    Node **dict = create_dict();
    int id = 0;
    visit(dict, seed, 0, &id);
    free_dict(dict, 1);
}
