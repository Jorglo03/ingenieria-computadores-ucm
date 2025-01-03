
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
//#include <...>
using namespace std;

#include "BinTree.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El coste de la solucion es O(n) ya que se recorren todos los nodos del arbol
 El problema se revuelve tomando como caso base cuando el nodo tiene un solo elemento y se inicializa
 la altura a uno y el maximo y el minimo del arbol a partir de ese nodo como el numero del propio nodo
 En el caso recursivo, se hacen las llamadas recursivas al arbol derecho e izquierdo si no estan vacios, y si 
 lo estan, se inicializan las alturas y el maximo y el minimo del arbol. A continuacion, se hacen las 
 comprobaciones pertinentes para ver si hasta ese momento el arbol es AVL, y finalmente se reestablece
 la altura y el maximo y el minimo, para que al volver de la llamada recursiva tenga los datos correctos

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


void treeAVL(const BinTree<int>& arbol, int& altura, bool& es, int& minimo, int& maximo) {
    if (arbol.left().empty() && arbol.right().empty()) {            //CASO BASE
        altura = 1;
        minimo = arbol.root();
        maximo = arbol.root();
    }
    else {                          //CASO RECURSIVO
        int altura_izq, altura_der, maximo_izq, maximo_der, minimo_izq, minimo_der;
        if (es) {
            if (!arbol.left().empty()) {
                treeAVL(arbol.left(), altura_izq, es, minimo_izq, maximo_izq);
            }
            else {
                altura_izq = 0;
                maximo_izq = arbol.root();
                minimo_izq = arbol.root();
            }
            if (!arbol.right().empty()) {
                treeAVL(arbol.right(), altura_der, es, minimo_der, maximo_der);
            }
            else {
                altura_der = 0;
                maximo_der = arbol.root();
                minimo_der = arbol.root();
            }

            if (!arbol.left().empty()) {
                if (maximo_izq >= arbol.root()) {
                    es = false;
                }
            }

            if (!arbol.right().empty()) {
                if (minimo_der <= arbol.root()) {
                    es = false;
                }
            }
            if (abs(altura_der-altura_izq) > 1) {
                es = false;
            }

            altura = max(altura_der, altura_izq) + 1;
            maximo = max(maximo_izq, maximo_der);
            minimo = min(minimo_izq, minimo_der);
        }
    }
}

void resuelveCaso() {

    
    // leer los datos de la entrada
    BinTree<int> arbol = read_tree<int>(cin);
    bool esAVL = true;
    int altura = 0;
    int maximo, minimo;

    // resolver el caso posiblemente llamando a otras funciones
    if(!arbol.empty())
        treeAVL(arbol,altura, esAVL, maximo, minimo);

    // escribir la solución
    if (esAVL) {
        cout << "SI" << endl;
    }
    else {
        cout << "NO" << endl;
    }
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
