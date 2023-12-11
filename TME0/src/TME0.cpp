//============================================================================
// Name        : TME0.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	int *tab = new int[10];
    for (int i = 0 ; i<10 ; i++)
        tab[i] = i;

    for (int i = 0 ; i<10 ; i++){
        std::cout << *(tab+i) << std::endl;
    }

    for (int i=9; i >= 0 ; i--) {
    	std::cout << *(tab+i) << std::endl;
    	if (tab[i] - tab[i-1] != 1) {
            cout << "probleme !";
        }
    }
    return 0;
}



