#include <cstring>
#include <iostream>
#include <string>

#include "List.h"

int main() {
  std::string abc = "abc";
  char *str = new char[4];
  str[0] = 'a';
  str[1] = 'b';
  str[2] = 'c';
  // FAUTE : char * doit terminer par \0
  str[3] = '\0';
  // FAUTE : overflow avec size_t quand 0 - 1 dans la boucle
  int i = 0;

  if (strcmp(str, abc.c_str()) == 0) {
    std::cout << "Equal !";
  }

  pr::List list;
  list.push_front(abc);
  list.push_front(abc);

  std::cout << "Liste : " << list << std::endl;
  std::cout << "Taille : " << list.size() << std::endl;

  // Affiche à l'envers
  for (i = list.size() - 1; i >= 0; --i) {
    std::cout << i << std::endl;
    std::cout << "elt " << i << ": " << list[i] << std::endl;
  }

  // FAUTE : pas d'alloc dynamique
  // liberer les char de la chaine
  // for (char *cp = str; *cp; cp++) {
  //   delete cp;
  // }
  // et la chaine elle meme
  // FAUTE : str est un tab
  delete[] str;
}
