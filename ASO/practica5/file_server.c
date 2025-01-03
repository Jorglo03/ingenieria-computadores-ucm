
/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2022.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/
/* file_server.c

   A file server that uses System V message queues to handle client requests
   (see file_client.c). The client sends an initial request containing
   the name of the desired file, and the identifier of the message queue to be
   used to send the file contents back to the child. The server attempts to
   open the desired file. If the file cannot be opened, a failure response is
   sent to the client, otherwise the contents of the requested file are sent
   in a series of messages.

   This application makes use of multiple message queues. The server maintains
   a queue (with a well-known key) dedicated to incoming client requests. Each
   client creates its own private queue, which is used to pass response
   messages from the server back to the client.

   This program operates as a concurrent server, forking a new child process to
   handle each client request while the parent waits for further client requests.
*/
#include "sfile.h"

void reset_signal_mask() {
    sigset_t mask;
    if (sigemptyset(&mask) == -1) {
        perror("Error al vaciar la máscara de señales");
        exit(EXIT_FAILURE);
    }
    if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1) {
        perror("Error al restablecer la máscara de señales");
        exit(EXIT_FAILURE);
    }
}

void reset_signal_handlers() {
    struct sigaction sa;
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    int i;
    for (i = 1; i < 32; i++) {
        if (i == SIGKILL || i == SIGSTOP || i == SIGCONT || i == SIGSYS) {
            continue;
        }
        if (i >= SIGRTMIN && i <= SIGRTMAX) {
            continue;
        }
        if (sigaction(i, &sa, NULL) == -1) {
            printf("%d", i);
            perror("Error al restablecer el manejador de señales");
            exit(EXIT_FAILURE);
        }
    }
}

void close_all_fds() {
    struct dirent *entry;
    DIR *dir;

    dir = opendir("/proc/self/fd");
    if (dir == NULL) {
        perror("Error opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            int fd = atoi(entry->d_name);
            if (fd != STDERR_FILENO && fd != STDIN_FILENO && fd != STDOUT_FILENO) {
                if (close(fd) == -1) {
                    perror("Error al cerrar el descriptor de archivo");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    closedir(dir);
}


void daemonize() {
    close_all_fds();
    reset_signal_handlers();
    reset_signal_mask();

    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork 1");
        exit(EXIT_FAILURE);
    }

    if (pid1 > 0) {
        exit(EXIT_SUCCESS);
    }

    if (setsid() < 0) {
        perror("Error al crear la sesión");
        exit(EXIT_FAILURE);
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork 2");
        exit(EXIT_FAILURE);
    }

    if (pid2 > 0) {
        exit(EXIT_SUCCESS);
    }

    if (chdir("/") < 0) {
        perror("Error en chdir");
        exit(EXIT_FAILURE);
    }

    umask(0);

    int dev_null = open("/dev/null", O_RDWR);
    if (dev_null < 0) {
        perror("Error al abrir /dev/null");
        exit(EXIT_FAILURE);
    }

    if (dup2(dev_null, STDERR_FILENO) == -1 || 
        dup2(dev_null, STDIN_FILENO) == -1 || 
        dup2(dev_null, STDOUT_FILENO) == -1) {
        perror("Error en dup2");
        exit(EXIT_FAILURE);
    }

    close(dev_null);
}

static void grimReaper(int sig){ /* SIGCHLD handler */
    int savedErrno;

    savedErrno = errno;                 /* waitpid() might change 'errno' */
    while (waitpid(-1, NULL, WNOHANG) > 0)
        continue;
    errno = savedErrno;
}

static void serveRequest(const struct requestMsg *req){
    /* Executed in child process: serve a single client */
    int fd;
    ssize_t numRead;
    struct responseMsg resp;
    mqd_t clientQueue;

    clientQueue = mq_open("/client_queue", O_WRONLY);

    fd = open(req->pathname, O_RDONLY);
    if (fd == -1) {                     /* Open failed: send error text */
        resp.mtype = RESP_MT_FAILURE;
        snprintf(resp.data, sizeof(resp.data), "%s", "Couldn't open");
        if (clientQueue == (mqd_t)-1) {
            perror("mq_open - client message queue");
            exit(EXIT_FAILURE);
        }
        if (mq_send(clientQueue, (const char *)&resp, strlen(resp.data) + 1, 0) == -1) {
            perror("mq_send");
        }  
        mq_close(clientQueue);
        exit(EXIT_FAILURE);             /* and terminate */
    }

    /* Transmit file contents in messages with type RESP_MT_DATA. We don't
       diagnose read() and msgsnd() errors since we can't notify client. */

    resp.mtype = RESP_MT_DATA;
    while ((numRead = read(fd, resp.data, RESP_MSG_SIZE)) > 0)
        if (mq_send(clientQueue, (const char *)&resp, numRead, 0) == -1)            
            break;

    /* Send a message of type RESP_MT_END to signify end-of-file */

    resp.mtype = RESP_MT_END;

    if (mq_send(clientQueue, (const char *)&resp, 0, 0) == -1) {
        perror("mq_send");
    }
}


int main(int argc, char *argv[]) {

    daemonize();
    struct requestMsg req;
    pid_t pid;
    ssize_t msgLen;
    int serverId;
    struct sigaction sa;

    /* Create server message queue */

    /*serverId = msgget(SERVER_KEY, IPC_CREAT | IPC_EXCL |
                            S_IRUSR | S_IWUSR | S_IWGRP);*/

    struct mq_attr attr;
    

    // Configurar los atributos de la cola de mensajes
    attr.mq_flags = 0;         // Flags (0 para ningún flag)
    attr.mq_maxmsg = 10;       // Número máximo de mensajes en la cola
    attr.mq_msgsize = 8192;    // Tamaño máximo de cada mensaje

    // Crear la cola de mensajes con los atributos configurados
    mqd_t serverQueue = mq_open("/server_queue", O_CREAT | O_RDONLY, 0666, &attr);    
    if (serverQueue == (mqd_t)-1) {
        if (errno == EEXIST) {
            printf("La cola de mensajes ya existe.\n");
            // Manejo si la cola de mensajes ya existe
        } else {
            perror("mq_open - server message queue");
            exit(EXIT_FAILURE);
        }
    }

    // Vaciar la cola de mensajes leyendo todos los mensajes disponibles
    //while (mq_receive(serverQueue, buf, attr.mq_msgsize, NULL) != -1) {}


    /* Establish SIGCHLD handler to reap terminated children */

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = grimReaper;
    if (sigaction(SIGCHLD, &sa, NULL) == -1){
        perror("sigaction");
        exit(1);
    }

    /* Read requests, handle each in a separate child process */

    for (;;) {
        //msgLen = msgrcv(serverId, &req, REQ_MSG_SIZE, 0, 0);
            char buf[attr.mq_msgsize];

        msgLen = mq_receive(serverQueue, buf, attr.mq_msgsize +1, NULL);
        if (msgLen == -1) {
            if (errno == EINTR)         /* Interrupted by SIGCHLD handler? */
                continue;               /* ... then restart msgrcv() */
            perror("mq_recieve");           /* Some other error */
            break;                      /* ... so terminate loop */
        }

        pid = fork();                   /* Create child process */
        if (pid == -1) {
            perror("fork");
            break;
        }

        if (pid == 0) {                 /* Child handles request */
            serveRequest(&req);
            _exit(EXIT_SUCCESS);
        }

        /* Parent loops to receive next client request */
    }

    /* If msgrcv() or fork() fails, remove server MQ and exit */

    mq_close(serverQueue);
    mq_unlink("/server_queue");
    exit(EXIT_SUCCESS);
}