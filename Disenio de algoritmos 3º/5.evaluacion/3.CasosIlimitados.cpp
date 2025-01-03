
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión y Raúl Arellano Jorge
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase
#include "Solucion.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Para la resolución del problema utilizamos una clase llamada solución que
 recibe un Digrafo en el constructor. En esta clase implementamos un algortimo de 
 recorrido en profundidad con detección de ciclos, viendo así si el grafo es cíclico o no.
 Para determinar si el programa "A VECES" o "SIEMPRE" termina, hemos creado un nodo extra al final del grafo
 el cual se visitará si el último nodo introducido por consola es una 'A' o una 'C'.
 La complejidad del algoritmo es O(V+E) siendo V el numero de vertices, y E el numero de aristas.

 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
   
   // leer los datos de la entrada
    int num;
    cin >> num;
    
   if (!std::cin)  // fin de la entrada
      return false;

   Digrafo g(num+1);

   for (int i = 0; i < num; i++) {
       char a;
       int inst;
       cin >> a;
       if (a == 'A') {
           g.ponArista(i, i+1);
       }
       else if (a == 'J') {
           cin >> inst;
           g.ponArista(i, inst - 1);
       }
       else if (a == 'C') {
           cin >> inst;
           g.ponArista(i, i+1);
           g.ponArista(i, inst - 1);
       }
   }
   
   // resolver el caso posiblemente llamando a otras funciones
   Solucion sol(g);
   // escribir la solución
   if (sol.hayCiclo() && sol.termina()) {
       cout << "A VECES\n";
   }
   else if (sol.hayCiclo() && !sol.termina()) {
       cout << "NUNCA\n";
   }
   else {
       cout << "SIEMPRE\n";
   }


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
