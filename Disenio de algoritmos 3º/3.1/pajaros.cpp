
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;


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


    int edad_inicial, num_parejas;

    cin >> edad_inicial >> num_parejas;


    if (edad_inicial == 0 && num_parejas == 0) {
        return false;
    }

    priority_queue<int> menores;
    priority_queue<int, vector<int>, greater<int>> mayores;  // Cola de prioridad para las edades mayores

    menores.push(edad_inicial);

    for (int i = 0; i < num_parejas; ++i) {
        int nueva_edad1, nueva_edad2;
        cin >> nueva_edad1 >> nueva_edad2;


        if (nueva_edad1 <= menores.top()) {
            menores.push(nueva_edad1);
        }
        else {
            mayores.push(nueva_edad1);
        }

        if (nueva_edad2 <= menores.top()) {
            menores.push(nueva_edad2);
        }
        else {
            mayores.push(nueva_edad2);
        }


        if (menores.size() > mayores.size() + 1) {
            mayores.push(menores.top());
            menores.pop();
        }
        else if (mayores.size() > menores.size()) {
            menores.push(mayores.top());
            mayores.pop();
        }


        int edad_punta = menores.top();

        cout << edad_punta << " ";
    }
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
