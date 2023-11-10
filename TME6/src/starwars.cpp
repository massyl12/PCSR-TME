#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "rsleep.h"

using namespace std;
int health;





void set_handler(int sig, void (*handler)(int)) {
    struct sigaction sa = {0};
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(sig, &sa, NULL);
}
void handler_SIGINT(int sig){

    health-=1;
    if(health == 0){
        cout<<getpid()<<" process will die"<<endl;
        _exit(1);
    }
    cout<<health << " left for "<<getpid()<<endl;
}
void handler_Defense_Luke(int sig){
     cout<<"Coup paré "<<endl;
}

void attaque(pid_t adversaire){
    cout<<getpid()<<" will attack "<<adversaire<<endl;
    int res;
    set_handler(SIGINT,handler_SIGINT);

    res = kill(adversaire,SIGINT);            //Kill return 0 if the process pid is  in stat != NULL (SSLEEP,SRUN,SZOMBIE)
    
    if(res!=0){
        
        cout<<getpid()<<" WON "<<endl;
        _exit(0);
    } 

    randsleep();
}

void defense(){
    set_handler(SIGINT,SIG_IGN);
    randsleep();
}

void defense_Luke(){
    //Mask the signal SIGINT
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask,SIGINT);
    sigprocmask(SIG_BLOCK,&mask,nullptr);

    //Define the handler for signal SIGINT 
    set_handler(SIGINT,handler_Defense_Luke);

    randsleep();
    sigdelset(&mask,SIGINT);
    if(getppid()!=1){           //If Vador dies, no other process will send a signal so Luke will wait here forever 
        sigsuspend(&mask);
    }
    
    //It's not fair anymore because  Luke is going to wait, block himself here until he received a signal so there is only a 
    //few(near to 0) chance that Vador will attack Luke while he is in attack mode
    
}

void combat(pid_t adversaire,void(*defense)()){
    
    while(1){

        defense();
        waitpid(-1,nullptr,WNOHANG);       //Wait for any child, and return immediatly if no child exited 
        //If the father exited, it will be his father who is going to do a wait so the father will switch from SZOMBIE to NULL so kill will return a value != 0
        //If waitpid waited the son, the son will switch from SZOMBIE into null so kill will return a value != 0
        attaque(adversaire);

    }
}


int main(){
    srand(time(0));
    pid_t pidVador = getpid();
    pid_t pidLuke;

    cout<<"Pid Vador : "<<pidVador<<endl;
    
    health = 3;
    //Just in case one of Vador or Luke is stuck and didn't have enough time to defend himself
    set_handler(SIGINT,SIG_IGN);

    pidLuke = fork();
    if(pidLuke==0){
        cout<<"Pid Luke : "<<getpid()<<endl;
        combat(pidVador,defense_Luke);
    }
    else{
        combat(pidLuke,defense);
    }
    return 0;
}