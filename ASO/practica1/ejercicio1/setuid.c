#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main() {
	
// Llamada al sistema setuid
    if (setuid(0) == -1) {
        // En caso de error
        perror("Error en setuid");        
		return 1;
    } else {
        // En caso de éxito
        printf("setuid ejecutado correctamente\n");
        return 0;
    }
} 
