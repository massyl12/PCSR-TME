#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sys/mman.h>
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
		cout << c << flush ;
	}
}

int main (int argc, char* argv[]) {

	int N = atoi(argv[1]);
	int M = atoi(argv[2]);
	cout<<"N = "<<argv[1]<<" et M = "<<argv[2]<<endl;
	int fd;
	Stack<char> *s;
	if ((fd = shm_open("/monshm", O_RDWR | O_CREAT, 0600)) == -1) {
		perror("shm_open");
		exit(1);}

	if (ftruncate(fd, sizeof(Stack<char>)) == -1) {
		perror("ftruncate");
		exit(1);}
	void *mapped_mem = mmap(0, sizeof(Stack<char>), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_mem == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 2;
    }

    // Utiliser un placement `new` pour initialiser un objet Stack<char>
    s = new (mapped_mem) Stack<char>();

	for(int i = 0; i < N; ++i)
	{ 
		pid_t pp = fork();
		if (pp==0) {
			producteur(s);
			exit(0);
		}
	}

	for(int j = 0; j < M; ++j)
	{
		pid_t pc = fork();
		if (pc==0) {
			consomateur(s);
			exit(0);
		}
	}

	for(int k = 0; k < N+M; ++k)
		wait(0);
		
	
	delete s;
	return 0;
}

