#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;
int main () {
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;
	int nbchild=0;
	for (int i=1, j=N; i<=N && j==N; i++ ) {
		if(fork()!=0){
			nbchild++;
			break;
		}
		nbchild=0;
		std::cout << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			if ( fork() == 0) {
				nbchild=0;
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
			}
			else{
				nbchild++;
			}
		}
	}
	
	for(int l=0;l<nbchild;l++){

		int ret;
		ret=wait(NULL);
		if(ret==-1){
			cout<<"wait problem"<<endl;
		}
	}

	if(wait(NULL)!=-1){
		cout<<"You still have a child, you didn't wait for him "<<endl;
	}
	return 0;
}
