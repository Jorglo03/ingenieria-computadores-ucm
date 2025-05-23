
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge L�pez Carri�n
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;




//#include "..."  // propios o los de las estructuras de datos de clase

const int MAX = 25000;

struct registro {
    int momento;
    int id; // identificador (se utiliza en caso de empate)
    int periodo; // tiempo entre consultas
};

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

bool operator<(registro const& a, registro const& b) {
    return b.momento < a.momento ||
        (a.momento == b.momento && b.id < a.id);
}

bool resuelveCaso() {
    int N; // n�mero de usuarios registrados
    cin >> N;
    if (N == 0) return false; // no hay m�s casos
    priority_queue<registro> cola;
    // leemos los registros
    for (int i = 0; i < N; ++i) {
        int id_usu, periodo;
        cin >> id_usu >> periodo;
        cola.push({ periodo, id_usu, periodo });
    }

    int envios; // n�mero de env�os a mostrar
    cin >> envios;
    while (envios--) {
        auto e = cola.top();
        cola.pop();
        cout << e.id << '\n';
        e.momento += e.periodo;
        cola.push(e);
    }
    cout << "---\n";
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
