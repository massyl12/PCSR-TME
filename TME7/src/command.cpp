#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
// Question 1 : la premier sortie de commande doit alimenter l'entrée de la deuxime commande
int main (int argc, char ** argv) {
    //diviser la commande 
    int pipe_index = -1;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "|") == 0) {
            pipe_index = i;
            break;
        }
    }
    std::cout<<"pipe index at "<<pipe_index<<std::endl;

    // Construire les tableaux d'arguments pour cmd1 et cmd2
    char *cmd1[pipe_index + 1];
    char *cmd2[argc-pipe_index];
    for (int i = 1; i < pipe_index; i++) {
        cmd1[i-1] = argv[i];
    }
    cmd1[pipe_index - 1] = NULL;

    for (int i = pipe_index + 1; i < argc; i++) {

        cmd2[i-pipe_index-1] = argv[i];
    }
    cmd2[argc-pipe_index-1] = NULL;


    int tubeDesc[2]; 
    pid_t pid_fils;

    for (int i = 0; cmd1[i] != nullptr; i++) {
        std::cout << "command 1 = " << cmd1[i] << std::endl;
    }

    for (int i = 0; cmd2[i] != nullptr; i++) {
        std::cout << "command 2 = " << cmd2[i] << std::endl;
    }

    
    if (pipe(tubeDesc) == -1) {
        perror ("pipe");
        exit (1);
    }
    if ((pid_fils = fork( )) == -1 ){
        perror ("fork");
        exit (2);
    }
    if (pid_fils == 0) { /* fils */
        dup2(tubeDesc[1],STDOUT_FILENO); //ecriture
        close (tubeDesc[1]); 
        close (tubeDesc[0]);
        if (execv(cmd1[0],cmd1) == -1) {
            perror ("execv"); 
            exit (3);
        }
    }
    else { /* père */
        dup2(tubeDesc[0],STDIN_FILENO); // lecture
        close (tubeDesc[0]);
        close (tubeDesc[1]);
        if (execv(cmd2[0], cmd2) == -1) {
            perror ("execv"); 
            exit (3);
        }
    }
    return (EXIT_SUCCESS);
}