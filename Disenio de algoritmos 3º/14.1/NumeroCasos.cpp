
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "ARM_Kruskal.h"  // propios o los de las estructuras de datos de clase
#include "GrafoValorado.h"
/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

void resuelveCaso() {

   // leer los datos de la entrada
    int n, m;
    cin >> n >> m;
    GrafoValorado<int> gv(n);
    for (int i = 0; i < m; i++) {
        int v, w, coste;
        cin >> v >> w >> coste;
        gv.ponArista({v-1,w-1,coste});
    }
   // resolver el caso posiblemente llamando a otras funciones
    ARM_Kruskal<int> arm(gv);
    if(arm.posible())
        cout << arm.costeARM() << endl;
    else {
        cout << "Imposible" << "\n";
    }
   // escribir la solución
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   int numCasos;
   std::cin >> numCasos;
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
