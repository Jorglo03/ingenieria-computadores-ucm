
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>

using namespace std;

#include "DiGrafoValorado.h"  // propios o los de las estructuras de datos de clase
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
    int n, s, t, p;
    cin >> n >> s >> t >> p;
   if (!std::cin)  // fin de la entrada
      return false;
   DigrafoValorado<int> dgv(n);
   for (int i = 0; i < p; i++) {
       int v, w, tiempo;
       cin >> v >> w >> tiempo;
       dgv.ponArista({ w-1,v-1,tiempo });
   }
   // resolver el caso posiblemente llamando a otras funciones
   Dijkstra<int> d(dgv, s-1);
   int sol = -1;
   for (int i = 0; i < n; i++) {
       if (d.distancia(i) <= t && d.hayCamino(i)) {
           sol++;
       }
   }

   // escribir la solución
   cout << sol << endl;

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
