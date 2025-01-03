#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/stat.h>

#define MAX_BUF 1024

int main(int argc, char *argv[]) {
    
    char* tuberia1 = "./tuberia1";
    char* tuberia2 = "./tuberia2";

    if(mkfifo(tuberia2, 0666) == -1){
        perror("Error al crear la tubería\n");
    }

    int fd1 = open(tuberia1, O_RDONLY | O_NONBLOCK);
    int fd2 = open(tuberia2, O_RDONLY | O_NONBLOCK);

    if(fd1 == -1 || fd2 == -1){
        perror("Error al abrir la tuberia");
        exit(EXIT_FAILURE);
    }
    int stdin_fd = fileno(stdin);
    fd_set conjunto;
    int num_fds = (fd1 > fd2 ? fd1 : fd2) + 1;
    char buf[MAX_BUF];

    while(1){
        FD_ZERO(&conjunto);
        FD_SET(fd1, &conjunto);
        FD_SET(fd2, &conjunto);
        FD_SET(stdin_fd, &conjunto);

        if(select(num_fds, &conjunto, NULL, NULL, NULL) == -1){
            perror("Error en select\n");
            exit(EXIT_FAILURE);
        }
        if(FD_ISSET(stdin_fd, &conjunto)){
            char c;
            if(read(stdin_fd,&c, 1) == 0){
                printf("Cerrado el programa con CTRL+D\n");
                break;
            }
        }
        if(FD_ISSET(fd1, &conjunto)){
            size_t size = read(fd1, buf, MAX_BUF);
            if(size > 0){
                printf("Tuberia 1: %.*s", (int) size, buf);
            }
        }
        if(FD_ISSET(fd2, &conjunto)){
            size_t size = read(fd2, buf, MAX_BUF);
            if(size > 0){
                printf("Tuberia 2: %.*s", (int) size, buf);
            }
        }
    }

    close(fd1);
    close(fd2);
    return 0;
}
