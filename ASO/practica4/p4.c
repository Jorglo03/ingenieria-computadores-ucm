#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#define MAXMSJ 100

volatile sig_atomic_t mensaje_disponible = 0;
volatile sig_atomic_t hijo_listo = 1;

void handler_sigusr1(int signum){
    mensaje_disponible = 1;
    hijo_listo = 0;
}

void handler_sigusr2(int signum){
    hijo_listo = 1;
    mensaje_disponible = 0;
}

void handler_sigterm(int signum){
    printf("Señal SIGTERM enviada al hijo, saliendo del programa...\n");
    exit(EXIT_SUCCESS);
}

int main(){

    FILE* mailbox;
    char mensaje[MAXMSJ];
    int pausa_secs = 1;
    char* pausa_env = getenv("PAUSASECS");

    signal(SIGUSR1, handler_sigusr1);
    signal(SIGUSR2, handler_sigusr2);
    signal(SIGTERM, handler_sigterm);

    if(pausa_env != NULL){
        pausa_secs = atoi(pausa_env);
    }    


    pid_t pid = fork();

    if(pid == 0){

        while(1){
            pause();
            if(mensaje_disponible == 1){
                mailbox = fopen("mailbox.txt", "r");
                fgets(mensaje, MAXMSJ, mailbox);
                fclose(mailbox);
                printf("\nHIJO-> Mensaje recibido: %s\n", mensaje);
                kill(getppid(), SIGUSR2);
            }
        }
    }
    else{
        while(1){
            if(hijo_listo == 1){
                mailbox = fopen("mailbox.txt", "w");
                printf("PADRE-> Escriba el mensaje: \n");
                char* result = fgets(mensaje, MAXMSJ, stdin);
                if(result == NULL){
                    printf("CTRL+D detectado en el padre, saliendo del programa...\n");
                    kill(pid, SIGTERM);
                    exit(EXIT_SUCCESS);
                }
                fputs(mensaje, mailbox);
                fclose(mailbox);
                kill(pid, SIGUSR1);
                pause();
                sleep(pausa_secs);
            }
        }
    }

    return 0;
}