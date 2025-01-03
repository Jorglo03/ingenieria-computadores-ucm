
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión y Raúl Arellano Jorge
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 El coste del algoritmo esta en 0(n*m) y el coste en espacio es O(n*m).

 Para resolver el ejercicio usamos programación dinámica descendente. 
 Creamos un algoritmo recursivo en el que almacenamos en una matriz las formas ya calculadas
 para no recalular lo mismo de nuevo.

 En cada llamada recursiva comprobamos un caso base que es  si hemos llegado ya a la 
 posición (n,m).
 También comprobamos si ya hemos calculado esa forma y si es así la retornamos directamente.
 Los casos recursivos comprueban primero si está en rango la casilla a la que queremos saltar,
 si esto se cumple, se llama recursivamente a la función.

 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int num_formas(const int& i,const int& j, Matriz<int>& formas, const Matriz<int>& datos) {
    if (i == datos.numfils() - 1 && j == datos.numcols() - 1) 
        return 1;

    if (formas[i][j] != -1)
        return formas[i][j];
    
    formas[i][j] = 0;

    if (i + datos[i][j] >= 0 && i + datos[i][j] < datos.numfils()) {
        formas[i][j] += num_formas(i + datos[i][j], j, formas, datos);
    }
    if (j + datos[i][j] >= 0 && j + datos[i][j] < datos.numcols()) {
        formas[i][j] += num_formas(i, j + datos[i][j], formas, datos);
    }
    return formas[i][j];
}


bool resuelveCaso() {
   
   // leer los datos de la entrada
    int n, m;
    cin >> n >> m;

   if (!std::cin)  // fin de la entrada
      return false;

   Matriz<int> datos(n, m);
   Matriz<int> formas(n, m, -1);

   for (int i = 0; i < n; i++) {
       for (int j = 0; j < m; j++) {
           cin >> datos[i][j];
       }
   }
   cout << num_formas(0, 0, formas, datos) << "\n";

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
