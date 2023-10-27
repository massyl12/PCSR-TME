#ifndef __COMBAT_H__
#define __COMBAT_H__

#include <stdlib.h>
#include <sched.h>
#include <signal.h>
#include "rsleep.h"
#include <iostream>

int healthPoints = 3;

namespace pr{
	void attaque (pid_t adversaire);
	void defense();
	void combat(pid_t adversaire);
}

void handler(int sig){
	healthPoints--;
}

void pr::attaque(pid_t adversaire){
	//handle attack if i got signal
	signal(SIGINT, handler);
	std::cout << getpid() << " : "
			"Points de vie : " << healthPoints << std::endl;
	if(healthPoints==0){
		std::cout << getpid() << " : I'm dead " << std::endl;
		exit(0);
	}

	//attack !
	if(kill(adversaire,SIGINT)==-1){
		exit(0);
	}
	randsleep();
}

void pr::defense(){
	signal(SIGINT, SIG_IGN);
	randsleep();
}

void pr::combat(pid_t adversaire){
	while(true){
		pr::defense();
		pr::attaque(adversaire);
	}
}

#endif
