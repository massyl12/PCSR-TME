#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
using namespace std;

void addDifferentWordInVec(vector<string>& vec, const string word){
	size_t i;
	for(i=0;i<vec.size();i++){
		if(vec.at(i)==word){
			break;
		}
	}
	if(i==vec.size()){
		vec.push_back(word);
	}
}

void addNumberWordInVec(vector<pair<string,int>>& vec, const string word){
	size_t i;
	for(i=0;i<vec.size();i++){
		if(vec.at(i).first==word){
			vec.at(i).second+=1;
		}
	}
	if(i==vec.size()){
		vec.push_back(make_pair(word,1));
	}
}

int numberOfWord(const vector<pair<string,int>>& vec, const string word){
	for(pair<string,int> p : vec){
		if(p.first==word){
			return p.second;
		}
	}
	return 0;
}

int main () {
	using namespace std::chrono;

	ifstream input = ifstream("./WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)

	//vecteur qui stocke tous les mots
	vector<string> allWordsVec;
	allWordsVec.reserve(21000);

	//vecteur qui stocke le nombre d'occurences de chaque mots
	vector<pair<string,int>> allWordsOccuVec;
	allWordsOccuVec.reserve(21000);


	regex re( R"([^a-zA-Z])");
	while (input >> word) {	
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		//Ajouter un mot différent dans le vecteur
		// addDifferentWordInVec(allWordsVec,word);
		// addNumberWordInVec(allWordsOccuVec,word);

			size_t i;
	for(i=0;i<allWordsOccuVec.size();i++){
		if(allWordsOccuVec.at(i).first==word){
			allWordsOccuVec.at(i).second+=1;
		}
	}
	if(i==allWordsOccuVec.size()){
		allWordsOccuVec.push_back(make_pair(word,1));
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
	// cout << "Found a total of differents " << allWordsVec.size() << " words." << endl;
	cout << "Found a total of " << numberOfWord(allWordsOccuVec,"war") << " 'war' words." << endl;
	cout << "Found a total of " << numberOfWord(allWordsOccuVec,"peace") << " 'peace' words." << endl;
	cout << "Found a total of " << numberOfWord(allWordsOccuVec,"toto") << " 'toto' words." << endl;

    return 0;
}


