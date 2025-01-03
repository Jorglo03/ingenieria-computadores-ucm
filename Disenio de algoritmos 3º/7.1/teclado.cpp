
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

const int N = 1000;

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
    int n;
    cin >> n;
    vector<int> cargas(n);
    if (n == 0)
        return false;
    for (int i = 0; i < n; i++) {
        cin >> cargas[i];
    }

    DigrafoValorado<int> dgv(n);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int v, w, valor;
        cin >> v >> w >> valor;
        AristaDirigida<int> ad(v-1, w-1, valor);
        dgv.ponArista(ad);
    }
    // resolver el caso posiblemente llamando a otras funciones
    Dijkstra<int> d(dgv, 0, cargas);
    if (d.hayCamino(n - 1)) {
        int tiempo_total = cargas[0];
        tiempo_total += d.distancia(n - 1);
        cout << tiempo_total << "\n";
    }
    else {
        cout << "IMPOSIBLE\n";
    }

    // escribir la solución

        

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
