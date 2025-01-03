
// Autor/a: Jorge López Carrión
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado: C++ y Windows
// Nombre del problema: Grados de interés
/* Comentario general sobre la solución
 explicando como se resuelve el problema: Se leen las filas y las columnas de la matriz y la propia matriz y se guardan los datos
 a cada posicion de la matriz se le calcula el grado de interes mediante la formula del enunciado. Finalmente, se ordena el array
 de los grados de interes y se imprime la informacion en el fichero */

#include <iostream>
#include <fstream>

using namespace std;

const int MAX = 50;         //Se declaran las constantes necesarias

typedef int tMatriz[MAX][MAX];      //Se declaran los tipos necesarios
typedef struct {
    int filas;
    int columnas;
    tMatriz m;
}tDatos;

bool resuelveCaso();                    //Se declaran los prototipos de las funciones
int gradosInteres(tDatos datos, int pos_fila, int pos_columna);

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
   std::ofstream out("datos.out");
   auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   std::cout.rdbuf(coutbuf);
   system("PAUSE");
#endif
   return 0;
}


bool resuelveCaso() {
    tDatos matriz;
    int aux=0, menor, cambio;
    int interes[MAX*MAX];

   cin >> matriz.filas;        //Se leen las filas y las columnas de la matriz y la propia matriz
   if (!std::cin)
       return false;
   cin >> matriz.columnas;
   for (int i = 0; i < matriz.filas; i++) {
       for (int j = 0; j < matriz.columnas; j++) {
           cin >> matriz.m[i][j];
       }
   }
   
   for (int i = 0; i < matriz.filas; i++) {         //Se invoca la funcion que calcula el grado de interes en cada posicion de la matriz
       for (int j = 0; j < matriz.columnas; j++) {
           interes[aux] = gradosInteres(matriz, i, j);
           aux++;                                   //El grado de interes de cada posicion se van guardando en un array
       }
   }

   for (int i = 0; i < aux - 1; i++) {      //Se recorre el array
       menor = i;                                      //Se supone el i el menor numero
       for (int j = i + 1; j < aux; j++) {          //A partir del siguiente numero se comprueba cual es el menor numero
           if (interes[j] < interes[menor]) {        //Se va comprobando cual es el menor numero de los no ordenados
               menor = j;
           }
       }
       cambio = interes[i];          //Se cambia la posicion del primer numero no ordenado por el menor de lo que quedaban sin ordenar
       interes[i] = interes[menor];
       interes[menor] = cambio;
   }
   
   for (int i = 0; i < aux; i++) {      //Finalmente, se imprime en el archivo la solucion
       cout << interes[i];
       if (i != aux - 1) {
           cout << " ";
       }
   }
   cout << endl;

   return true;
}

int gradosInteres(tDatos datos, int pos_fila, int pos_columna) {
    int interes, suma = 0, suma_diagonal1 = 0, suma_diagonal2 = 0,x, y;

    for (int i = 0; i < datos.columnas; i++) {          //Se efectua la suma de todos los elementos de la fila
        suma += datos.m[pos_fila][i];
    }
    for (int i = 0; i < datos.filas; i++) {             //Se efectua la suma de todos los elementos de la columna
        suma += datos.m[i][pos_columna];
    }
    x = pos_fila;               
    y = pos_columna;
    
    //Se recorren las diagonales(en los dos sentidos cada diagonal partiendo de la posicion dada) sumando sus terminos
    for (int i = 0; i < 4; i++) {
        while (pos_fila < datos.filas && pos_fila >= 0 && pos_columna >= 0 && pos_columna < datos.columnas) {
            if (i == 0) {
                suma_diagonal1 += datos.m[pos_fila][pos_columna];
                pos_fila--;
                pos_columna++;
            }
            else if (i == 1) {
                suma_diagonal1 += datos.m[pos_fila][pos_columna];
                pos_fila++;
                pos_columna--;
            }
            else if (i == 2) {
                suma_diagonal2 += datos.m[pos_fila][pos_columna];
                pos_fila--;
                pos_columna--;
            }
            else if (i == 3) {
                suma_diagonal2 += datos.m[pos_fila][pos_columna];
                pos_fila++;
                pos_columna++;
            }
        }
        pos_fila = x;       //Se van reiniciando las filas y las columnas a los datos iniciales
        pos_columna = y;
    }
    suma_diagonal1 -= datos.m[x][y];
    suma_diagonal2 -= datos.m[x][y];

    interes = suma - suma_diagonal1 - suma_diagonal2;         //Se calcula el grado de interes en la posicion dada

    return interes;     
}