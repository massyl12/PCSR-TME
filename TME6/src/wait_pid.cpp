#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <sys/wait.h>
#include <chrono>
#include <thread>
#include <unistd.h>

// fonction wait till pid :
// suspendre l'exécution de processus appelant 
//jus qu'à il remarque la erminaison de son fils de pid "pid"


//variable indiquant si le temps a expiré 
bool sonFinished = false;
bool isFinished  = false;

//question 7 : wait_till_pid avec wait
int wait_till_pid(pid_t pid){
    int status;
    pid_t fils = wait(&status);
    return fils;
}
//question 8 
//sec : le telps maximum en secondes pour
// l'attente la terminaison de son fils
void handler_child(int){
    std::cout<<"le fils a terminé son processus"<<std::endl;
    sonFinished= true;
    
}
void handler_alarm(int){
    std::cout<<"le délais a expiré"<<std::endl;
    isFinished = true;
}
int wait_till_pid (pid_t pid, int sec){
    //retorune 0 si le délai expire avant la terminaison
    //sinon retourne pid  
    int status;
    auto start_time = std::chrono::steady_clock::now();
    //gestionaire des signaux SIGCHILD et SIGINT
    signal(SIGCHLD,handler_child);
    signal(SIGALRM, handler_alarm);
    //commence à chronometrer le temps 
    alarm(sec);

    //dénifir le struc sigset pour attendre uniquement les SIGALARM et SIGCHD
    sigset_t signals;
    sigfillset(&signals);
    sigdelset(&signals,SIGALRM);
    sigdelset(&signals,SIGCHLD);
     while (true) {
        sigsuspend(&signals);
        if(isFinished == true ){
             alarm(0) ;return 0;
        }
        if(sonFinished == true){
            alarm(0);
            pid_t fils = wait(&status);
            return fils;
        }
    }

}
int main(int argc, char** argv){
    pid_t pid_fils1 = fork(); 
    if(pid_fils1 == 0){
        std::cout<<"Fils : pid = "<<getpid()<<std::endl;
        sleep(2); 
        exit(0); 
    }
    else{
        int pid_fils2 = wait_till_pid(pid_fils1,1);
        if(pid_fils2 == 0){
            std::cout<<"wait_till_pid = "<<pid_fils2<<std::endl;
        }
        else if(pid_fils2 >0){
            std::cout<<"wait_till_pid ="<<pid_fils2<<std::endl;
        }
        else{
            std::cout<<"Error - PID fils n'existe pas "<<std::endl;
        }
    }
    return 0;
}