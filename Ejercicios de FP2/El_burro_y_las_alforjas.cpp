
// Autor/a: Jorge López Carrión
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado: C++ y Windows 
// Nombre del problema: Burro Alforjas
// Comentario general sobre la solución: se muestra el numero de burros que se han podido cargar, con dos sacos del mismo peso
// explicando como se resuelve el problema: se leen los datos del fichero y se organizan los burros que puedan ser cargados con dos sacos del
// mismo peso, sin que el peso importe.

#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

const int MAXIMO = 100000;
const int MAX_PESO = 20000;

typedef int tDatos[MAX_PESO];

int resolver(tDatos datos);
void resuelveCaso();

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
int resolver(tDatos datos) {
    int num_burros = 0;

    for (int i = 0; i < MAX_PESO; i++) {
        if (datos[i] > 0) {
            num_burros = num_burros + datos[i] / 2;
        }
    }

    return num_burros;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    tDatos datos;
    int burros, sacos, pares, peso;

    for (int i = 0; i < MAX_PESO; i++) {
        datos[i] = 0;
    }

    std::cin >> burros;
    std::cin >> sacos;
    for (int i = 0; i < sacos; i++) {
        std::cin >> peso;
        datos[peso]++;
    }

    pares = resolver(datos);

    if (burros < pares) {
        std::cout << burros << endl;
    }
    else if (burros >= pares) {
        std::cout << pares << endl;
    }
}
