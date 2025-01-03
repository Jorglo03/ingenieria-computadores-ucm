
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge L�pez Carri�n
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
//#include <...>
using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
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
    // escribir la soluci�n
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
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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
