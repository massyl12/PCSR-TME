#include <iostream>
#include <unistd.h>
#include <vector> 
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
int main () {
	// à faire : un processus attent en trop 
	vector<pid_t> children ; 
	pid_t pid ;
	const int N = 2;
	std::cout << "main pid=" << getpid() << std::endl;
	int i=1;
	int j = N;
	for (; i<=N && j==N ; i++) {
		
		if(fork()==0)
		{
			//std::cout << "je suis un enfant i:j " << i << ":" << j << std::endl;
			
			for (int k=1; k<=i && j==N ; k++) {
			
			// fils
			if ( (pid = fork()) == 0) {
				
				j=0;
				//std::cout << " je suis un petit enfant k:j " << k << ":" << j << std::endl;
				exit(0);

			}
			else{
				std::cout<<"récupéré mon petit fils :"<<pid<<std::endl;
				children.push_back(pid); 

			} //pere 
			
		} }
		else
		{
			break;
		}
		
	}

		
	
// Attendre les petits-enfants
    int status;
    pid_t wpid;
    while (!children.empty()) {
        wpid = waitpid(-1, &status, 0);
        if (wpid > 0) {
            std::cout << "fin de petit fils " << wpid << " avec valeur = " << WEXITSTATUS(status) << endl;
            // Supprimer le processus terminé de la liste
            children.erase(std::remove(children.begin(), children.end(), wpid), children.end());
        }
    }
children.clear();

	if(wait(NULL) == -1){
		cout<<"OK"<<endl;
	}

	return 0;
}
		// nombre de processus crée = N + N! 
