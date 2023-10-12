#include <iostream>
#include "..\include\String.hpp"

int main() {
    pr::String x("Le penseur");
    std::cout << "La taille de la chaine est " <<  x.length() << "\n";

    pr::String x2;
    x2.newcopy("oui"); // Utilisez la fonction newcopy pour créer une nouvelle chaîne

    return 0;
}
