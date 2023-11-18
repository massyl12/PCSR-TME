#pragma once

#include <cstring> // size_t,memset
#include <semaphore.h>
namespace pr {

#define STACKSIZE 100

using namespace std;
template<typename T>
class Stack {
	T tab [STACKSIZE];
	size_t sz;
	sem_t sem_prod;
	sem_t sem_cons;
	sem_t mutex;

public :
	Stack () : sz(0) { 
		sem_init(&sem_prod,0,STACKSIZE);
		sem_init(&sem_cons,0,0);
		sem_init(&mutex,0,1);
		memset(tab,0,sizeof tab) ;}

	T pop () {
		// bloquer si vide
		sem_wait(&sem_cons);
		sem_wait(&mutex);
		T toret = tab[--sz];
		sem_post(&mutex);
		sem_post(&sem_prod);
		return toret;
	}

	void push(T elt) {
		//bloquer si plein
		sem_wait(&sem_prod);
		sem_wait(&mutex);
		tab[sz++] = elt;
		sem_post(&mutex);
		sem_post(&sem_cons);
	}
};

}
