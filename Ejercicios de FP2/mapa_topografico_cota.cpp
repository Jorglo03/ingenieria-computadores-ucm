
// Autor/a: Jorge López Carrión
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado: C++ y Windows
// Nombre del problema: Máxima cota de un mapa topográfico
// Comentario general sobre la solución
// explicando como se resuelve el problema: Se leen los datos del archivo y a continuacion se guarda el primer numero
// se empieza suponiendo que ese es el maximo y se va comprobando si el siguiente es mayor y asi sucesivamente.
// se guarda el numero mayor y sus correspondientes coordenadas en las que se encuentra y se envian a otra funcion
// para que las imprima en el archivo

#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

const int MAXIMO = 100;

typedef int tMatriz[MAXIMO][MAXIMO];
typedef struct {
    int filas;
    int columnas;
}tPosicion;
typedef struct {
    int max;
    int fila_max;
    int columna_max;
}tDatos;

void resolver(tDatos datos);
bool resuelveCaso();

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

// función que resuelve el problema
void resolver(tDatos datos) {
    cout << datos.max << " " << datos.fila_max << " " << datos.columna_max << endl;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int i = 0, j = 0;
    int numero;
    tPosicion matriz;
    tDatos datos;
    tMatriz mapa;

    cin >> matriz.filas;
    cin >> matriz.columnas;
    cin >> numero;
    datos.max = numero;
    datos.columna_max = j;
    datos.fila_max = i;
    while (i < matriz.filas) {
        j = 0;
        while (j < matriz.columnas) {
            if (numero > datos.max) {
                datos.max = numero;
                datos.fila_max = i;
                datos.columna_max = j;
            }
            mapa[i][j] = numero;
            if ((i != matriz.filas - 1) || (j != matriz.columnas - 1)) {
                cin >> numero;
            }
            j++;
        }
        i++;
    }

    if (!std::cin)  // fin de la entrada
        return false;

    resolver(datos);



    return true;
}

