#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr {

void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];
    //unique_lock<mutex> bb(bm);      //Big lock on banque
    // Q6 pour eviter un deadlock, on ordonne les lock de mutex
    if(deb<cred){
        debiteur.lock();
        crediteur.lock();
    }
    else{
        crediteur.lock();
        debiteur.lock();
    }
  
	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
	}
    debiteur.unlock();
    crediteur.unlock();
}
size_t Banque::size() const {
	return comptes.size();
}
bool Banque::comptabiliser (int attendu) const {        //Q7 : oui le thread executant cette fonction sera satisfait avec la synchro actuelle
// car on evite la data race sur les soldes de compte
    //unique_lock<mutex> bb(bm);     big lock on banque
	int bilan = 0;
	int id = 0;
    recursive_mutex temp;
	for (const auto & compte : comptes) {
        //lock every previous account
        compte.lock();
		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
		}
                 
		bilan += compte.getSolde();
		id++;
	}
	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
	}
    //Unlock the lock only after we have done the accountents
    for( const auto & compte : comptes){
        compte.unlock();
    }
	return bilan == attendu;
}
    
    
    void Banque::tranfert_aleatoire(int index){
        int i;
        int j;
        int val;
        int s;
        for(int k = 0;k<1000;++k){
            //generation aleatoire du compte debiteur (i), crediteur (j) , la valeur (val) , le temps de sleep (s)
            i = rand()%(this->size());
            j = rand()%(this->size());
            val = rand()%(100)+1;
            //pas de datarace car Compte::debiter et Compte::crediter sont securiser par un unique_lock
            this->transfert(i,j,val);
            s = rand()%21;
//            cout<<"Thread : "<<index<<" has done a radom transaction and about to sleep "<<endl;
//            this_thread::sleep_for(chrono::seconds(s));
//            cout<<"Thread : "<<index<<" is now awake "<<endl;
        }

    }
    
    
    void Banque::comptable_iter(int nb_iter,int attendu) const{
        bool res;
        for(int i = 0;i<nb_iter;++i){
            res = Banque::comptabiliser (attendu);
            if(!res){
                cout<<"Bilan faux "<<endl;
                break;
            }
            cout<<"Bilan correct "<<endl;
            
        }
        
    }
}
