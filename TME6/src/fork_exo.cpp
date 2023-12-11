#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

/*question 1 : On engendre 10 processus 

main pid=18166
pid=18167 ppid=18166 i:j 1:3
pid=18168 ppid=18167 i:j 1:0
pid=18169 ppid=18167 i:j 2:3
pid=18170 ppid=18169 i:j 2:0
pid=18171 ppid=18169 i:j 2:0
pid=18172 ppid=18169 i:j 3:3
pid=18173 ppid=18172 i:j 3:0
pid=18174 ppid=18172 i:j 3:0
pid=18175 ppid=18172 i:j 3:0

*/


int main () {
	int cpt = 0;
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;
	for (int i=1, j=N; i<=N && j==N ; i++ ) {
		if (fork() == 0) {
			cpt = 0;
		} else {
			cpt++;
			break;
				}	
		std::cout << "pid=" << getpid() << " ppid=" << getppid() << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			cpt++;
			if ( fork() == 0) {
				cpt = 0;
				j=0;
				std::cout << "pid=" << getpid() << " ppid=" << getppid() << " i:j " << i << ":" << j << std::endl;
			}else{
				cpt++;
			}
		}
	}
	for (size_t i = 0; i<cpt; i++){
		wait(NULL);
	}
	return 0;
}
