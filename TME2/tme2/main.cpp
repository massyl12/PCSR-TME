#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>

int main () {
    using namespace std;
    using namespace std::chrono;

    ifstream input = ifstream("./WarAndPeace.txt");

    auto start = steady_clock::now();
    cout << "Parsing War and Peace" << endl;

    // vector
    std::vector<pair<string,int>> v = {};
    std::vector<string> pattern = {"war","peace","toto"};

    size_t nombre_lu = 0;
    // prochain mot lu
    string word;
    // une regex qui reconnait les caractères anormaux (négation des lettres)
    regex re( R"([^a-zA-Z])");
    int egale;
    while (input >> word) {
        // élimine la ponctuation et les caractères spéciaux
        word = regex_replace ( word, re, "");
        // passe en lowercase
        transform(word.begin(),word.end(),word.begin(),::tolower);

        // word est maintenant "tout propre"
        if (nombre_lu % 100 == 0){
            
            // on affiche un mot "propre" sur 100
            //cout << nombre_lu << ": "<< word << endl;
        }
        egale=0;
        for (int i = 0; i < v.size(); i++)
            if (!word.compare(v[i].first)) { // si les mots sont egaux
                v[i].second++;
                egale = 1;
                break;
            }
            
        if (!egale){
            
            v.push_back({word,1});
        }
            

        nombre_lu++;
    }
    

    cout << "Finished Parsing War and Peace" << endl;
    
    for(int i=0;i<v.size();i++){
        if(v[i].first == "war"|| v[i].first == "peace" || v[i].first == "toto"){
            cout << v[i].first << ":" << v[i].second<<endl;
        }
    }
    auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
    cout << "Found a total of " << v.size() << " unique words" << endl;
    
    input.close();


    return 0;
}



