
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge L�pez Carri�n
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
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

const int MAX = 10000;
const int INF = 1000000000; // 
int adyacente(int v, int i) {
    switch (i) {
    case 0: return (v + 1) % MAX; // + 1
    case 1: return (v * 2) % MAX; // * 2
    case 2: return v / 3; // / 3
    }
}

int bfs(int origen, int destino) {
    if (origen == destino) return 0;
    vector<int> distancia(MAX, INF);
    distancia[origen] = 0;
    queue<int> cola; cola.push(origen);
    while (!cola.empty()) {
        int v = cola.front();       //saca la cabeza
        cola.pop();
        for (int i = 0; i < 3; ++i) {
            int w = adyacente(v, i);
            if (distancia[w] == INF) {          //si no ha sido visitado
                distancia[w] = distancia[v] + 1;    //su distancia es la de v mas 1 porque en la busqueda se avanza en un vertice mas(para llegar se necesitan los de v mas 1 vertice)
                if (w == destino) return distancia[w];      //distancia[w] es el numero de aristas que se han tenido que recorrer desde origen para llegar al numero
                else cola.push(w);
            }
        }
    }
}


bool resuelveCaso() {
    int origen, destino;
    cin >> origen >> destino;
    if (!cin) return false;
    cout << bfs(origen, destino) << "\n";
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
