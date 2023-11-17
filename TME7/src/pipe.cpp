#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include<iostream>
#include <sys/wait.h>

int main(int argc, char **argv){
    int fd1[2];

    pid_t pid_fils;

    //On part du principe qu'il y'a que deux commandes
    //pour stocker les arguments
    char *cmd1[argc];
    char *cmd2[argc];

    for (int i = 0; i < argc; ++i) {//comme tous les champs de cmd sont a null pas besoin de le gerer pour excv
        cmd1[i] = NULL;
        cmd2[i] = NULL;
    }
    bool swtch = false;
    int i = 0;
    int j = 0;
    for(; i < argc ; i++){
       if (strcmp(argv[i],"|") == 0){
        swtch = true;
        j = i;
       }
       if(swtch){
        cmd2[i-j] = argv[i];
       }
       cmd1[i] = argv[i];
    }
    //creation de deux pipes 
    if (pipe(fd1) == -1) {
        perror("pipe");
        exit(1);
    }

    if (pid_fils = fork() == -1){
        perror("fork");
        exit(2);
    }

    if (pid_fils == 0){
        dup2(fd1[1],STDIN_FILENO); //On redirige la sortie du pipe vers l'entrée standard du fils 
        close(fd1[0]);
        close(fd1[1]);
        if (execv (cmd2[0],cmd2) == -1) {
            perror ("execl"); exit (3);
        }
    }
    else{
        dup2(fd1[0],STDOUT_FILENO); //On redirige l'entrée du pipe vers la sortie standard du pére 
        close(fd1[0]);
        close(fd1[1]);
        if (execv (cmd1[0],cmd1) == -1) {
            perror ("execl"); exit (3);
        }
    }

    wait(NULL);

}