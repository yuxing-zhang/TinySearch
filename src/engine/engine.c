#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../utils/dict.h"
#include "../utils/html.h"
#include "../indexer/indexer.h"
#include "engine.h"

/* Calculate the intersection of two counters. Common elements are added up.
 * The results are saved in `dict`.
 * and_add(dict1, dict2) = {x: dict1[x] + dict2[x] | x in dict1 && x in dict2}
 */
void and_add(Node **dict, Node **count) {
    Node *p, *q;
    for (int i = 0; i < MAX_SLOT; i++)
        if (dict[i])
            for (p = dict[i]; p;) {
                if (has_key(count, p->key)) {
                    *(int *)p->value += *(int *)get_value(count, p->key);
                    p = p-> next;
                }
                else {
                    q = p;
                    p = p->next;
                    del_key(dict, q->key);
                }
            } } /* Carry a search again `index`.
 * nf - # of files in data/html
 * term - search terms
 * n - # of search terms
 * Return - # of pages containing all search terms
 *
 * The results are sorted decreasingly according to node value.
 */
void search(Node **index, int nf, char **term, int n) {
    Node **dict = create_dict();
    int *c;
    char *id;
    // Time the search
    clock_t begin = clock(), end;
    // Build a fresh dict.
    // dict = {x: 0 for 'x.html' in 'data/'}
    for (int i = 0; i < nf ; i++) {
        c = malloc(sizeof(int));
        *c = 0;
        id = malloc(MAX_ID_LENGTH);
        memset(id, 0, MAX_ID_LENGTH);
        sprintf(id, "%d", i);
        add_key(dict, id, c);
    }
    // Remove pages not containing all terms and
    // add up the word count for remaining pages.
    for (int i = 0; i < n; i++) {
        if (has_key(index, term[i]))
            and_add(dict, get_value(index, term[i]));
        else {
            // Search failed if a term is contained in no page
            end = clock();
            printf("0 pages found in %.3f seconds\n", (float)(end-begin) /\
                    CLOCKS_PER_SEC);
            return;
        }
    }
    // Store the valid `id`s in an array and sort it
    Node result[nf];
    // # of found html
    int nr = 0;
    for (int i = 0; i < MAX_SLOT; i++)
        if (dict[i])
            for (Node *p = dict[i]; p; p = p->next) {
                result[nr] = *p;
                nr++;
            }
    qsort(result, nr, sizeof(Node), cmp);
    // Print results
    end = clock();
    printf("%d pages found in %.3f seconds\n", nr, (float)(end-begin) /\
            CLOCKS_PER_SEC);
    char url[MAX_URL_LENGTH], pth[MAX_PATH_LENGTH];
    FILE *f;
    for (int i = 0; i < nr; i++) {
        sprintf(pth, "data/html/%s.html", result[i].key);
        f = fopen(pth, "r");
        fgets(url, sizeof url, f);
        printf("%s", url);
        fclose(f);
    }
    free_dict(dict, 1);
}

// Cmparison function to use in sorting search results.
// This will sort the array in decreasing order.
int cmp(const void *m, const void *n) {
    const Node *cm = m;
    const Node *cn = n;
    int mv = *(int *)cm->value, nv = *(int *)cn->value;
    return (mv < nv) - (nv < mv);
}

Node **load_dict() {
    Node **dict = create_dict();
    FILE *f = fopen("data/index.dat", "r");
    char buf[MAX_INDEX_LENGTH], *s, *t, *w, *id;
    memset(buf, 0, sizeof buf);
    int page_count, *count;
    Node **c;
    while (fgets(buf, sizeof buf, f)) {
        // Remove trailing new-line
        // buff = "word page_count id1 count1 id2 count2 ..."
        buf[strlen(buf)-1] = 0;
        t = buf;
        // `s` = word
        s = strsep(&t, " ");
        w = malloc(MAX_WORD_LENGTH);
        strcpy(w, s);
        c = create_dict();
        add_key(dict, w, c);
        // `s` = page_count
        s = strsep(&t, " ");
        sscanf(s, "%d", &page_count);
        for (int i = 0; i < page_count; i++) {
            // `s` = id_i
            s = strsep(&t, " ");
            id = malloc(MAX_ID_LENGTH);
            strcpy(id, s);
            // `s` = count_i
            s = strsep(&t, " ");
            count = malloc(sizeof(int));
            sscanf(s, "%d", count);
            add_key(c, id, count);
        }
    }
    fclose(f);
    return dict;
}

int main(int argc, char *argv[]) {
    Node **index = load_dict();
    int i, j;
    char pth[MAX_PATH_LENGTH], buf[MAX_SEARCH_LENGTH];
    char *ter[MAX_TERMS], *s, *t;
    FILE *f;
    for (j = 0;;j++) {
        sprintf(pth, "data/html/%d.html", j);
        if(!(f = fopen(pth, "r")))
            break;
    }
    fclose(f);
//    search(index, j, argv+1, argc-1);    
    // Reserve space to contain search terms
    for (i = 0; i < MAX_TERMS; i++)
        ter[i] = malloc(MAX_TERM_LENGTH);
    // Search loop
    while (1) {
        printf("Search >>> ");
        if(!fgets(buf, sizeof buf, stdin)) {
            putchar('\n');
            break;
        }
        // In case of no input
        if (buf[0] == '\n')
            continue;
        // Change upper case letters to lower cases
        for (i = 0; i < strlen(buf); i++)
            if (buf[i] >= 'A' && buf[i] <= 'Z')
                buf[i] += 32;
        // Removing trailing newline
        buf[i-1] = 0;
        t = buf;
        for (i = 0; (s = strsep(&t, " ")) != NULL;)
            if (*s)
                strcpy(ter[i++], s);
        search(index, j, ter, i);
    }
    free_dict(index, 2);
    for (i = 0; i < MAX_TERMS; i++)
        free(ter[i]);
}










