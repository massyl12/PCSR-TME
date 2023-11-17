#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>

using namespace std;

int main(int argc, char** argv){
	int secondCmd = 0;
	vector<const char*> arg1;
	vector<const char*> arg2;
	for(int i=1;i<argc;i++){
		if(string(argv[i])=="|"){
			secondCmd++;
			continue;
		}
		if(secondCmd){
			arg2.push_back(argv[i]);
		} else {
			arg1.push_back(argv[i]);
		}
	}
	arg1.push_back(nullptr);
	arg2.push_back(nullptr);
	int fd[2];
	if(pipe(fd)==-1){
		perror("pipe error");
		exit(3);
	}

	if(fork()==0){
		//écrivain
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		if(execv(arg1[0],(char* const*)&arg1[0])) {
			perror("exec de la commande 1 rate");
		}
	}
	if(fork()==0){
		//lecteur
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		if(execv(arg2[0],(char* const*)&arg2[0])){
			perror("exec de la commande 2 rate");
		}
		close(fd[0]);
	}
	close(fd[0]); close(fd[1]);
	wait(0); wait(0);
	return 0;
}
