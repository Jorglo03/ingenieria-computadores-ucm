
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión y Raúl Arellano Jorge
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 El coste temporal esta en el orden de 0(n*m) siendo n = group1.size(); y m = group2.size();
 El coste en espacio esta en el orden de 0(n*m) siendo n = group1.size(); y m = group2.size();

 Las ecuaciones de recurrencia son las siguientes:
                 |  dp[i-1][j-1] + 1 si group1[i-1] = group2[j-1]
    dp[i][j] =   |
                 |  max(dp[i-1][j], dp[i][j-1]) si group1[i-1] != group2[j-1]

En la matriz dp vamos guardando la longitud maxima de la lista de reproduccion considerando 
los primeros i elementos del group1 y los primeros j elemntos del group2.
En la funcion solve, lo primero que hacemos es crear la matriz.
Luego la relleneamos calculando asi la longuitud maxima posible de la lista.
A continuación, creamos el vector de strings a devolver en la funcion (playlist),
rellenando el vector , empezando con la matriz desde la esquina inferior derecha, e
introduciendo las canciones de la manera mas optima a el vector playlist.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

vector<string> solve(vector<string>& group1, vector<string>& group2) {

    // Construye una matriz para almacenar la longitud máxima de la lista
    int n = group1.size();
    int m = group2.size();

    Matriz<int> dp(n + 1,m + 1, 0);
    // Calcula la longitud máxima posible de la lista

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {

            if (group1[i - 1] == group2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    // Reconstruye la lista de reproducción
    int i = n, j = m;
    vector<string> playlist;

    while (i > 0 && j > 0) {

        if (group1[i - 1] == group2[j - 1]) {
            playlist.push_back(group1[i - 1]);
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }
    return playlist;
}

bool resuelveCaso() {
   
   // leer los datos de la entrada
    
    string secuencia1, secuencia2, p;
    getline(cin, secuencia1);
   if (!std::cin)  // fin de la entrada
      return false;
   vector<string> v1, v2;
   stringstream ss(secuencia1);
   while (ss >> p) {
       v1.push_back(p);
   }
   getline(cin, secuencia2);
   stringstream ss2(secuencia2);
   while (ss2 >> p) {
       v2.push_back(p);
   }
   // resolver el caso posiblemente llamando a otras funciones
 
   vector<string> sol;
   sol = solve(v1, v2);

   // escribir la solución
   for (int i = sol.size() - 1; i >= 0; i--) {
       cout << sol[i] << " ";
   }
   cout << "\n";
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
