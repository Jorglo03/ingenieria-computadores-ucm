#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main() {
    // Obtener el UID efectivo y real del usuario
    uid_t effective_uid = geteuid();
    uid_t real_uid = getuid();

    // Verificar si el bit setuid está activado en el ejecutable
    int setuid_bit_activated = (effective_uid != real_uid);

    // Imprimir la información sobre los UIDs y el bit setuid
    printf("UID efectivo: %d\n", effective_uid);
    printf("UID real: %d\n", real_uid);
    printf("El bit setuid está %sactivado en el ejecutable.\n", setuid_bit_activated ? "" : "des");

    // Obtener información adicional sobre el usuario real utilizando getpwuid()
    struct passwd *user_info = getpwuid(real_uid);
    if (user_info != NULL) {
        printf("Nombre de usuario: %s\n", user_info->pw_name);
        printf("Directorio home: %s\n", user_info->pw_dir);
        printf("Shell: %s\n", user_info->pw_shell);
    } else {
        perror("Error al obtener información del usuario real");
        return 1;
    }

    return 0;
}
