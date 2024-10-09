#include "Banque.h"
#include <random>
#include <cstddef>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
using namespace std;

const int NB_THREAD = 10;
const int SOLDEINITIAL = 1000;
namespace pr {
void work(int index, Banque & b){
	std::cout << "started "<< index << endl;
	for(int k = 0; k<1000 ; ++k){
		//Choisir i et j deux indices de comptes aléatoires
		auto i = ::rand() %5;
		auto j = ::rand() %5 ;
		auto m = ::rand() %100 + 1;
		//essayer de transférer le montant m de i à j.
		b.transfert_lock(i,j,m);
		auto r = ::rand() % 21 ; // 0 to 20 ms
		std::this_thread::sleep_for (std::chrono::milliseconds(r));
	}
	std::cout << "finished "<< index << endl;

} 
	
}
int main () {
	vector<thread> threads;
	threads.reserve(NB_THREAD);
	// iniatiliser baqnue 
	pr::Banque b(5,SOLDEINITIAL);
	
	for(int i = 0; i <NB_THREAD ; ++i){
		threads.emplace_back(pr::work,i,std::ref(b));
	}
	
	
	for (auto & t : threads) {
		t.join();
	}

	// TODO : tester solde = NB_THREAD * JP

	return 0;
}
