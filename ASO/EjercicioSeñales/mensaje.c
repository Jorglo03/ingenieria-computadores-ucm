#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

char* mensaje = NULL;
int hay_mensaje = 0;
time_t start_time;

void alarm_handler(int signum) {
    if (!hay_mensaje)
        printf("Mensaje del temporizador\n");
    else
        printf("%s\n", mensaje);
}

void sigint_handler(int signum) {
    printf("\nCTRL+C capturado\n");
}

void sigterm_handler(int signum) {
    time_t end_time = time(NULL);
    int duracion = (int)difftime(end_time, start_time);
    printf("El programa ha durado %d segundos\n", duracion);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    start_time = time(NULL);
    pid_t pid = getpid();
    printf("PID: %d\n", pid);

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Uso: %s <segundos> [mensaje]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 3) {
        mensaje = argv[2];
        hay_mensaje = 1;
    }

    int segundos = atoi(argv[1]);

    struct sigaction s_alarm;
    s_alarm.sa_handler = alarm_handler;
    sigemptyset(&s_alarm.sa_mask);
    s_alarm.sa_flags = 0;
    sigaction(SIGALRM, &s_alarm, NULL);

    struct sigaction s_int;
    s_int.sa_handler = sigint_handler;
    sigemptyset(&s_int.sa_mask);
    s_int.sa_flags = 0;
    sigaction(SIGINT, &s_int, NULL);

    signal(SIGTERM, sigterm_handler);

    alarm(segundos);

    while(1) {
        pause();
        alarm(segundos);
    }

    return 0;
}
