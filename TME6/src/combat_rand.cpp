#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include "rsleep.h"
// exo 1.3 combat de signaux
//Question 4
//l'aventage de nanosleep c'est que si on a reçu l'interruption par le signal,errno est défini à EINTR
//nanosleep() puisse être appelé à nouveau avec la durée restante.le programme va donc reprendre le sommeil après une interruption
int vie = 3;
void decrementation(int signum) {
    if(signum == SIGINT){
        vie -= 1;
        std::cout << "Processus " << getpid() << " a reçu le signal "  << ",vie restants : " << vie << std::endl;
    }
    if (vie <= 0) {
        std::cout << "Processus " << getpid() << " est mort" <<std::endl;
        exit(1); // Le processus se termine en retournant 1
    }
}
void attaque(pid_t adversaire){
    //gestionnaire pour le singal SIGINT 
    sigset_t sig_proc;
    struct sigaction action;
    sigemptyset(&sig_proc);
    action.sa_mask=sig_proc;
    action.sa_flags=0;
    action.sa_handler = decrementation;
    sigaction(SIGINT, &action,NULL);

    //envoie le signal 
    // si échoue
    if (kill (adversaire, SIGINT) <0){
        std::cout<<"l'adversaire" << adversaire<<"est mort"<<std::endl;
        exit(0);
    }
    // dormir entre 0.3 - 1 seconde
    randsleep() ;
}

void defense(){
    sigset_t sig_proc;
    struct sigaction action;
    sigemptyset(&sig_proc);
    action.sa_mask=sig_proc;
    action.sa_flags=0;
    action.sa_handler = SIG_IGN;
    sigaction(SIGINT, &action,NULL);
    // dormir entre 0.3 - 1 seconde
    randsleep() ;
}

void combat(pid_t adversaire){
    while(1){
        defense();
        attaque(adversaire);

    }

}

int main () {

    pid_t pid = fork();
    if(pid == 0 ){//processus fils Luke
        combat(getppid());
    }
    else{ // processus pere Vador 
        combat(pid);
    }
    return 0;
}