#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
enum opcion { NOOP, FICHERO, DIRECTORIO };

void imprimeDatosFichero(struct stat file_stat, char* path){
    printf("%s", path);
    printf(" (%.2f kb, %ld link)", (float)file_stat.st_size / 1024, (long)file_stat.st_nlink);

    if (S_IXUSR & file_stat.st_mode || S_IXOTH & file_stat.st_mode || S_IXGRP & file_stat.st_mode) {
        printf("*");
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int opt;
    int modo = NOOP;
    char *path = NULL;

    while ((opt = getopt(argc, argv, "f:d:")) != -1) {
        switch (opt) {
            case 'f':
                modo = FICHERO;
                path = optarg;
                break;
            case 'd':
                modo = DIRECTORIO;
                path = optarg;
                break;
            default:
                printf("Faltan argumentos en el programa\n");
                // exit(1);
                break;
        }
    }
    if (modo == FICHERO) {
        struct stat file_stat;
        if (lstat(path, &file_stat) != 0) {
            perror("Error en lstat\n");
        }
        if (S_ISREG(file_stat.st_mode)) {
            printf("%s", path);
            printf("(inodo %lu %.2f kb)\n", file_stat.st_ino,(float)file_stat.st_size / 1024);
        } 
        else {
            printf("%s no es un archivo regular.\n", path);
        }
    } 
    else if (modo == DIRECTORIO) {
        // Manejar el caso del directorio
        struct stat file_stat;
        if (lstat(path, &file_stat) != 0) {
            perror("Error en lstat\n");
        }
        if(S_ISDIR(file_stat.st_mode)){
            if (S_IXUSR & file_stat.st_mode || S_IXOTH & file_stat.st_mode || S_IXGRP & file_stat.st_mode ||
                S_IRUSR & file_stat.st_mode || S_IROTH & file_stat.st_mode || S_IRGRP & file_stat.st_mode) {
            
                DIR* dirp;
                struct dirent *dp;
                char buff[1024];
                dirp = opendir(path);
                
                while((dp = readdir(dirp)) != NULL){
                    if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0){
                        continue;
                    }
                    snprintf(buff, sizeof(buff), "%s/%s", path, dp->d_name); //tener la ruta completa. Sin esto no funciona si trabajamos con directorios fuera del workspace
                    struct stat fs;
                    lstat(buff,&fs);

                    if(S_ISDIR(fs.st_mode)){
                        printf("[%s]", dp->d_name);
                        printf(" %ld links\n", (long) fs.st_nlink);
                    }
                    else if(S_ISREG(fs.st_mode)){
                        imprimeDatosFichero(fs, dp->d_name);
                    } 
                    else if(S_ISLNK(fs.st_mode)){
                        char enlace_simbolico[1024];

                        ssize_t len = readlink(buff, enlace_simbolico, sizeof(enlace_simbolico) - 1);
                        if(len != -1){
                            enlace_simbolico[len] = '\0';
                            printf("%s (%s)\n", dp->d_name, enlace_simbolico);
                        }
                        else{
                            perror("Error leyendo el enlace simbolico\n");
                        }
                    }
                }
                closedir(dirp);
            }
            else{
                perror("Error con los permisos del directorio");
                exit(1);
            }
        }
		else {
            perror("La entrada no es un directorio.\n");
            exit(1);
		}
	        
        
    }

    return 0;
}
