#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include "HashMap.h"

using namespace std;
using namespace pr;

int getOccurence(HashMap<string,int> table , string word){
    int* value = table.get(word);
    if(value){
        return *value;
    }
	return 0;
}

int main () {
	using namespace std::chrono;

	ifstream input = ifstream("/tmp/WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");

    HashMap<string,int> table(30000);

	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;

        int* value = table.get(word);
		if(value==nullptr){
            table.put(word,1);
		} else {
            (*value)++;
		}
	}
	input.close();

	std::vector<pair<string, int>> vectorFromHashMap;
	for (const auto& bucket : table.buckets) {
		vectorFromHashMap.insert(vectorFromHashMap.end(), bucket.begin(), bucket.end());
	}

    std::sort(vectorFromHashMap.begin(), vectorFromHashMap.end(),[] (const pair<string,int> & a, const pair<string,int> & b) {
    	return a.second > b.second ;}
    );

    for(int i=0;i<10;++i){
    	cout << vectorFromHashMap.at(i).first << "----------" << vectorFromHashMap.at(i).second << std::endl;
    }
 	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
    cout << "Found a total of " << table.size() << " differents words in Vector." << endl;
    cout << "Nombre d'occurences du mot war " << getOccurence(table, "war") << endl;
    cout << "Nombre d'occurences du mot peace " << getOccurence(table, "peace") << endl;
    cout << "Nombre d'occurences du mot toto " << getOccurence(table, "toto") << endl;
    return 0;
}


