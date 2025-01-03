
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
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

bool resuelveCaso() {

    // leer los datos de la entrada
    int n, l;
    cin >> n >> l;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> agujeros(n);

    for (int i = 0; i < n; i++) {
        cin >> agujeros[i];
    }

    // resolver el caso posiblemente llamando a otras funciones
    int parchesNecesarios = 0;
    int posicionActual = 0; // La posición actual en la manguera

    for (int i = 0; i < n; i++) {
        if (agujeros[i] > posicionActual) {
            // Colocar un parche en la posición actual
            posicionActual = agujeros[i] + l;
            parchesNecesarios++;
        }
    }
    // escribir la solución
    cout << parchesNecesarios << endl;

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
