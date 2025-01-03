
// Autor/a: Jorge López Carrión
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado: Visual Studio 2019 y Windows
// Nombre del problema: Examen FP2. Junio 2020. Modelo 1
/* Comentario general sobre la solución explicando como se resuelve el problema:Se leen el numero de filas y el numero de columnas de la matriz
y se guarda la informacion de toda la matriz. A continuacion, se va comprobando si cada alimento es seductor o no para saber el numero total
de alimentos seductores. Finalmente, se imprime en pantalla el numero todal de seductores.*/

#include <iostream>
#include <fstream>

using namespace std;

const int M = 30;               //Se declaran las constantes necesarias
const int FILAS = 6;
const int COLUMNAS = 12;

typedef int tMatriz[FILAS][COLUMNAS];       //Se declaran los tipos necesarios
typedef struct {
    tMatriz matriz;
    int filas;
    int columnas;
}tMatriz2;

void resuelveCaso();            //Se declaran los prototipos de las funciones
bool seductor(int alimento, tMatriz2 matriz);
int numAlimentos(tMatriz2 matriz);

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


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    tMatriz2 matriz;
    int numAlimentos1;

    cin >> matriz.filas >> matriz.columnas;             //Se leen las filas y las columnas
    for (int i = 0; i < matriz.filas; i++) {
        for (int j = 0; j < matriz.columnas; j++) {
            cin >> matriz.matriz[i][j];                 //Se rellena toda la matriz
        }
    }
    numAlimentos1 = numAlimentos(matriz);               //Se llama a la funcion que calcula el numero de alimentos seductores

    cout << numAlimentos1 << endl;                      //Se escribe la solucion
}

bool seductor(int alimento, tMatriz2 matriz) {
    bool seductor = false;
    int suma = 0;

    for (int i = 0; i < matriz.columnas; i++) {         //Se calcula el numero de veces que han "visitado" el alimento
        suma += matriz.matriz[alimento][i];
    }
    if (suma > M) {                                     //Se comprueba si el alimento es seductor
        seductor = true;
    }

    return seductor;
}

int numAlimentos(tMatriz2 matriz) {
    int numAlimentos = 0;
    bool seductor1;

    for (int i = 0; i < matriz.filas; i++) {            
        seductor1 = seductor(i, matriz);                //Se llama a la funcion para que calcule si el alimento es seductor
        if (seductor1 == true) {
            numAlimentos++;                             //Si es seductor se suma un alimento seductor mas a la variable
        }
    }

    return numAlimentos;
}