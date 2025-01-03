/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión y Raúl Arellano Jorge
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
 //#include <...>
using namespace std;

#include "TreeSet_AVL.h"  // propios o los de las estructuras de datos de clase


const int MAX = 50000;


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
    int n;
    cin >> n;

    if (n == 0)
        return false;

    Set<int> arbol;
    int dato;
    for (int i = 0; i < n; i++) {
        cin >> dato;
        arbol.insert(dato);
    }
    int m;
    cin >> m;
    int arr[MAX];
    for (int i = 0; i < m; i++) {
        cin >> arr[i];
    }

    // resolver el caso posiblemente llamando a otras funciones 
    // escribir la solución
    for (int i = 0; i < m; i++) {
        try {
            cout << arbol.kesimo(arr[i]) << endl;
        }
        catch (myException) {
            cout << "??\n";
        }
    }
    cout << "---" << endl;



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