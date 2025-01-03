
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión y Raúl Arellano Jorge
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
//#include <...>
using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "Solucion.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Para solucionar el ejercicio, utilizaremos una reperesentación de las ciudades y sus carreteras mediante grafos valorados.
 Una vez con el grafo creado, utilizamos una clase "Solucion", la cual contiene el código para la resolución del ejercicio.
 En esta clase utilizamos un algortimo de Kruskal para encontrar el ARM y así saber el coste menor de combustible necesario
 para llegar a todas las ciudades, sabiendo que en cada ciudad se reposta.
 
 La complejidad del ejercicio es O(m log m) siendo m el número de carreteras.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

    // leer los datos de la entrada
    int n, m;
    cin >> n >> m;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> gv(n);
    for (int i = 0; i < m; i++) {
        int v, w, valor;
        cin >> v >> w >> valor;
        Arista<int> a(v-1,w-1,valor);
        gv.ponArista(a);
    }
    // resolver el caso posiblemente llamando a otras funciones
    Solucion<int> s(gv);
    // escribir la solución
    if (s.func_termina()) {
        cout << s.costeARM() << "\n";
    }
    else {
        cout << "Imposible\n";
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
