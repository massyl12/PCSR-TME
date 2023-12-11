#pragma once
#include <cstring>

namespace pr {
    class String {
    private:
        char* str; // Modifiez const char* en char* car vous souhaitez le modifier

    public:
        String(const char* ori = ""); // Constructeur par défaut
        ~String(); // Destructeur pour libérer la mémoire

        size_t length() const; // Modifiez le paramètre pour supprimer la déclaration inutile
        void newcopy(const char* str);
    };
}
