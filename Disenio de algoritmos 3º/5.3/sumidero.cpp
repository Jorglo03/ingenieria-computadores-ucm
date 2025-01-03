
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
//#include <...>
using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

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



    int tareas, relaciones;
    cin >> tareas >> relaciones;
    
    
    
    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo digrafo(tareas), inverso(tareas);
    
    for (int i = 0; i < relaciones; i++) {
        int v, w;
        cin >> v >> w;
        digrafo.ponArista(v, w);
    }

    inverso = digrafo.inverso();

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la solución
    int sol = -1;
    for (int w = 0; w < digrafo.V(); w++) {
        if ((digrafo.ady(w).size() == 0) && (inverso.ady(w).size() == digrafo.V() - 1)) {
            sol = w;
        }

    }

    if (sol == -1) {
        cout << "NO\n";

    }
    else {
        cout << "SI " << sol << "\n";

    }
    

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
