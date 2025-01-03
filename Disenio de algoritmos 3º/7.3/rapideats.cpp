
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
//#include <...>
using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "Dijkstra.h"

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
    int n, c;
    cin >> n >> c;
    if (!std::cin)  // fin de la entrada
        return false;

    DigrafoValorado<int> dgv(n);
    for (int i = 0; i < c; i++) {
        int v, w, valor;
        cin >> v >> w >> valor;
        AristaDirigida<int> ad1(v - 1, w - 1, valor);
        AristaDirigida<int> ad2(w - 1, v - 1, valor);
        dgv.ponArista(ad1);
        dgv.ponArista(ad2);
    }
    // resolver el caso posiblemente llamando a otras funciones
    int entregas;
    cin >> entregas;
    for (int i = 0; i < entregas; i++) {
        int origen, destino;
        cin >> origen >> destino;
        Dijkstra<int> d(dgv, origen-1);
        if (d.hayCamino(destino-1)) {   // escribir la solución
            cout << d.distancia(destino - 1) << "\n";
        }
        else {
            cout << "NO LLEGA\n";
        }
    }
    cout << "---\n";
   

    

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
