#include <stdio.h>
#include <sys/utsname.h>

int main() {
    struct utsname system_info;

    // Llamada al sistema uname para obtener información del sistema
    if (uname(&system_info) != 0) {
        perror("Error en uname");
        return 1;
    }

    // Mostrar los detalles del sistema
    printf("Sistema operativo: %s\n", system_info.sysname);
    printf("Nombre del nodo: %s\n", system_info.nodename);
    printf("Release del sistema: %s\n", system_info.release);
    printf("Versión del sistema: %s\n", system_info.version);
    printf("Arquitectura de la máquina: %s\n", system_info.machine);

    return 0;
}
