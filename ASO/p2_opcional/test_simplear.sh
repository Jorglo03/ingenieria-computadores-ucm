#!/bin/bash

# Verificar si simplear está presente y es ejecutable
if [ ! -x "./simplear" ]; then
    echo "Error: simplear no encontrado o no es ejecutable"
    exit 1
fi

# Verificar si existe el directorio tmp y limpiarlo si es necesario
if [ -d "./tmp" ]; then
    rm -r "./tmp"
fi

# Crear un nuevo directorio temporal
mkdir "./tmp"
cd "./tmp" || exit

# Crear tres archivos dentro del directorio tmp
head -n 10 /etc/passwd > file2.txt
head -c 1024 /dev/urandom > file3.dat

# Crear un archivo ar con los tres archivos creados
../simplear -c miarchivoar.ar file1.txt file2.txt file3.dat

# Crear un directorio para extraer los archivos
mkdir out

# Copiar el archivo ar al directorio out
cp miarchivoar.ar out/

# Cambiar al directorio out
cd out || exit

# Extraer el contenido del archivo ar
../simplear -x miarchivoar.ar

# Comparar los archivos extraídos con los originales
if diff tmp/file2.txt ../file2.txt && diff file3.dat ../file3.dat; then
    echo "Correcto"
    exit 0
else
    echo "Error: Los archivos extraídos no son idénticos a los originales"
    exit 1
fi
