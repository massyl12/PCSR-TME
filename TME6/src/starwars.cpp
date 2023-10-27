#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "rsleep.h"
using namespace std;
int health;


void handler_SIGINT(int sig){
    health-=3;
    if(health==0){
        cout<<"The process will termine "<<endl;
        _exit(1);
    }
    else{
        cout<<"You have "<<health<<" left"<<endl;
    }
}


void attaque(pid_t adversaire){
    int ret_kill;
    struct sigaction sa={0};
    sa.sa_handler = &handler_SIGINT;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags=0;
    sigaction(SIGINT,&sa,NULL);

    ret_kill=kill(adversaire,SIGINT);
    if(ret_kill==-1){
        cout<<"You win !!"<<endl;
        _exit(0);
    }
    randsleep();
}


void defense(){
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sa.sa_flags=0;
    sigaction(SIGINT,&sa,NULL);
}

void combat(pid_t adversaire){

    while(1){
        defense();
        attaque(adversaire);
    }
}



int main(){

    pid_t pidVador = getpid();
    pid_t pidLuke;
    health = 3;
    pidLuke=fork();
    if(pidLuke==0){
        combat(pidVador);
    }
    else{
        combat(pidLuke);
        wait(NULL);
    }
    return 0;
}