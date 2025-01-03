
// Autor/a: Jorge López Carrión
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado:C++ y Windows
// Nombre del problema: Sudokus correctos
// Comentario general sobre la solución
// explicando como se resuelve el problema: Se mete en un array unidimensional todas las filas , se ordenan y se comprueban que
// no se repitan los numeros, se aplica el mismo procedimiento en las columnas y en las regiones y se escribe finalmente
// si no se ha repetido ningun numero en una fila, columna o region

#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

const int MAX = 9;                  //Se declaran las constantes y los tipos necesarios
typedef int tMatriz[MAX][MAX];
typedef int tArray[MAX];

void resolver(tMatriz datos);               //Se declaran los prototipos de las funciones
void resuelveCaso();
bool leerCuadro(tMatriz datos, int fila, int columna);
bool comprobarIguales(tArray array);

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("datos.in");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
   std::ofstream out("datos.out");
   auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
   
   int numCasos;
   std::cin >> numCasos;
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   std::cout.rdbuf(coutbuf);
   system("PAUSE");
#endif
   return 0;
}

// función que resuelve el problema
void resolver(tMatriz datos) {
    bool comprobar = true, comprobar_repeticion;
    int x=0, y=0, fila_cuadro = 0, columna_cuadro = 0;
    tArray array;

    for (int i = 0; i < MAX; i++) {             //Se recorren las filas y se introduce en un array unidimensional
        for (int j = 0; j < MAX; j++) {
            array[j] = datos[i][j];
        }
        comprobar_repeticion = comprobarIguales(array);     //Se comprueba si no se repiten los numeros
        if (comprobar_repeticion == false) {
            comprobar = false;
        }
    }
    for (int i = 0; i < MAX; i++) {         //Se recorren las columnas y se introducen en un array unidimensional
        for (int j = 0; j < MAX; j++) {
            array[j] = datos[j][i];
        }
        comprobar_repeticion = comprobarIguales(array);
        if (comprobar_repeticion == false) {
            comprobar = false;
        }
    }
    for (int i = 0; i < MAX; i++) {
        
        if (i == 3 || i == 6) {     //Se van aumentando las filas y las columnas para que se vayan leyendo todas las regiones
            fila_cuadro += 3;
        }

        comprobar_repeticion = leerCuadro(datos, fila_cuadro, columna_cuadro);      //Funcion que guarda el cuadro en un array
        if (comprobar_repeticion == false) {
            comprobar = false;
        }

        columna_cuadro += 3;
        if (columna_cuadro > 7) {
            columna_cuadro = 0;
        }
    }
    //Finalmente, se escribe si el sudoku esta bien resuelto
    if (comprobar == true) {
        cout << "SI" << endl;
    }
    else if (comprobar == false) {
        cout << "NO" << endl;
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    tMatriz matriz;

    for (int i = 0; i < MAX; i++) {             //Se lee la matriz y se guarda
        for (int j = 0; j < MAX; j++) {
            cin >> matriz[i][j];
        }
    }

   resolver(matriz);
   
}

bool leerCuadro(tMatriz datos, int fila, int columna) {
    int aux = 0, menor, cambio;
    tArray array;
    bool comprobar = true;

    for (int i = fila; i < fila + 3; i++) {                 //Se lee el cuadro de 3x3 con la fila y la columna indicada
        for (int j = columna; j < columna + 3; j++) {
            array[aux] = datos[i][j];
            aux++;
        }
    }
    
    comprobar = comprobarIguales(array);

    return comprobar;
}

bool comprobarIguales(tArray array) {
    int menor, cambio;
    bool comprobar = true;
    
    //Se ordena el array
    for (int i = 0; i < MAX - 1; i++) {      //Se recorre el array
        menor = i;                                      //Se supone el i el menor numero
        for (int j = i + 1; j < MAX; j++) {  //a partir del siguiente numero se comprueba cual es el menor numero
            if (array[j] < array[menor]) {      //Se va comprobando cual es el menor numero de los no ordenados
                menor = j;
            }
        }
        cambio = array[i];          //Se cambia la posicion del primer numero no ordenado por el menor de lo que quedaban sin ordenar
        array[i] = array[menor];
        array[menor] = cambio;

    }
    for (int i = 0; i < MAX - 1; i++) {         //Se comprueba que no se repitan los numeros
        if (array[i] == array[i + 1]) {
            comprobar = false;
        }
    }

    return comprobar;
}