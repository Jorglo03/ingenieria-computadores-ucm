#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define ARMAGIC "<arspl>\n" /* Numero Magico simplear */
#define MAGSIZE 8           /* Longitud Numero Magico */

struct ar_ghdr /* Cabecera global */
{
    char ar_magic[MAGSIZE]; /* Numero Magico fichero simplear */
    int nfiles;             /* Numero de miembros */
};

struct ar_lhdr /* Cabecera de miembro de archivo */
{
    char ar_memname[16]; /* Nombre del miembro (maximo de 15 caracteres) */
    long ar_size;        /* Tamaño del contenido del miembro (en bytes) */
    char ar_date[12];    /* Fecha */
    int ar_uid;          /* ID de usuario */
    int ar_gid;          /* ID de grupo */
    char ar_mode[12];    /* Modo - octal */
};

int create_ar(char *ar_name, int n_files, char **files)
{
    struct ar_ghdr ghdr;
    struct ar_lhdr lhdr;
    FILE *ar_file;
    int i, fd, ret;
    char buf[1024];

    strcpy(ghdr.ar_magic, ARMAGIC);
    ghdr.nfiles = n_files;

    ar_file = fopen(ar_name, "w");
    if (!ar_file)
    {
        perror("Error opening ar file");
        return -1;
    }

    
    ret = fwrite(&ghdr, sizeof(struct ar_ghdr), 1, ar_file);
    if (ret != 1)
    {
        perror("Error writing global header");
        fclose(ar_file);
        return -1;
    }

    for (i = 0; i < n_files; i++)
    {
        fd = open(files[i], O_RDONLY);
        if (fd == -1)
        {
            perror("Error opening file");
            fclose(ar_file);
            return -1;
        }

        
        strncpy(lhdr.ar_memname, files[i], 15);
        lhdr.ar_memname[15] = '\0';

        struct stat file_stat;
        if (fstat(fd, &file_stat) == -1)
        {
            perror("Error getting file status");
            close(fd);
            fclose(ar_file);
            return -1;
        }
        lhdr.ar_size = file_stat.st_size;
        sprintf(lhdr.ar_date, "%ld", (long)file_stat.st_mtime);
        lhdr.ar_uid = file_stat.st_uid;
        lhdr.ar_gid = file_stat.st_gid;
        sprintf(lhdr.ar_mode, "%o", file_stat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

        ret = fwrite(&lhdr, sizeof(struct ar_lhdr), 1, ar_file);
        if (ret != 1)
        {
            perror("Error writing local header");
            close(fd);
            fclose(ar_file);
            return -1;
        }

        
        while ((ret = read(fd, buf, sizeof(buf))) > 0)
        {
            ret = fwrite(buf, 1, ret, ar_file);
            if (ret <= 0)
            {
                perror("Error writing file content");
                close(fd);
                fclose(ar_file);
                return -1;
            }
        }

        close(fd);
    }

    fclose(ar_file);
    return 0;
}

int insert_file(char *ar_name, char *file_name)
{
    
    FILE *ar_file = fopen(ar_name, "r+b");
    if (!ar_file)
    {
        perror("Error opening ar file");
        return -1;
    }

    
    struct ar_ghdr ghdr;
    fread(&ghdr, sizeof(struct ar_ghdr), 1, ar_file);

    
    fseek(ar_file, 0, SEEK_END);

   
    int fd = open(file_name, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        fclose(ar_file);
        return -1;
    }

    
    struct ar_lhdr lhdr;
    strncpy(lhdr.ar_memname, file_name, 15);
    lhdr.ar_memname[15] = '\0';

    struct stat file_stat;
    if (fstat(fd, &file_stat) == -1)
    {
        perror("Error getting file status");
        close(fd);
        fclose(ar_file);
        return -1;
    }
    lhdr.ar_size = file_stat.st_size;
    sprintf(lhdr.ar_date, "%ld", (long)file_stat.st_mtime);
    lhdr.ar_uid = file_stat.st_uid;
    lhdr.ar_gid = file_stat.st_gid;
    sprintf(lhdr.ar_mode, "%o", file_stat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    fwrite(&lhdr, sizeof(struct ar_lhdr), 1, ar_file);

    
    char buf[1024];
    int ret;
    while ((ret = read(fd, buf, sizeof(buf))) > 0)
    {
        ret = fwrite(buf, 1, ret, ar_file);
        if (ret <= 0)
        {
            perror("Error writing file content");
            close(fd);
            fclose(ar_file);
            return -1;
        }
    }

    close(fd);
    fclose(ar_file);
    return 0;
}

int extract_ar(char *ar_name)
{
    struct ar_ghdr ghdr;
    struct ar_lhdr lhdr;
    FILE *ar_file;
    int ret;
    char buf[1024];

    ar_file = fopen(ar_name, "r");
    if (!ar_file)
    {
        perror("Error opening ar file");
        return -1;
    }

    
    ret = fread(&ghdr, sizeof(struct ar_ghdr), 1, ar_file);
    if (ret != 1)
    {
        perror("Error reading global header");
        fclose(ar_file);
        return -1;
    }

    
    for (int i = 0; i < ghdr.nfiles; i++)
    {
        
        ret = fread(&lhdr, sizeof(struct ar_lhdr), 1, ar_file);
        if (ret != 1)
        {
            perror("Error reading local header");
            fclose(ar_file);
            return -1;
        }

        
        FILE *outfile = fopen(lhdr.ar_memname, "w");
        if (!outfile)
        {
            perror("Error creating output file");
            fclose(ar_file);
            return -1;
        }

        while (lhdr.ar_size > 0)
        {
            int to_read = sizeof(buf);
            if (lhdr.ar_size < sizeof(buf))
                to_read = lhdr.ar_size;
            ret = fread(buf, 1, to_read, ar_file);
            if (ret <= 0)
            {
                perror("Error reading file content");
                fclose(outfile);
                fclose(ar_file);
                return -1;
            }
            ret = fwrite(buf, 1, ret, outfile);
            if (ret <= 0)
            {
                perror("Error writing file content");
                fclose(outfile);
                fclose(ar_file);
                return -1;
            }
            lhdr.ar_size -= ret;
        }

        fclose(outfile);
    }

    fclose(ar_file);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s [-c|-r|-x] <ar_file> [files...]\n", argv[0]);
        return 1;
    }

    char *option = argv[1];
    char *ar_name = argv[2];

    if (strcmp(option, "-c") == 0)
    {
        if (argc < 4)
        {
            fprintf(stderr, "Usage: %s -c <ar_file> [files...]\n", argv[0]);
            return 1;
        }
        return create_ar(ar_name, argc - 3, &argv[3]);
    }
    else if (strcmp(option, "-r") == 0)
    {
        if (argc != 4)
        {
            fprintf(stderr, "Usage: %s -r <ar_file> <file_to_insert>\n", argv[0]);
            return 1;
        }
        return insert_file(ar_name, argv[3]);
    }
    else if (strcmp(option, "-x") == 0)
    {
        if (argc != 3)
        {
            fprintf(stderr, "Usage: %s -x <ar_file>\n", argv[0]);
            return 1;
        }
        return extract_ar(ar_name);
    }
    else
    {
        fprintf(stderr, "Unknown option: %s\n", option);
        return 1;
    }

    return 0;
}
