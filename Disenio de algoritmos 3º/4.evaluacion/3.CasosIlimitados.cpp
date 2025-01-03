
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión y Raúl Arellano Jorge
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
//#include <...>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase
#include "solucion.h"
/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 Para la solución, creamos otra clase .h, que resuelva en el constructor la minima distancia
 desde todas las posiciones de Alex y Lucas y el trabajo, y que al sumarlas, esa misma distancia sea mínima.
 Hacemos un recorrido en anchura, guardando la distancia de cada uno de los componentes
 a todos los vertices y comprobando cual es la menor suma de los tres.

 La complejidad de la solución es O(V+E).

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
   
   // leer los datos de la entrada
    int n, c, lucas, alex, trabajo;
    cin >> n >> c >> lucas >> alex >> trabajo;
   if (!std::cin)  // fin de la entrada
      return false;
   
   Grafo grafo(n);
   // resolver el caso posiblemente llamando a otras funciones
   for (int i = 0; i < c; i++) {
       int v, w;
       cin >> v >> w;
       grafo.ponArista(v - 1, w - 1);
   }

   // escribir la solución
   solucion sol(grafo, lucas, alex, trabajo);
   
   cout << sol.minimo() << endl;

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
