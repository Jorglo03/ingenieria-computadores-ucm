
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge L�pez Carri�n
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <deque>
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
    int n, c;
    cin >> n >> c;
    if (!std::cin)  // fin de la entrada
        return false;

    DigrafoValorado<int> dgv(n);
    for (int i = 0; i < c; i++) {
        int v, w, valor;
        cin >> v >> w >> valor;
        AristaDirigida<int> a1(v - 1, w - 1, valor);
        dgv.ponArista(a1);
        AristaDirigida<int> a2(w - 1, v - 1, valor);
        dgv.ponArista(a2);
    }

    // resolver el caso posiblemente llamando a otras funciones
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int origen, destino;
        cin >> origen >> destino;
        Dijkstra<int> d(dgv, origen-1);

        if (d.hayCamino(destino-1)) {
            cout << d.distancia(destino-1);
            deque<AristaDirigida<int>> cola = d.camino_final(destino-1);
            cout << ": ";
            while (!cola.empty()) {
                cout << cola.front().desde()+1;
                if (cola.size() > 1) {
                    cout << " -> ";
                }
                else if (cola.size() == 1){
                    cout << " -> " << cola.front().hasta() + 1;
                }
                cola.pop_front();
            }
            cout << "\n";
        }
        else {
            cout << "NO LLEGA\n";
        }
        
    }
    
    cout << "---\n";
   
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
