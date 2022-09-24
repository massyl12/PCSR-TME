#include <iostream>

#include "strutil.h"

int main1() {
  const char *str = "Hello World";
  char *s = pr::newcpy(str);
  std::cout << "Str1 : " << str << "; Len = " << pr::length(str)
            << "@ = " << (void *)str << "\n";
  std::cout << "Str2 : " << s << "; Len = " << pr::length(s)
            << "@ = " << (void *)s << std::endl;
  delete[] s;
  return 0;
}
