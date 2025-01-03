#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

int main(int argc, char** argv){

    dlerror();

    void *manejador = dlopen("./libmilibreria.so", RTLD_LAZY);

    if(!manejador){
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    int (*funaux1)() = dlsym(manejador, "funaux1");

    if(!funaux1){
        fprintf(stderr, "Error al obtener el simbolo: %s\n", dlerror());
        exit(1);
    }
    int res = funaux1();
    printf("- el resultado de ejecutar la funcion 1 es %d\n",res);

    int (*funaux2)() = dlsym(manejador, "funaux2");

    if(!funaux2){
        fprintf(stderr, "Error al obtener el simbolo: %s\n", dlerror());
        exit(1);
    }
    res = funaux2();
    printf("- el resultado de ejecutar la funcion 2 es %d\n",res);

    dlclose(manejador);

    return 0;
}