#include "Banque.h"

using namespace std;

const int NB_THREAD = 10;

bool transfer(int idDebit, int  idCredit, size_t val){	

}
int main () {
	vector<thread> threads;
	threads.reserve(NB_THREAD);

	for(size_t i = 0; i< NB_THREAD; ++i){
		threads.push_back(thread());

	}
	for (auto & t : threads) {
		t.join();
	}

	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
