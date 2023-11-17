#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>


using namespace std;
using namespace pr;

#define N 5
#define M 6


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

	for(int i=0;i<N;i++){
		pid_t pp = fork();
		if (pp==0) {
			producteur(s);
			return 0;
		}
	}

	for(int j=0;j<M;j++){
		pid_t pc = fork();
		if (pc==0) {
			consomateur(s);
			return 0;
		}
	}

	for(int i=0;i<N+M;i++)
		wait(0);

	delete s;
	return 0;
}

