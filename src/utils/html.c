/* General html parsing funtions.
 * The following functions are provided:
 * - Retrieving all valid URLs in a html page
 * - Removing white spaces in a html page
 * - Removing all tags, javascripts, CSS in a html page,
 *   thus leaving only normal texts.
 * - Loading a html page into memory.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "html.h"

/* Get the next URL in a html file

Args:
    html - html file to scan
    url - URL of the html file
    next - next valid URL
    pos - starting position to scan
Return:
    position of the next url
*/
int get_next_url(char *html, const char *url, char *next, int pos) {
    // clean up
    if (!pos)
        remove_white_space(html);
    for (; html[pos]; pos++) {
        if (html[pos] == '<' &&
            (html[pos+1] == 'A' || html[pos+1] == 'a') && html[pos+2] == 'h') {
            char *p1 = strchr(html+pos+1, '='), *p2;
            // several invalid cases
            if (!p1 || *(p1-1) == 'e' || p1 - html - pos > 10)
                continue;
            p1++;
            if (*p1 == '\'' || *p1 == '\"')
                p1++;
            if (*p1 == '.' || *p1 == '#' || !strncmp(p1, "mailto:", 7))
                continue;
            if (!(p2 = strpbrk(p1, "\'\">")))
                continue;
            if (!strncmp(p2-4, ".pdf", 4))
                continue;
            // found a full URL
            if (!strncmp(p1, "http", 4) || !strncmp(p1, "HTTP", 4)) {
                strncpy(next, p1, p2-p1);
                next[p2-p1] = 0;
                return p2 - html + 1;
            }
            int i;
            // found an absolute path
            if (*p1 == '/') {
                for (i = 8; i < strlen(url); i++)
                    if (url[i] == '/')
                        break;
                strncpy(next, url, i);
                next[i] = 0;
                strncat(next, p1, p2-p1);
            } else {
            // found a relative path
                strcpy(next, url);
                i = strlen(next);
                if (next[i-1] != '/') {
                    next[i] = '/';
                    next[i+1] = 0;
                }
                strncat(next, p1, p2-p1);
            }
            return p2 - html + 1;
        }
    }
    // reached eof of html
    return -1;
}


// Convert upper case string to lower case wherever possible
void lower(char *s) {
    for (int i = 0; s[i]; i++)
        if (s[i] < 91 && s[i] > 64)
            s[i] += 32;
}

/* Normalize URL

The normalization contains two major components: first, if the
URL ends with a trailing slash '/' character, this trailing slash
will be removed from the URL; and second, if the URL points to
a file (with an extension), then only certain file extensions are
accepted; currently, acceptable normal file extensions start with
.htm, .HTM, .php, or .jsp.

Args:
    url - url to be normalized
Return:
    validity of the url: 0 = invalid, 1 = valid
*/
int normalize_url(char *url) {
    int len = strlen(url);
    if (url[len-1] == '/') {
        url[len-1] = 0;
        return 1;
    }
    
    int j;
    for (j = len-1; j >= 0; j--)
        if (url[j] == '.')
            break;

    if (strncmp(url+j, ".htm", 4) &&
        strncmp(url+j, ".HTM", 4) &&
        strncmp(url+j, ".php", 4) &&
        strncmp(url+j, ".jsp", 4)
        ) return 0;
    return 1;
}

// Removes white space in strings
void remove_white_space(char *html) {
    char *buffer = malloc(strlen(html)+1);
    int i, j;
    for (i = j = 0; html[i]; i++) {
        if (html[i] <= 32)
            continue;
        buffer[j++] = html[i];
    }
    buffer[j] = 0;
    strcpy(html, buffer);
    free(buffer);
}

// Remove all tags, CSS and java scripts
void textualize(char *html) {
    // p is the new end and q is the scanning pointer
    char *p, *q, *t;
    for (p = html, q = strchr(html, '\n') + 1; *q; q++) {
        if (*q == '<') {
            if (!strncmp(q, "<script", 7))
                q = strstr(q, "</script>");
            if (!strncmp(q, "<style", 6))
                q = strstr(q, "</style>");
            q = strchr(q, '>');
            if (*p != ' ')
                *p++ = ' ';
        } else if (*q == '&') {
            // if no near ';' then treat '&' as normal
            if((t = memchr(q, ';', 10)))
                q = t;
        } else if (*q >= 'a' && *q <= 'z')
            *p++ = *q;
        // Change upper case letters into lower cases
        else if (*q >= 'A' && *q <= 'Z')
            *p++ = *q + 32;
        else
            *p++ = ' ';
    }
    *p = 0;
}

// Load a saved a page into memory
char *load_html(const char *pth) {
    FILE *f;
    if ((f = fopen(pth, "r")) == NULL)
        return NULL;
    char *html = malloc(sizeof(char) * MAX_PAGE_LENGTH);
    memset(html, 0, sizeof(char) * MAX_PAGE_LENGTH);
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), f))
        strcat(html, line);
    fclose(f);
    return html; 
}

/* Test module
int main(int argc, char *argv[]) {
    char *s = "https://web.cs.dartmouth.edu";
    char next[1000];
    FILE *f = fopen("data/html/0.html", "r");
    char html[80000];
    memset(html, 0, sizeof(html));
    char line[1000];
    while (!feof(f)) {
        fgets(line, sizeof(line), f);
        strcat(html, line);
    }
    int pos = 0;
    while ((pos = get_next_url(html, s, next, pos)) != -1) {
        puts(next);
    }
}
*/
/* Test module 2
int main() {
    FILE *f = fopen("../../data/html/115.html", "r");
    char buf[MAX_LINE_LENGTH];
    char html[MAX_PAGE_LENGTH];
    memset(html, 0, sizeof html);
    while (fgets(buf, sizeof buf, f))
        strcat(html, buf);
    textualize(html);
    puts(html);
}
*/
