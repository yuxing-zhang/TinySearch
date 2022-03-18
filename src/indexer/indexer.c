/* The indexer builds a reverse index for crawled webpages. The index will be
 * saved as `/data/index.dat'.
 * The index is a nested dictionary:
 *     index = {word: {id: count | `id'.html has `word'}}
 * The index.dat contains newline separated records. Each record has the
 * following format:
 *     word count id1 count1 id2 count2 ...,
 * where `count' is the # of webpages containing `word', and `count'i is the #
 * of occurrence of `word' in page `id'i.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"
#include "html.h"
#include "indexer.h"

// Count a single occurrence of a word in a webpage. `dict' is updated.
void count(Node *dict[], char *word, int id) {
    Node **counter;
    int *c = malloc(sizeof(int));
    *c = 1;
    char *i = malloc(sizeof(char) * MAX_ID_LENGTH);
    sprintf(i, "%d", id);

    if (!has_key(dict, word)) {
        counter = create_dict();
        add_key(dict, word, counter);
        add_key(counter, i, c);
    } else {
        counter = get_value(dict, word);
        if (!has_key(counter, i))
            add_key(counter, i, c);
        else
            ++*(int *)get_value(counter, i);
    }
}

// Count the occurrence of every word in a webpage. `dict' is updated.
// Return -1 when file cannot be opened
// Return 0 upon success
int count_page(Node *dict[], int id) {
    char pth[MAX_PATH_LENGTH];
    sprintf(pth, "data/html/%d.html", id);
    char *html;
    if (!(html = load_html(pth)))
        return -1;
    // Remove all tags and javascripts
    textualize(html);
    char *s, *t = html;
    while ((s = strsep(&t, " ")))
        if (*s) {
            char *w = malloc(MAX_WORD_LENGTH);
            strcpy(w, s);
            count(dict, w, id);
        }
    return 0;
}

// Serialize an indexer dictionary
void save_dict(Node *dict[]) {
    int count;
    char s[MAX_INDEX_LENGTH];
    FILE *f = fopen("data/index.dat", "w");
    Node **counter;
    for (int i = 0; i < MAX_SLOT; i++)
        if (dict[i])
            for (Node *w = dict[i]; w; w = w->next) {
                counter = (Node **)w->value;
                // `count` stores the # of pages containing word `w`
                count = 0;
                memset(s, 0, sizeof s);
                for (int j = 0; j < MAX_SLOT; j++)
                    if (counter[j])
                        for (Node *p = counter[j]; p; p = p->next) {
                            count++;
                            // s = " id1 count1 id2 count2 ..."
                            // s[0] = ' '
                            sprintf(s, "%s %s %d", s, p->key, *(int *)p->value);
                        }
                // "word page_count id1 count1 id2 count2...\n"
                fprintf(f, "%s %d%s\n", w->key, count, s);
            }
    fclose(f);
}

// Create a dictionary from a saved index
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
//        puts(buf);
        t = buf;
        // `s` = word
        s = strsep(&t, " ");
        w = malloc(MAX_WORD_LENGTH);
        strcpy(w, s);
//        puts(w);
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
//            puts(id);
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


int main() {
    Node **dict = create_dict();
    for (int i = 0;;i++)
        if (count_page(dict, i) == -1)
            break;
    save_dict(dict);
    free_dict(dict, 2);
//    dict = load_dict();
//    save_dict(dict);
//    free_dict(dict, 2);
}


