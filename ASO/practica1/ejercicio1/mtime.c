// includes
#include <stdio.h>
#include <time.h>

int main(){
  

    char *shoy, *s;

    // consular la fecha actual
    time_t tiempo;

    time(&tiempo);
    
    shoy = ctime(&tiempo);

    printf("Hoy es: %s",shoy);
 
    // calcular que fecha fue hace 10 dias
    
    time_t tiempo_diez_dias = tiempo - (10 * 24 * 60 * 60);

    s = ctime(&tiempo_diez_dias);

    printf("Hace 10 dias fue: %s",s);    
    
    return 0;
}    