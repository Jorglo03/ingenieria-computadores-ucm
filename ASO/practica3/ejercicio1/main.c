#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    if(argc != 2){
        fprintf(stderr, "Faltan o sobran argumentos!");
        exit(EXIT_FAILURE);
    }

    int pipefd[2];

    if(pipe(pipefd) == -1){
        perror("Error al crear la tubería sin nombre");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if(pid == 0){
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        execlp(argv[3], argv[3], argv[4], NULL);
        perror("Error en el execlp");
        exit(EXIT_SUCCESS);
    }
    else{
        close(pipefd[0]);
        dup2(pipefd[1],STDOUT_FILENO);
        execlp(argv[1], argv[1], argv[2], NULL);
        perror("Error en el execlp");
        exit(EXIT_SUCCESS);
    }
    wait(NULL);
    return 0;
}
