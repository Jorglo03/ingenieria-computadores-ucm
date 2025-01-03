
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

struct registro {
    string nombre;
    int gravedad;
    int antiguedad;
};

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 El coste es lineal porque se recorren todos los usuarios O(n).
 Se van leyendo los usuarios y conforme se van leyendo, modificando el operador <, se van insertando en el orden
 correspondiente a la cola de prioridad, para que vayan saliendo en el orden pedido para la solucion.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool operator<(registro const& a, registro const& b) {
    return a.gravedad < b.gravedad || (a.gravedad == b.gravedad && a.antiguedad > b.antiguedad);
}


bool resuelveCaso() {

    // leer los datos de la entrada
    int n;
    cin >> n;

    registro usuario;
    priority_queue<registro> cola;
    char letra;
    string nombre;
    if (n == 0)
        return false;
    
    // resolver el caso posiblemente llamando a otras funciones
    for (int i = 0; i < n; i++) {
        cin >> letra;
        if (letra == 'I') {
            cin >> usuario.nombre;
            cin >> usuario.gravedad;
            usuario.antiguedad = i;
            cola.push(usuario);
        }
        else if (letra == 'A') {
            cout << cola.top().nombre << endl;// escribir la solución
            cola.pop();
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
