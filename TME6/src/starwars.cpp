#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "rsleep.h"
using namespace std;
int health;

#include <signal.h>

void set_handler(int sig, void (*handler)(int)) {
    struct sigaction sa = {0};
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(sig, &sa, NULL);
}

void handler_SIGUSER1_Vador(int sig){
    cout<<"Vador defeated his son "<<endl;
    _exit(0);
}

void handler_SIGUSER1_Luke(int sig){
    cout<<"Luke defeated his father "<<endl;
    _exit(0);
}

void handler_SIGINT(int sig){
    health -= 1;
    if(health==0){
        cout<<getpid()<<" will termine "<<endl;
    }
    else{
        cout<<getpid()<<" you have "<<health<<" left chance"<<endl;
    }
}

void handler_Luke_Defence(int sig){
    cout<<"Coup paré par Luke , ahah"<<endl;
}

void attaque(pid_t adversaire,char * perso){
    cout<<getpid()<<" will attack "<<adversaire<<endl;
    //cout<<"attacking"<<endl;
    set_handler(SIGINT, handler_SIGINT);
    if(strcmp(perso,"Luke")==0){
        cout<<" here I sleep  pid = "<<getpid()<<endl;         
        sleep(10);
    }
    kill(adversaire,SIGINT);    //ne renvoie pas -1 si le fils est zombie
    randsleep();
}


void defense(){
    //cout<<"defending"<<endl;
    set_handler(SIGINT, SIG_IGN);
    randsleep();                                    //pourquoi quand je ne m'endors pas ici, je ne rentre jamais dans le if pidLuke==0?
}

void defense_Luke(){
    //To define the handler of the defense in case of a signal SIGINT
    set_handler(SIGINT, handler_Luke_Defence);
   

    //To mask the signal SIGINT
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask,SIGINT);
    sigprocmask(SIG_BLOCK,&mask,nullptr);               //plus du tout equitable car Luke mask tous les signaux SIGINT qui n'est pas retabli dans attack

    randsleep();

    //To poll if we received a SIGINT signal
    sigemptyset(&mask);
    sigsuspend(&mask);
}

void combat(pid_t adversaire,void(*defense)(),char *perso){
    cout<<"Combat mon adversaire "<<adversaire<<endl;
    while(1){
        defense();

        attaque(adversaire,perso);

        if(health==0){
            kill(adversaire,SIGUSR1);
            _exit(1);
        }
    }
}



int main(){
    srand(time(0));
    pid_t pidVador = getpid();
    pid_t pidLuke;

    cout<<"Pid Vador : "<<pidVador<<endl;
    
    health = 3;
    //Just in case one of Vador or Luke is stuck and didn't have enough time to defend himself
    set_handler(SIGINT, SIG_IGN);

    pidLuke = fork();
    if(pidLuke==0){
        //When Luke is dying, he is going to send a signal to his father
        set_handler(SIGUSR1, handler_SIGUSER1_Luke);

        //To define the handler of the defense in case of a signal SIGINT      
        set_handler(SIGINT, handler_Luke_Defence);


        combat(pidVador,defense_Luke,"Luke");
        
    }
    else{
        //When Vador is dying, he is going to send a signal to his son
        set_handler(SIGUSR1, handler_SIGUSER1_Vador);

        cout<<"Pid Luke  : "<<pidLuke<<endl;
        combat(pidLuke,defense,"Vador");
        wait(NULL);
    }
    return 0;
}