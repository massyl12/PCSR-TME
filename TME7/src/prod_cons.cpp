#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sys/mman.h>



using namespace std;
using namespace pr;

void producteur (Stack<char> * stack) {
	cout<<"Here into prod"<<endl;
	char c ;
	while (cin.get(c)) {
		stack->push(c);
	}
}

void consomateur (Stack<char> * stack) {
	cout<<"Here into cons"<<endl;
	while (true) {
		//char c = stack->pop();
		//cout << c << flush ;
	}
}

int main () {
	//For his child, 'space' will be at same memory space (physically) as him when one of them attempt to use it
	//the page table of each process mapping that shared region will have entries pointing to the same physical pages
	void *space = mmap(0,sizeof(Stack<char>),PROT_READ|PROT_WRITE,MAP_ANONYMOUS | MAP_SHARED,-1,0);
	if(space == MAP_FAILED){
		perror("MMAP FAILED");
	}
	//To create the class into the shared space
	Stack<char> * s = new (space) Stack<char>();


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
	/*if(munmap(space,sizeof(Stack<char>)) == -1){
		perror("Munmap failed");
	}*/
	//clang++ -std=c++20 -o prod_cons prod_cons.cpp Stack.h -lrt 
	//delete s;
	return 0;
}

