#include "String.h"
#include "strutil.h"
#include <iostream>

pr::String getAlpha() {
	char tab[27];
	for (int i = 0; i < 26; ++i) {
		tab[i] = 'a'+i;
	}
	tab[26] = '\0';
	return pr::String(tab);
}

int main() {
  pr::String abc = getAlpha();
  std::cout << abc << std::endl;
  std::cout << (pr::String("afsrasrt") < pr::String("ac")) << std::endl;
  return 0;
}
