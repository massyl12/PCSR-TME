#include "strutil.h"

#include <cstdlib>
#include <cstring>

namespace pr {

size_t length(const char *s) {
  const char *ptr = s;
  while (*(++ptr))
    ;
  return ptr - s;
}
char *newcopy(const char *s) {
  char *cpy;
  // cpy = new char[length(s) + 1];
  cpy = (char *)malloc(length(s) + 1);
  char *ptr = cpy;
  while (*s) {
    *cpy++ = *s++;
  }
  *cpy = '\0';
  return ptr;
}
char *newcpy(const char *s) {
  size_t len = length(s);
  char *res = new char[len + 1];
  memcpy(res, s, len + 1);
  return res;
}
int compare(const char *s1, const char *s2) {
  while (*s1 == *s2 && *(s1++) && *(s2++))
    ;
  return (*s1 - *s2);
}
}  // namespace pr
