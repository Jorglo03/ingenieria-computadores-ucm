
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


int contarFormas(int k, int s) {
    // Inicializar un vector para almacenar los resultados parciales
    // dp[i] representará el número de formas de obtener la suma s
    // usando números del 1 al k
    vector<int> dp(s + 1, 0);

    // Caso base: hay una sola forma de obtener la suma 0 (no usar ningún número)
    dp[0] = 1;

    // Calcular dinámicamente las formas de obtener cada suma
    for (int i = 1; i <= k; ++i) {
        for (int j = i; j <= s; ++j) {
            dp[j] = (dp[j] + dp[j - i]);
        }
    }

    return dp[s];
}


void resuelveCaso() {
   
   // leer los datos de la entrada
    int k, s;
    cin >> k >> s;

    int formas = contarFormas(k, s);
    cout << formas << endl;
   // resolver el caso posiblemente llamando a otras funciones
   
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
