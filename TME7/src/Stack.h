#pragma once

#include <cstring> // size_t,memset

namespace pr {

#define STACKSIZE 100

template<typename T>
class Stack {
	T tab [STACKSIZE];
	size_t sz;
	sem_t mutex;
	sem_t sempop;
	sem_t sempush;
public :
	Stack () : sz(0) {
		 memset(tab,0,sizeof tab) ;
		 //int sem_init(sem_t *sem, int pshared, unsigned int value); https://manpages.ubuntu.com/manpages/xenial/fr/man3/sem_init.3.html

		 /*Ici on déclare 3 semaphores
		 1 pour jouer le rôle de mutex, les 2 autres sémaphore pour le push et le pop
		 */ 
		 sem_init(&mutex, 1, 1);
		 sem_init(&sempush, 1, STACKSIZE);
		 sem_init(&sempop, 1, 1, 0)
		 }

	~Stack() {
			sem_destroy(&mutex);
			sem_destroy(&sempush);
			sem_destroy(&sempop);

	}
	T pop () {
		sem_wait(&sempop);
		//proteger la section critique 
		sem_wait(&mutex);
		T toret = tab[--sz];
		sem_post(&mutex);
		sem_post(&sempush);
		return toret;
	}

	void push(T elt) {
		//bloquer si plein
		sem_wait(&sempush);
		//proteger la section critique 
		sem_wait(&mutex);
		tab[sz++] = elt;
		sem_post(&mutex);
		sem_post(&sempop);
	}
};

}
