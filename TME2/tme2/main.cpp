#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include "HashMap.h"
int main() {
    using namespace std;
    using namespace std::chrono;

    ifstream input("WarAndPeace.txt");

    auto start = steady_clock::now();
    cout << "Parsing War and Peace" << endl;

    size_t nombre_lu = 0;
    vector<pair<string, int>> mots_occurrences;
    pr::HashMap<string, int> hash(2000); 

    string word;
    regex re(R"([^a-zA-Z])");

    while (input >> word) {
        word = regex_replace(word, re, "");
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (!word.empty()) {
        //     bool found = false;

        //     Recherche manuelle dans le vecteur mots_occurrences
        //     for (auto& e : mots_occurrences) {
        //         if (e.first == word) {
        //             e.second++;  // Si trouvé, incrémenter le compteur
        //             found = true;
        //             break;
        //         }
        //     }

        //     if (!found) {
        //         Si le mot n'est pas trouvé, l'ajouter au vecteur avec une occurrence de 1
        //         mots_occurrences.push_back(make_pair(word, 1));
        //     }
            int* value = hash.get(word);
            if (value) {
                // Si le mot est trouvé, on incrémente le compteur
                hash.put(word, *value + 1);
            } else {
                // Si le mot n'est pas trouvé, on l'ajoute avec une occurrence de 1
                hash.put(word, 1);
            }

        }

        if (nombre_lu % 100 == 0) {
            cout << nombre_lu << ": " << word << endl;
        }
        nombre_lu++;
    }
    input.close();

    cout << "Finished Parsing War and Peace" << endl;

    auto end = steady_clock::now();
    cout << "Parsing took "
         << duration_cast<milliseconds>(end - start).count()
         << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
    //cout << "Found a total of " << mots_occurrences.size() << " unique words." << endl;
    cout << "Found a total of " << hash.size() << " unique words." << endl;
    // Afficher les occurrences des mots spécifiques
    vector<string> mots_recherche = {"war", "peace", "toto"};
    // for (const auto& mot : mots_recherche) {
    //     bool found = false;
    //     for (auto& e : hash) {
    //         if (e.key == mot) {
    //             cout << "The word \"" << mot << "\" appears " << hash.get(e.key) << " times." << endl;
    //             found = true;
    //             break;
    //         }
    //     }
    //     if (!found) {
    //         cout << "The word \"" << mot << "\" does not appear in the text." << endl;
    //     }
    // }
    
    for (const auto& mot : mots_recherche) {
        int* count = hash.get(mot);  // On récupère le pointeur vers la valeur
        if (count) {
            cout << "The word \"" << mot << "\" appears " << *count << " times." << endl;
        } else {
            cout << "The word \"" << mot << "\" does not appear in the text." << endl;
        }
    }
    return 0;
}

