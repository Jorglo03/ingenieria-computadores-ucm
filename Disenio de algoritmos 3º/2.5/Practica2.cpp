
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión y Raúl Arellano Jorge
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El coste es 0(n) porque se recorre una vez

 @ </answer> */

struct candidato {
    int votos;
    int escanios;
    int indice;
};


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool operator<(candidato const& a, candidato const& b) {
    return (a.votos * (1 + b.escanios) < b.votos * (1 + a.escanios))
        || (a.votos * (1 + b.escanios) == b.votos * (1 + a.votos) && a.votos < b.votos)
        || (a.votos * (1 + b.escanios) == b.votos * (1 + a.votos) && a.votos == b.votos && a.indice > b.indice);
}


bool resuelveCaso() {

    // leer los datos de la entrada
    int c, n;
    cin >> c >> n;

    priority_queue<candidato> cola;
    vector<candidato> vector(c);
    candidato aux;
    
    if (c == 0 && n == 0)
        return false;
    
   

    for (int i = 0; i < c; i++) {
        cin >> aux.votos;
        aux.indice = i;
        aux.escanios = 0;
        vector[i].escanios = 0;
        cola.push(aux);
    }

    // resolver el caso posiblemente llamando a otras funciones
    for (int i = 0; i < n; i++) {
        aux = cola.top();
        aux.escanios++;
        cola.pop();
        vector[aux.indice].escanios++;
        cola.push(aux);
    }
    // escribir la solución
    for (int i = 0; i < c; i++) {
        cout << vector[i].escanios << " ";
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
