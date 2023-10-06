#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <string>
#include <forward_list>
#include <algorithm>
using namespace std;

template <typename k, typename v>
class Hashmap {
    struct Entry {
        const k Key;
        v value;
    };
    vector<forward_list<Entry>> Buckets;

public:
    Hashmap(size_t alloc) : Buckets(alloc) {}

    bool put(const k& Key, const v& value) {
        size_t n = std::hash<k>()(Key);
        size_t target = n % Buckets.size();

        for (auto &ent : Buckets[target]) {
            if (ent.Key == Key) {
                ent.value++; // Incrémente la valeur existante.
                return true; // La clé existe déjà, mise à jour de la valeur.
            }
        }

        // La clé n'existe pas, ajoutez une nouvelle entrée avec une valeur de 1.
        Buckets[target].push_front({Key, 1});
        return true;
    }

	const forward_list<Entry>& getBucket(size_t index) const {
        if (index < Buckets.size()) {
            return Buckets[index];
        }
        throw out_of_range("Bucket index out of range");
    }

};


int main () {
	using namespace std;
	using namespace std::chrono;
	
	// vector< std::pair<string,int> > Vector_word;
	Hashmap<string,int> Mymap(10);

	ifstream input = ifstream("./WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
		// int v = 1;
		// for (size_t i=0; i<Vector_word.size();i++){
		// 	if (Vector_word[i].first == word) {
		// 		Vector_word[i].second++;
		// 		v = 0;
		// 		break;
		// 	}
		// } 

		// if (v == 1) Vector_word.emplace_back(word, 1);
		Mymap.put(word,1);
		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;

		nombre_lu++;
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
    // cout << "mot_diff " << ": "<< Vector_word.size() << endl;
    // for (size_t i=0; i<Vector_word.size();i++){
    // 	if (Vector_word[i].first == "war")
    // 		cout << "Occurence War " << ": "<< Vector_word[i].second<< endl;
    // 	if (Vector_word[i].first == "peace")
    // 		cout << "Occurence peace " << ": "<< Vector_word[i].second<< endl;
    // 	if (Vector_word[i].first == "toto")
    // 		cout << "Occurence toto " << ": "<< Vector_word[i].second<< endl;   	
    // } 

	// Afficher le contenu de la Hashmap
	for (size_t i = 0; i < 10; i++) {
    	for (const auto &ent : Mymap.getBucket(i)) {
        	cout << "Key: " << ent.Key << ", Value: " << ent.value << endl;
    	}
	}

    return 0;
}


