/* Hash function for strings.
 * Taken from http://www.cse.yorku.ca/~oz/hash.html
 */

#include <string.h>

//! this one is called djb2
unsigned long hash(const char* str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++) != 0)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}
