#pragma once

#include <cstring> // size_t,memset
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
namespace pr {

#define STACKSIZE 100

template<typename T>
class Stack {
	T tab [STACKSIZE];
	size_t sz;
	sem_t mut;
	sem_t full;
	sem_t empty;
	public :
	Stack () : sz(0) {
		memset(tab,0,sizeof tab) ;
		sem_init(&mut,1,1);
		sem_init(&full,1,0);
		sem_init(&empty,1,STACKSIZE);
	}

	~ Stack() {
		sem_destroy(&mut);
		sem_destroy(&full);
		sem_destroy(&empty);
		delete [] tab;
	}


	T pop () {
		// bloquer si vide
		sem_wait(&full);
		sem_wait(&mut);
		T toret = tab[--sz];
		sem_post(&mut);
		sem_post(&empty);
		return toret;
	}

	void push(T elt) {
		//bloquer si plein
		sem_wait(&empty);
		sem_wait(&mut);
		tab[sz++] = elt;
		sem_post(&mut);
		sem_post(&full);
	}
};

}
