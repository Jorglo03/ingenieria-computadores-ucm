#include <sys/types.h>
#include <time.h>
#include <stdio.h>

int main() {
    // Obtención del tiempo actual (time_t)
    time_t tiempo_actual;
    time(&tiempo_actual);

    // Obtención de la estructura (struct tm) local
    struct tm *info_tiempo = localtime(&tiempo_actual);

    // Formatear la fecha en una cadena con el patrón "Hoy es Viernes, 11:40"
    char cadena_formateada[80];
    strftime(cadena_formateada, sizeof(cadena_formateada), "Hoy es %A, %H:%M", info_tiempo);

    // Mostrar la cadena resultante
    printf("%s\n", cadena_formateada);

    return 0;
}
