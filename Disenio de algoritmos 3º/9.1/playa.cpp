
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


struct Edificio {
    int occidental, oriental;
};

bool compararEdificios(const Edificio& a, const Edificio& b) {
    return a.occidental < b.occidental;
}

int minTuneles(const vector<Edificio>& edificios) {
    vector<Edificio> edificiosOrdenados = edificios;
    sort(edificiosOrdenados.begin(), edificiosOrdenados.end(), compararEdificios);

    int tuneles = 0;
    int extremoOrienteActual = INT_MIN;

    for (const Edificio& edificio : edificiosOrdenados) {
        if (extremoOrienteActual <= edificio.occidental) {
            // Necesitamos construir un nuevo túnel
            tuneles++;
            extremoOrienteActual = edificio.oriental;
        }
        else {
            // No es necesario construir un nuevo túnel, ya que el edificio está cubierto
            extremoOrienteActual = min(extremoOrienteActual, edificio.oriental);
        }
    }

    return tuneles;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int n;
    cin >> n;

    if (n == 0)
        return false;

    vector<Edificio> edificios(n);

    for (int i = 0; i < n; ++i) {
        cin >> edificios[i].occidental >> edificios[i].oriental;
    }
    // resolver el caso posiblemente llamando a otras funciones
    int tuneles = minTuneles(edificios);

    // escribir la solución
    cout << tuneles << endl;

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
