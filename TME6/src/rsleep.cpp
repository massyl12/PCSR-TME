#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include "rsleep.h"
#include <signal.h>
#include <cstdio>


void randsleep() {
  int r = rand();
  double ratio = (double)r / (double) RAND_MAX;
  struct timespec tosleep;
  tosleep.tv_sec =0;
  // 300 millions de ns = 0.3 secondes
  tosleep.tv_nsec = 300000000 + ratio*700000000;
  struct timespec remain;
  while ( nanosleep(&tosleep, &remain) != 0) { 
    /*
     tant qu'on sleep pas jusqu'au bout on fait boucle, on fait ça car nanosleep peut se faire interrompre par les signaux.
     Or durant l'attaque on veut se faire signaler pour prendre des dégats mais pas forcement ce reveiller.
     On quitte la boucle quand le temps restant = 0   
     */
    tosleep = remain;
  }
}

int pv = 3;
void handler(int sig){
  if (sig == SIGINT){
    pv--;
    printf("AIE il me reste plus que %d points de vie, moi le grand %d ne me laissera pas faire!\n",pv, getpid());
    if (pv == 0) {
      printf("Je meurts mais rappel toi que je suis : %d\n",getpid());
      exit(1);
    }
  }
}

void attaque (pid_t adversaire){
  signal(SIGINT,handler);
  int i = kill(adversaire,SIGINT);
  if (i < 0){
    printf("AHAHA moi %d ai vaincu %d  !!\n",getpid(),adversaire);
    exit(0);
  }
  randsleep();
}

void defense(){
  signal(SIGINT,SIG_IGN);
  randsleep();
}

void combat(pid_t adversaire){
  while (true)
  {
    defense();
    attaque(adversaire);
  }
}

int main(){
  pid_t pere = getpid();
  pid_t fils = fork();
  if (fils == 0){
    srand(fils); //on fait ça pour s'assurer que le pére et le fils ont des graines différents
    combat(pere); //le fils
  }
  else{
    srand(pere);
    combat(fils); //pere
  }

  return 0;
}

/*
Question 6
Le combat serait inéquitable car le fils attendrait juste que le père envoit un signal pour paré.
Il va parer tous les coups
*/