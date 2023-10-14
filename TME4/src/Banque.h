#pragma once

#include "Compte.h"
#include <vector>
#include <chrono>

namespace pr {

class Banque {
	typedef std::vector<Compte> comptes_t;
	comptes_t comptes;
//    mutable std::mutex bm;    Q9 mutex entre transfert et comptable pour qu'on ne puisse faire qu'un transfert ou bien un bilan comptable a la fois
public :
	Banque (size_t ncomptes, size_t solde) : comptes (ncomptes, Compte(solde)){
	}
	void transfert(size_t deb, size_t cred, unsigned int val) ;
	size_t size() const ;
	bool comptabiliser (int attendu) const ;
    void tranfert_aleatoire(int index) ;
    void comptable_iter(int nb_iter,int attendu) const;
};

}
