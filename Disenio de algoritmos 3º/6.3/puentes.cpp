
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>

using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "ARM_Kruskal.h"  // propios o los de las estructuras de datos de clase

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
    int i, p;
    cin >> i >> p;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> gv(i);
    for (int i = 0; i < p; i++) {
        int v, w, coste;
        cin >> v >> w >> coste;
        Arista<int> a(v-1, w-1, coste);
        gv.ponArista(a);
    }
    
    // resolver el caso posiblemente llamando a otras funciones

    ARM_Kruskal<int> arm(gv);
    if (arm.recorrido_entero_funct()) {
        cout << arm.costeARM() << "\n";
    }
    else {
        cout << "No hay puentes suficientes\n";
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
