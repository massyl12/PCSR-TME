//
//  main.cpp
//  
//
//  Created by Harena Rakotondratsima on 29/09/2023.
//

#include "main.hpp"
#include "hashtab.hpp"
#include "generic.hpp"
#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <utility>
void inserer_mot(HashMap <string,int>& hash,string word,int* nb_mot){     //donner la reference de l'objet pour que le changement soit effectif
    hash.ensure_capacity();
    int nb_occur;
    const int* v=hash.get(word);
    if(v){                              //Si le mot existe deja dans la hash map
        nb_occur = *v;
        hash.put(word,++nb_occur);
    }
    else{
        
        *nb_mot=*nb_mot+1;
        hash.put(word,1);
    }
}


//cle : mot valeur : nb occurence
int main () {
    using namespace std;
    using namespace std::chrono;
    
    ifstream input = ifstream("../WarAndPeace.txt");
    string s[3]={"war","peace","toto"};
    HashMap <string,int> hash (1000);                   //taille de hashmap de 20400  specification du type de K et V
   
    cout << "Parsing War and Peace" << endl;

    //
    size_t nombre_lu = 0;
    // prochain mot lu
    string word;
    // une regex qui reconnait les caractères anormaux (négation des lettres)
    regex re( R"([^a-zA-Z])");
    auto start = steady_clock::now();
    vector<pair<string,int>> vec;
    int nb_mot_diff=0;
    int cpt = 0;
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
        nombre_lu++;
        inserer_mot(hash,word,&nb_mot_diff);
    }


    cout << "Finished Parsing War and Peace" << endl;
    
    //Looking for word : War, Peace, Toto
    for(int i=0;i<3;i++){
       const int *v = hash.get(s[i]);
        if(v){
            cout <<"For "<<s[i]<< " : "<< *v << endl;
        }
        
        else{
            cout<<"No word : "<<s[i]<<endl;
        }
    }

    auto end = steady_clock::now();
    input.close();
    cout << "Parsing took + Finding war peace toto + counting number of differents words : "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
    cout << "Found a totol of : "<<nb_mot_diff<<" differents words"<<endl;

   
    //Iterating into the hashmap Q5 TME3
    for(auto i = hash.begin();i!=hash.end();++i){   //HashMap<string,int>::iterator  //??? pourquoi i++ ne fonctionne pas????
       // cpt++;
       // cout<<"CPT = "<<cpt<<endl;
        vec.emplace_back(i->Key,i->Value);                      //definir operator -> si je veux utiliser i->Value ou ->Key
    }
    
    
    //Q6 TME3
    sort(vec.begin(), vec.end(), [] (pair<string,int> a, pair<string,int> b) { return b.second < a.second;} );
    
    for(int i = 0;i<10;i++){
        cout << "Word : "<<vec[i].first<<" Number of occurence : "<<vec[i].second<<endl;
    }

    //cout<< "Nb element in vec = "<<vec.size()<<endl;
    
    
    size_t co = count(vec.begin(),vec.end());
    cout<<"Count : << "<<co<<endl;
    return 0;
}



