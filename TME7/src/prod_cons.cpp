#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <vector>


using namespace std;
using namespace pr;

#define N 1
#define M 2
bool b = true;

void producteur (Stack<char> * stack) {
	char c ;
	while (cin.get(c) && b) {
		cout << "prod " << c << endl;
		stack->push(c);
		cout << "prod end" << endl;
	}
}

void consomateur (Stack<char> * stack) {
	while (b) {
		cout << "cons" <<endl;
		char c = stack->pop();
		cout << c << flush ;
	}
}


int main () {
	void* ptr = mmap(NULL, sizeof(Stack<char>),PROT_WRITE|PROT_READ,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	if (ptr == MAP_FAILED) {
	    // Handle the error
	    perror("mmap");
	    exit(EXIT_FAILURE);
	}
	Stack<char> * s = new (ptr) Stack<char>();
	signal(SIGINT,[](int sig){
		b=false;
	});
	vector<pid_t> sons;
	sons.reserve(N+M);
	for(int i=0;i<N;i++){
		pid_t pp = fork();
		if (pp==0) {
			producteur(s);
			return 0;
		} else {
			sons.push_back(pp);
		}
	}

	for(int j=0;j<M;j++){
		pid_t pc = fork();
		if (pc==0) {
			consomateur(s);
			return 0;
		}else {
			sons.push_back(pc);
		}
	}

	while(b){}

	for(int i=0;i<N+M;i++)
		kill(sons[i],SIGINT);

	for(int i=0;i<N+M;i++)
		wait(0);

	munmap(ptr, sizeof(Stack<char>));
	delete s;
	return 0;
}

