#pragma once
#include <cstddef>
#include <ostream>

namespace pr {
class String {
  const char *str;
  friend std::ostream &operator<<(std::ostream &, const String &);
  friend bool operator==(const String &a, const String &b);
  friend bool operator!=(const String &a, const String &b);

 public:
  String(const char *);
  String(const String &s);
  ~String();
  size_t length() const;
  bool operator<(const String &b) const;
  bool operator>(const String &b) const;
};
std::ostream &operator<<(std::ostream &, const String &);
bool operator==(const String &a, const String &b);
bool operator!=(const String &a, const String &b);
}  // namespace pr
