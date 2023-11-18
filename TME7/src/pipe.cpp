#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc,char **argv){
    int i;
    int pfd[2];
    pipe(pfd);

    for (i = 2; i < argc; i++) {
        if(strcmp(argv[i],"|") == 0){
            argv[i] = nullptr;
            break;
        }
    }

    if(fork()==0){
        close(pfd[0]);                          //close the read for the one who is writting
        dup2(pfd[1],STDOUT_FILENO);             //Will remplace the output standard to pfd[1] (the write end of the pipe)
        execv(argv[1],argv+1);
        perror("Error with child 1");
        return EXIT_FAILURE;
    }

    if(fork()==0){
        close(pfd[1]);                          //close the write for the one who is reading
        dup2(pfd[0],STDIN_FILENO);              //will remplace the input standard to pfd[0]  (the read end of the pipe)
        execv(argv[i+1],argv+i+1);
        perror("Error with child 2");
        return EXIT_FAILURE;
    }

    close(pfd[1]);                              //close write for the father 
    close(pfd[0]);                              //close read for the father

    wait(NULL);
    wait(NULL);

}