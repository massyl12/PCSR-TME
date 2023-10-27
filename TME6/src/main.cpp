#include "combat.h"

using namespace pr;

//I am Vador
int main(){
	pid_t luke = fork();

	if(luke==0){
		combat(getppid());
	} else {
		combat(luke);
	}
	return 0;
}
