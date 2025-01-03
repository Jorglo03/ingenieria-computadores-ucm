
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge L�pez Carri�n
 *
 *@ </answer> */

#include <iostream>
#include <fstream>

using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "Dijkstra.h"

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
    int i, c;
    cin >> i;
    if (!std::cin)  // fin de la entrada
        return false;

    cin >> c;
    
    DigrafoValorado<int> dgv(i);

    for (int i = 0; i < c; i++) {
        int v, w, valor;
        cin >> v >> w >> valor;
        AristaDirigida<int> ad1(v-1, w-1, valor);
        AristaDirigida<int> ad2(w-1, v-1, valor);
        dgv.ponArista(ad1);
        dgv.ponArista(ad2);
    }
    // resolver el caso posiblemente llamando a otras funciones
    Dijkstra<int> d(dgv, 0);
    // escribir la soluci�n
    cout << d.maneras_func(i-1) << "\n";
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
