#include "Compte.h"

using namespace std;

namespace pr {
void Compte::crediter (unsigned int val) {
	//unique_lock<mutex> g(m);
	unique_lock<recursive_mutex> g(m);
	solde+=val ;
}
bool Compte::debiter (unsigned int val) {
	//unique_lock<mutex> g(m);
	unique_lock<recursive_mutex> g(m);
	bool doit = solde >= val;
	if (doit) {
		solde-=val ;
	}
	return doit;
}
int Compte::getSolde() const  {
	// unique_lock<mutex> g(m);
	unique_lock<recursive_mutex> g(m);
	return solde;
}
// NB : vector exige Copyable, mais mutex ne l'est pas...
Compte::Compte(const Compte & other) {
	other.m.lock();
	solde = other.solde;
	other.m.unlock();
}

	void Compte::lock() const{
		m.lock();

	}
	void Compte::unlock() const{
		m.unlock();
	}
	bool Compte::trylock() const{
		return m.try_lock();
	}

}

/*Question 6
Il y'a un problème : lorsque on prend deux comptes i,j et que 
deux threads font une transaction de i vers j et de j vers i.
Ceci à pour effet de faire faire un deadlock, en effet  
si le mutex de i se fait bloquer par debiter
et si le mutex de j se fait bloquer par debiter
au credit on aura un dead_lock
pour regler ce soucis 
*/