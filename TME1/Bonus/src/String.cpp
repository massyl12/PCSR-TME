#include "String.hpp"
#include <cstdlib>

namespace pr {

String::String(const char* ori) {
    newcopy(ori); // Utilisez la fonction newcopy pour initialiser str
}

String::~String() {
    delete[] str; // Libérez la mémoire allouée dans le destructeur
}

void String::newcopy(const char* ori) {
    size_t len = std::strlen(ori) + 1;
    str = new char[len]; // Allouez la mémoire pour str

    char* it = str;
    while (*ori) {
        *it = *ori;
        ++it;
        ++ori;
    }
    *it = '\0';
}

size_t String::length() const {
    return std::strlen(str); // Utilisez la fonction std::strlen pour obtenir la longueur de str
}

} // namespace pr
