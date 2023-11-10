#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
using namespace std;
int ret = 0;   //
pid_t wait_till_pid(pid_t pid){

    pid_t child = wait(nullptr);
    while(child != pid && child !=-1){
        child = wait(nullptr);
    }

    if(child == -1) return -1;
    return pid;
}

void set_handler(int sig, void (*handler)(int)) {
    struct sigaction sa = {0};
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(sig, &sa, NULL);
}


void handler_wait(int sig){

    ret = wait(nullptr);
}

void handler_alarm(int sig){
    cout<<" time out "<<endl;
    ret = 0;
}

pid_t wait_till_pid(pid_t pid, int sec){
        
    sigset_t mask;
    sigfillset(&mask);
    set_handler(SIGCHLD,handler_wait);
    set_handler(SIGALRM,handler_alarm);
    sigdelset(&mask,SIGCHLD);
    sigdelset(&mask,SIGALRM);
    //mask every other signal except SIGCHILD and SIGALARM while waiting them
    alarm(sec);
    while(1){
        sigsuspend(&mask);
        if(ret == 0) return 0;
        if(ret == pid ) {
            set_handler(SIGALRM,SIG_IGN);           //To ignore the signal of Alarm
            cout<<"Waited the child process : "<<pid<<endl;
            return pid;

        }
    }
}


int main(){

    pid_t child = fork();

    if(child == 0){
        sleep(3);
        _exit(0);
    }

    wait_till_pid(child,1);  //to generate a time out
    //wait_till_pid(child,10)  //to generate Waited the child process XXXX

    return 0;
}