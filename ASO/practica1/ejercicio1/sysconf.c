#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main() {
    // Ticks por segundo
    printf("Ticks por segundo: %ld\n", sysconf(_SC_CLK_TCK));

    // Número máximo de procesos simultáneos que puede ejecutar un usuario
    printf("Número máximo de procesos simultáneos por usuario: %ld\n", sysconf(_SC_CHILD_MAX));

    // Número máximo de ficheros que puede abrir un proceso
    printf("Número máximo de ficheros que puede abrir un proceso: %ld\n", sysconf(_SC_OPEN_MAX));

    // Tamaño de las páginas de memoria
    printf("Tamaño de las páginas de memoria: %ld bytes\n", sysconf(_SC_PAGESIZE));

    // Longitud máxima de los argumentos a un programa
    printf("Longitud máxima de los argumentos a un programa: %ld bytes\n", sysconf(_SC_ARG_MAX));

    // Número máximo de enlaces de un fichero en el sistema de archivos
    printf("Número máximo de enlaces de un fichero en el sistema de archivos: %ld\n", sysconf(_SC_LINE_MAX));

    // Tamaño máximo de una ruta en el sistema de archivos
    printf("Tamaño máximo de una ruta en el sistema de archivos: %ld bytes\n", pathconf("/", _PC_PATH_MAX));

    // Tamaño máximo de un nombre de fichero en el sistema de archivos
    printf("Tamaño máximo de un nombre de fichero en el sistema de archivos: %ld bytes\n", pathconf("/", _PC_NAME_MAX));

    return 0;
}
