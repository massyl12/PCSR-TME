#include "Banque.h"
#include <chrono>
#include <thread>
#include <cstdlib>
#include <iostream>
/*Question 2 oui car les données sont MT-safe dans compte*/
using namespace std;

const int NB_THREAD = 10;
const size_t NB_Compte = 20;
const size_t NB_TRANSACTION = 1000;

void transaction(size_t nbcompte, pr::Banque &B) {
	cout<< "Creation de la transaction" <<endl;
    for (size_t it = 0; it < NB_TRANSACTION; ++it) {
        size_t i = rand() % nbcompte;
        size_t j = rand() % nbcompte;
        int m = rand() % 99 + 1;

        //B.transfert(i, j, m);
		B.transfert_with_mutex(i, j, m); //on a un deadlock car on utilise le mutex d'un compte mais pour crediter le compte on utilise ce même mutex
        this_thread::sleep_for(chrono::milliseconds(rand() % 20));
    }
	cout<< "fin de creation de la transaction" <<endl;
}

int main () {
    pr::Banque B(NB_Compte, 100);
    vector<thread> threads;
    threads.reserve(NB_THREAD);

    for(size_t i = 0; i < NB_THREAD; ++i) {
        threads.emplace_back(thread(transaction, NB_Compte, std::ref(B)));
    }
   

    for (auto &t : threads) {
        t.join();
    }

    thread test(&pr::Banque::comptabiliser, ref(B), 100);

    test.join();

    /*Question 7 et 8 Bilan comptable faux : attendu 100 obtenu : 2000
    */
    return 0;
}
