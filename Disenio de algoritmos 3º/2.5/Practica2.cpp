
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge L�pez Carri�n y Ra�l Arellano Jorge
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 El coste es 0(n) porque se recorre una vez

 @ </answer> */

struct candidato {
    int votos;
    int escanios;
    int indice;
};


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
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
    // escribir la soluci�n
    for (int i = 0; i < c; i++) {
        cout << vector[i].escanios << " ";
    }
    cout << "\n";


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
