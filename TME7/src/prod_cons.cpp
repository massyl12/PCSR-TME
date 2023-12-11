#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sys/mman.h>
#include <sys/stat.h> 
#include <fcntl.h> 

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
		cout <<"oui" << endl;
		cout << c << flush ;
	}
}


std::vector<pid_t> kills;

void ctrlCKill(int sig){
	if (sig == SIGINT){
		for (auto p : kills) {
			kill(p,SIGINT);
		}
	}
}
// pour exec g++ -o mon_programme prod_cons.cpp -pthread -lrt

int main () {
	int fd;
	void* shared_space;
	//catch le ctrl c
	signal(SIGINT,ctrlCKill);

	//Creation de la mémoire partagé
	if ( (fd = shm_open("/segme16",O_CREAT|O_EXCL|O_RDWR,0600) )== -1){
		perror("shm_open");
		exit(EXIT_FAILURE);
	}; 

	//allocation de la zone mémoire
	if (ftruncate(fd, sizeof(Stack<char>))){
		perror("ftruncate");
		exit(EXIT_FAILURE);
	};

	//On est crée la shared memory 
	if ((shared_space = mmap(NULL, sizeof(Stack<char>),PROT_READ | PROT_WRITE,MAP_SHARED,fd, 0)) == MAP_FAILED){
		perror("mmap");
		exit(1);
	}

	//le new (addr) permet d'allouer à une adresse connu c'est le new placement
	Stack<char> *s = new (shared_space) Stack<char>();

	pid_t pp = fork();
	if (pp==0) {
		//fils
		producteur(s);
		return 0;
	}

	pid_t pc = fork();
	if (pc==0) {
		//fils
		consomateur(s);
		return 0;
	}else
		{	
			kills.push_back(pc);//pére
		}

	wait(0);
	wait(0);

	//clean up
	s->~Stack();
	munmap(shared_space,sizeof(Stack<char>));
	close(fd);
	return 0;
}

