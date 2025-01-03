
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión
 *
 *@ </answer> */

#include <iostream>
#include <fstream>

using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "ARM_Kruskal.h"  // propios o los de las estructuras de datos de clase

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
    int n, m, a;
    cin >> n >> m >> a;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> gv(n);
    for (int i = 0; i < m; i++) {
        int x, y, coste;
        cin >> x >> y >> coste;
        Arista<int> a(x-1, y-1, coste);
        gv.ponArista(a);
    }
   
    
    // resolver el caso posiblemente llamando a otras funciones
    ARM_Kruskal<int> arm(gv, a);

    // escribir la solución
    cout << arm.costeARM() << " " << arm.numAeropuerto() << "\n";

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
