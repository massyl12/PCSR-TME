#include "Compte.h"

using namespace std;

namespace pr {
void Compte::crediter (unsigned int val) {
    //Q5 le thread se bloque immediatement si on mutex m, il faut faire recursive_mutex m comme ca le thread qui a lock le mutex dans transaction peut aussi lock ce mutex et pas un autre thread
	unique_lock<recursive_mutex> g(m);
	solde+=val ;
}
bool Compte::debiter (unsigned int val) {
    //Q5 le thread se bloque immediatement si on mutex m, il faut faire recursive_mutex m comme ca le thread qui a lock le mutex dans transaction peut aussi lock ce mutex et pas un autre thread
	unique_lock<recursive_mutex> g(m);
	bool doit = solde >= val;
	if (doit) {
		solde-=val ;
	}
	return doit;
}
int Compte::getSolde() const  {
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
}
