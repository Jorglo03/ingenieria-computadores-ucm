
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge L�pez Carri�n y Ra�l Arellano Jorge
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
//#include <...>
using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "Solucion.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Para solucionar el ejercicio, utilizaremos una reperesentaci�n de las ciudades y sus carreteras mediante grafos valorados.
 Una vez con el grafo creado, utilizamos una clase "Solucion", la cual contiene el c�digo para la resoluci�n del ejercicio.
 En esta clase utilizamos un algortimo de Kruskal para encontrar el ARM y as� saber el coste menor de combustible necesario
 para llegar a todas las ciudades, sabiendo que en cada ciudad se reposta.
 
 La complejidad del ejercicio es O(m log m) siendo m el n�mero de carreteras.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
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
    // escribir la soluci�n
    if (s.func_termina()) {
        cout << s.costeARM() << "\n";
    }
    else {
        cout << "Imposible\n";
    }

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
