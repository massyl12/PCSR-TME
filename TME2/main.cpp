#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <utility>

int main () {
	using namespace std;
	using namespace std::chrono;
	vector<pair<string, size_t>> mots;
	ifstream input = ifstream("/users/Etu9/28711949/git/PSCR-TME/TME2/WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;
	size_t isinlist;
	size_t motsz = 0;
	//size_t nombre_lu = 0;
	// prochain mot lu
	string word;

	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		isinlist = 0;
		for(size_t i = 0; i < mots.size(); ++i){
			if(mots.at(i).first == word){
				isinlist = 1;
				mots.at(i).second++;
				break;
			}
		}
		
		if(isinlist == 0){
			pair<string, size_t> tmp;
			tmp.first = word;
			tmp.second = 1;
			mots.push_back(tmp);
		}
		isinlist = 0;
		
		// word est maintenant "tout propre"
		/*
		if (mots.size() != motsz && !(mots.size() % 100))
			// on affiche un mot "propre" sur 100
			cout << mots.size() << ": "<< mots.at(mots.size()-1).first << endl;
		//nombre_lu++;
		*/
		motsz = mots.size();
		for(size_t i = 0; i < mots.size(); ++i){
    		cout << mots.at(i).first << " : " << mots.at(i).second <<endl; 
		}
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << motsz << " words." << endl;

    return 0;
}


