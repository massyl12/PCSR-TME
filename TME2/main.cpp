#include <chrono>
#include <fstream>
#include <iostream>
#include <regex>
#include <utility>
#include <vector>

int main() {
  using namespace std;
  using namespace std::chrono;

  ifstream input = ifstream("./WarAndPeace.txt");

  auto start = steady_clock::now();
  cout << "Parsing War and Peace" << endl;

  size_t nombre_lu = 0;
  // prochain mot lu
  string word;
  // une regex qui reconnait les caractères anormaux (négation des lettres)
  regex re(R"([^a-zA-Z])");
  vector<pair<string, int>> vec;
  while (input >> word) {
    // élimine la ponctuation et les caractères spéciaux
    word = regex_replace(word, re, "");
    // passe en lowercase
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    auto it = std::find_if(vec.begin(), vec.end(), [&word](const auto& item) {
      return std::get<0>(item) == word;
    });
    if (it != vec.end()) {
      it->second++;
    } else {
      vec.push_back(make_pair(word, 0));
    }
    // word est maintenant "tout propre"
    // if (nombre_lu % 100 == 0)
    //   // on affiche un mot "propre" sur 100
    //   cout << nombre_lu << ": " << word << endl;
    nombre_lu++;
  }
  input.close();

  cout << "Finished Parsing War and Peace" << endl;

  auto end = steady_clock::now();

  auto it = std::find_if(vec.begin(), vec.end(), [&word](const auto& item) {
    return std::get<0>(item) == "war";
  });
  if (it != vec.end()) {
    cout << "Found a total of " << it->second << " occurences of 'war'.\n";
  }

  it = std::find_if(vec.begin(), vec.end(), [&word](const auto& item) {
    return std::get<0>(item) == "peace";
  });
  if (it != vec.end()) {
    cout << "Found a total of " << it->second << " occurences of 'peace'.\n";
  }

  it = std::find_if(vec.begin(), vec.end(), [&word](const auto& item) {
    return std::get<0>(item) == "toto";
  });
  if (it != vec.end()) {
    cout << "Found a total of " << it->second << " occurences of 'toto'.\n";
  } else {
    cout << "Found a total of " << 0 << " occurences of 'toto'.\n";
  }

  cout << "Parsing took " << duration_cast<milliseconds>(end - start).count()
       << "ms.\n";

  cout << "Found a total of " << nombre_lu << " words.\n";

  return 0;
}
