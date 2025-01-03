
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge L�pez Carri�n
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

    // escribir la soluci�n

        

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
