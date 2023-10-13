#include "Banque.h"
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;
using namespace pr;

const int NB_THREAD = 10;

void transfertloop(Banque &b){

	for (int k = 0; k<1000000;k++){
		int i = std::rand() % 200;
		int j;
		while ((j = std::rand() % 200)==i);
		int m = std::rand() % 99 + 1;
		b.transfert(i, j, m);
		cout<<"Transfert d'un montant de "<<m<<" de "<<i<<" vers "<<j<<endl;
		//int sleep_time = std::rand() % 20;
		//this_thread::sleep_for(chrono::milliseconds(sleep_time));
	}

}

void comptabiliser2 (Banque &b) {
	for (int k = 0; k<1000000;k++){
		cout<<"Debut comptabiliser "<<k<<endl;
		b.comptabiliser(1000*200);
		cout<<"Fin comptabiliser"<<endl;
		this_thread::sleep_for(chrono::milliseconds(1));
	}
}

int main () {

	std::srand(std::time(nullptr));

	vector<thread> threads;
	// TODO : creer des threads qui font ce qui est demandé
	Banque *b = new Banque(200, 1000);

	/* for (int i = 0; i < NB_THREAD; i++){
		cout<<"Création du thread "<<i<<endl;
		threads.emplace_back(transfertloop, std::ref(*b));
	} */
	threads.emplace_back(comptabiliser2, std::ref(*b));

	for (auto & t : threads) {
		t.join();
	}

	// TODO : tester solde = NB_THREAD * JP
	return 0;
}

