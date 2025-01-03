#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if(argc != 2){
        fprintf(stderr, "Faltan o sobran argumentos!");
    }
    char* tuberia = "./tuberia1";

    int fd = open(tuberia, O_WRONLY);

    if(fd == -1){
        perror("Error al abrir la tuberia");
        exit(EXIT_FAILURE);
    }

    if(write(fd, argv[1], strlen(argv[1])) == -1){
        perror("Error al escribir en la tuberia");
        exit(EXIT_FAILURE);
    }

    close(fd);

    return 0;
}
