#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>


using namespace std;
using namespace pr;

void producteur (Stack<char> * stack) {
	char c ;
	while (cin.get(c)) {
		stack->push(c);
	}
}

void consomateur (Stack<char> * stack) {
	while (true) {
		char c = stack->pop();
		cout << c << flush ;
	}
}

int main () {
	Stack<char> * s = new Stack<char>();
	/* Créé le segment en lecture écriture */
	sem_t *mutex = sem_open("/mutex",O_CREAT|O_EXCL|O_RDWR,0600,1);
	ftruncate(mutex, sizeof(struct myshm));
	mutex= mmap(NULL, sizeof(struct myshm),PROT_READ | PROT_WRITE,MAP_SHARED,mutex, 0)
	if(pid){
		sem_unlink("/monsem0");
	}

	pid_t pp = fork();
	if (pp==0) {
		producteur(s);
		return 0;
	}

	pid_t pc = fork();
	if (pc==0) {
		consomateur(s);
		return 0;
	}

	wait(0);
	wait(0);

	delete s;
	return 0;
}

