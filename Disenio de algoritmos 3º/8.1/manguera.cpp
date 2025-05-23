
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge L�pez Carri�n
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

    // leer los datos de la entrada
    int n, l;
    cin >> n >> l;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> agujeros(n);

    for (int i = 0; i < n; i++) {
        cin >> agujeros[i];
    }

    // resolver el caso posiblemente llamando a otras funciones
    int parchesNecesarios = 0;
    int posicionActual = 0; // La posici�n actual en la manguera

    for (int i = 0; i < n; i++) {
        if (agujeros[i] > posicionActual) {
            // Colocar un parche en la posici�n actual
            posicionActual = agujeros[i] + l;
            parchesNecesarios++;
        }
    }
    // escribir la soluci�n
    cout << parchesNecesarios << endl;

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
