#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <chrono>
#include <thread>
// exo 1.3 combat de signaux
//Question 3 
int vie = 3;
void decrementation(int signum) {
    if(signum == SIGUSR1){
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
    signal(SIGUSR1,decrementation);

    //envoie le signal 
    // si échoue
    if (kill (adversaire, SIGUSR1) <0){
        std::cout<<"l'adversaire" << adversaire<<"est mort"<<std::endl;
        exit(0);
    }
    // dormir entre 0.3 - 1 seconde
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.3, 1.0);
    double random_duration = dis(gen);
    std::chrono::duration<double> sleep_duration(random_duration);
    std::this_thread::sleep_for(sleep_duration);

}

void defense(){
    signal(SIGUSR1,SIG_IGN);
    // dormir entre 0.3 - 1 seconde
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.3, 1.0);
    double random_duration = dis(gen);
    std::chrono::duration<double> sleep_duration(random_duration);
    std::this_thread::sleep_for(sleep_duration);
}

void combat(pid_t adversaire){
    while(1){
        defense();
        attaque(adversaire);

    }

}

int main () {

    pid_t pid = fork();
    if(pid == 0 ){ //processus fils Luke
        srand(time(NULL) + getpid()); // pour éviter qu' ils dormment sur les mêmes durées 
        combat(getppid());
    }
    else{ // processus pere Vador 
        srand(time(NULL) + getpid());
        combat(pid);
    }
    
    return 0;
}