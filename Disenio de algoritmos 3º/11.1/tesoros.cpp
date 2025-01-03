
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

struct Tesoro {
    int profundidad;
    int oro;
};
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int tesoro_rec(vector<Tesoro> const& obj, int i, int j,
    Matriz<int>& caja) {
    if (caja[i][j] != -1) // subproblema ya resuelto
        return caja[i][j];
    if (i == 0 || j == 0) caja[i][j] = 0;
    else if (obj[i - 1].profundidad*3 > j)
        caja[i][j] = tesoro_rec(obj, i - 1, j, caja);
    else
        caja[i][j] = max(tesoro_rec(obj, i - 1, j, caja),
            tesoro_rec(obj, i - 1, j - obj[i - 1].profundidad*3, caja)
            + obj[i - 1].oro);
    return caja[i][j];
}


int capacidad(vector<Tesoro> const& objetos, int M, vector<bool>& sol, int& num_tesoros) {
    int n = objetos.size();
    Matriz<int> caja(n + 1, M + 1, -1);
    int valor = tesoro_rec(objetos, n, M, caja);
    // cálculo de los objetos
    int i = n, j = M;
    sol = vector<bool>(n, false);
    while (i > 0 && j > 0) {
        if (caja[i][j] != caja[i - 1][j]) {
            num_tesoros++;
            sol[i - 1] = true;
            j = j - objetos[i - 1].profundidad*3;
        }
        --i;
    }
    return valor;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int t, n;
    cin >> t >> n;
    if (!std::cin)  // fin de la entrada
        return false;
    vector<Tesoro> tesoros(n);
    vector<bool> sol(n);
    for (int i = 0; i < n; i++) {
        cin >> tesoros[i].profundidad >> tesoros[i].oro;
    }
    // resolver el caso posiblemente llamando a otras funciones
    int num_tesoros = 0, cantidad;
    cantidad = capacidad(tesoros, t, sol, num_tesoros);
    cout << cantidad << "\n" << num_tesoros << "\n";  // escribir la solución
    for (int i = 0; i < n; i++) {
        if(sol[i]){
            cout << tesoros[i].profundidad << " " << tesoros[i].oro << "\n";;
        }
    }
    cout << "---\n";

   

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
