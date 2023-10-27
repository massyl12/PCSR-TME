#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main2 () {
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;
	int i,j;
	int cpt=1;
	for (i=1, j=N, cpt = 1; i<=N && j==N && fork()==0 ; i++ ) {
		cpt++;
		std::cout << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			cpt++;
			if ( fork() == 0) {
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
				exit(0);
			}
		}
	}
	for(int l = 0; l < min(i,j); l++){
		if (wait(0) == -1){
			cout << "J'ai trop attendu =(" << i << j << endl;
		}
//		wait(nullptr);
	}
	if (wait(0) != -1){
		cout << "J'ai pas assez attendu =(" << getpid() << endl;
	}
	return 0;
}
