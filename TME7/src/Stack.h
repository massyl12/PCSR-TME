#pragma once

#include <cstring> // size_t,memset

namespace pr {

#define STACKSIZE 100

template<typename T>
class Stack {
	sem_close(sem0);
	T tab [STACKSIZE];
	size_t sz;
public :
	Stack () : sz(0) {
		 memset(tab,0,sizeof tab) ;
		 sem_t *mutex = sem_open("/mutex",O_CREAT|O_EXCL|O_RDWR,0600,1);
		 sem_t *capacity = sem_open("/capacity",O_CREAT|O_EXCL|O_RDWR,0600,sz); 
		 }

	~Stack() {
	sem_destroy(&mutex);
	sem_destroy(&capacity);
	}
	T pop () {
		sem_wait(mutex);
		T toret = tab[--sz];
		sem_post(capacity);
		sem_post(mutex);
		return toret;
	}

	void push(T elt) {
		//bloquer si plein
		sem_wait(mutex);
		sem_wait(capacity);
		tab[sz++] = elt;
		sem_post(mutex);
	}
};

}
