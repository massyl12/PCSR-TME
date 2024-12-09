#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include "rsleep.h"

// exo 1.3 combat de signaux
//Question 5
//Pour obtenir des tirages qui sont différents à chaque lancement on utilise srand() avec time et le pid 
// cdla garantit une graine unique pour chaque processus
int vie = 3; //
//un handler qui affiche "coup paré" 
void handler_luke(int signum){
    if (signum == SIGINT) {
        std::cout << "Processus "<<getpid()<<" a donné le coup paré" << std::endl;
    }
}

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
        std::cout<<"l'adversaire " << adversaire<<" est mort"<<std::endl;
        exit(0);
    }
    // dormir entre 0.3 - 1 seconde
    randsleep() ;
}

void defense_luke() {
    //positionner un handler qui affiche "coup paré" avec sigaction
    sigset_t sig_proc;
    struct sigaction action;
    sigaction(SIGINT, &action, NULL);
    sigemptyset(&sig_proc);
    action.sa_mask=sig_proc;
    action.sa_flags=0;
    action.sa_handler = handler_luke;
    sigaction(SIGINT, &action,NULL);

    //masquer les signaux avec sigprocmask
    sigaddset(&sig_proc, SIGINT);
    sigprocmask(SIG_SETMASK, &sig_proc, NULL); // Bloquer SIGINT

    // Dormir entre 0.3 - 1 seconde
    randsleep();

    // invoquer sigsuspend pour tester si une attaque a eu lieu, et donc afficher le message "coup
    //paré" si le signal a été reçu.
    sigfillset (&sig_proc);
    sigdelset (&sig_proc, SIGINT);
    sigsuspend(&sig_proc);

}
void defense_vador(){
    signal(SIGUSR1,SIG_IGN);
    // dormir entre 0.3 - 1 seconde
    randsleep() ;
}
void combat(pid_t adversaire, pid_t pid_luke) {
    while (1) {
        if (getpid() == pid_luke) {
            // Le processus courant est Luke
            defense_luke();
        } else {
            // Le processus courant est Vador
            defense_vador();
        }
        attaque(adversaire);
    }
}


int main () {
    pid_t pid_luke;
    pid_t pid = fork();

    if (pid == 0) { // Processus fils Luke
        std::cout<<"le processus fils pid = "<<getpid()<<std::endl;
        pid_luke = getpid();
        srand(time(NULL) + getpid());
        combat(getppid(), pid_luke);
    } else { // processus pere Vador 
        std::cout<<"le processus pere pid = "<<getpid()<<std::endl;
        pid_luke = pid;
        srand(time(NULL) + getpid());
        combat(pid, pid_luke);
    }
    return 0;
}
//Question 6  : le combat est il équitable? 
// Non la défense est réussie à chaque fois qu'un processus est en phase de défense.