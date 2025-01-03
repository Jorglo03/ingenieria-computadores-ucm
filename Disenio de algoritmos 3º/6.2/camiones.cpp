
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
 //#include <...>
using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "solucion.h"  // propios o los de las estructuras de datos de clase

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
    int v, e;
    cin >> v >> e;
    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> gv(v);
    for (int i = 0; i < e; i++) {
        int v, w, valor;
        cin >> v >> w >> valor;
        Arista<int> arista(v-1, w-1, valor);
        gv.ponArista(arista);
    }
    
    // resolver el caso posiblemente llamando a otras funciones
    
    int c;
    cin >> c;
    for (int i = 0; i < c; i++) {
        int origen, destino, ancho_camion;
        cin >> origen >> destino >> ancho_camion;
        solucion sol(gv, origen-1, ancho_camion);
        if(sol.llega(destino-1)){// escribir la solución
            cout << "SI\n";
        }
        else {
            cout << "NO\n";
        }
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
