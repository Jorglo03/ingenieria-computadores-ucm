#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    // Verificar si se proporciona un argumento
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <valor_entero>\n", argv[0]);
        return 1;
    }

    // Obtener el valor entero de la línea de comandos
    int mivar = 0;
    int entero = atoi(argv[1]);
    // Obtener el tiempo inicial
    struct timeval inicio, fin;
    gettimeofday(&inicio, NULL);

    // Bucle de 10000 iteraciones
    for (int i = 0; i < 10000; ++i) {
        mivar += entero; // Incrementar mivar con el valor entero proporcionado
    }

    // Obtener el tiempo final
    gettimeofday(&fin, NULL);

    // Calcular el tiempo transcurrido en microsegundos
    long tiempo_transcurrido = (fin.tv_sec - inicio.tv_sec) * 1000000 + (fin.tv_usec - inicio.tv_usec);

    // Mostrar el valor final de mivar y el tiempo transcurrido
    printf("Valor final de mivar: %d\n", mivar);
    printf("Tiempo transcurrido: %ld microsegundos\n", tiempo_transcurrido);

    return 0;
}
