#include "String.h"

#include <cstring>

#include "strutil.h"
namespace pr {
String::String(const char *s) { str = newcpy(s); }

String::String(const String &s) { str = newcpy(s.str); }
String::~String() { delete[] str; }

size_t String::length() const {
  const char *ptr = str;
  while (*(++ptr))
    ;
  return ptr - str;
}

std::ostream &operator<<(std::ostream &out, const String &s) {
  out << s.str;
  return out;
}
bool operator==(const String &a, const String &b) {
  return compare(a.str, b.str) == 0;
}
bool operator!=(const String &a, const String &b) {
  return compare(a.str, b.str) != 0;
}
bool String::operator<(const String &b) const {
  return compare(str, b.str) < 0;
}
bool String::operator>(const String &b) const {
  return compare(str, b.str) < 0;
}
}  // namespace pr
