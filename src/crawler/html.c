#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "html.h"

/* Get the next URL in a html file

The main component of the html parser. It can handle normal absolute
and relative URLs found in the <a href=""> tags.

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
            (html[pos+1] == 'A' || html[pos+1] == 'a')) {
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

            

/* Convert upper case string to lower case wherever possible

Args:
    s - string to convert
*/
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

/* Removes white space in strings

Args:
    html - string whose white spaces to be removed
*/
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

/* Test module
int main(int argc, char *argv[]) {
    char *s = "https://web.cs.dartmouth.edu";
    char next[1000];
    FILE *f = fopen("../../data/1.html", "r");
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
