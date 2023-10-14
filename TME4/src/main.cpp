#include "Banque.h"
#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>
#include <ctime>
using namespace std;

const int NB_THREAD = 10;
#define Ncompte 10
#define SOLDEINIT 100

int main () {
	vector<thread> threads;
    srand(time(0));
    pr::Banque b(Ncompte,SOLDEINIT);
    for(int i = 0; i< NB_THREAD; ++i){
        //passer la fonction membre de Banque en pointeur (adresse), &b parce que dans transfert on a besoin de l'objet *this
        threads.emplace_back(&pr::Banque::tranfert_aleatoire,&b,i);
        cout<<"Thread : "<<i<<" created "<<endl;
    }

    thread comptable(&pr::Banque::comptable_iter,&b,100,SOLDEINIT*Ncompte);
    for (int i = 0;i<threads.size();++i) {
		threads[i].join();
        cout<<"Thread : "<<i<<" joined "<<endl;
	}
    comptable.join();
	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
