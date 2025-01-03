#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX_BUF 1024
#define MAX_MENSAJES 10

int main(int argc, char *argv[]) {
    
    int padre_hijo[2];
    int hijo_padre[2];

    if(pipe(padre_hijo) == -1 || pipe(hijo_padre) == -1){
        perror("Error al crear las tuberías\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if(pid == 0){
        close(padre_hijo[1]);
        close(hijo_padre[0]);
        int i;
        for(i = 0; i < MAX_MENSAJES; i++){
            char buf[MAX_BUF];
            size_t size = read(padre_hijo[0], buf, MAX_BUF);
            int j;
            for(j = 0; j < size; j++){
                buf[j] = toupper(buf[j]);
            }
            printf("Mensaje recibido por el proceso hijo: %.*s\n",(int) size, buf);
            sleep(1);
            if(i < MAX_MENSAJES - 1){
                char confirmacion = 'n';
                write(hijo_padre[1], &confirmacion, sizeof(char));
            }
            else{
                char fin = 'q';
                write(hijo_padre[1], &fin, sizeof(char));
            }
        }
        close(padre_hijo[0]);
        close(hijo_padre[0]);
        exit(EXIT_SUCCESS);
    }
    else{
        close(padre_hijo[0]);
        close(hijo_padre[1]);
        int i = 0;
        while(i < MAX_MENSAJES){
            char msj[MAX_BUF];
            printf("Ingrese un mensaje: ");
            fgets(msj, sizeof(msj), stdin);

            if(write(padre_hijo[1], msj, strlen(msj)) == -1){
                perror("Error al enviar el mensaje\n");
                exit(EXIT_FAILURE);
            }
            char confirmacion;
            if(read(hijo_padre[0], &confirmacion, sizeof(char)) == -1){
                perror("Error al leer el mensaje de confirmacion\n");
                exit(EXIT_FAILURE);
            }
            if(confirmacion == 'n'){
                printf("El proceso hijo está disponible para un nuevo mensaje\n");
            }
            else if(confirmacion == 'q'){
                printf("Numero de mensajes maximos enviados\n");
            }
            i++;
        }
        close(padre_hijo[1]);
        close(hijo_padre[0]);

        wait(NULL);
    }

    return 0;
}
