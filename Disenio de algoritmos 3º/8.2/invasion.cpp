
/*@ <answer>
 *
 * nombre y Apellidos: Jorge L�pez Carri�n
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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
    int n;
    cin >> n;
    if (!std::cin)  // fin de la entrada
        return false;

    std::vector<int> efectivosEnemigos(n);
    std::vector<int> efectivosDefensa(n);

    for (int j = 0; j < n; j++) {
        std::cin >> efectivosEnemigos[j];
    }

    for (int j = 0; j < n; j++) {
        std::cin >> efectivosDefensa[j];
    }
    // resolver el caso posiblemente llamando a otras funciones
    std::sort(efectivosEnemigos.begin(), efectivosEnemigos.end());
    std::sort(efectivosDefensa.begin(), efectivosDefensa.end());

    int ciudadesGanadas = 0;
    int j = 0; // �ndice para efectivos de defensa

    for (int i = 0; i < n; i++) {
        while (j < n && efectivosDefensa[j] < efectivosEnemigos[i]) {
            j++;
        }

        if (j < n) {
            ciudadesGanadas++;
            j++; // Mover al siguiente equipo de defensa
        }
    }
    // escribir la soluci�n
    std::cout << ciudadesGanadas << std::endl;

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
