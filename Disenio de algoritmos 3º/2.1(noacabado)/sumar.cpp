
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "queue" // Incluye la biblioteca para priority_queue
using namespace std;

const int MAX = 100000;

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 El coste de la solucion es O(n) ya que se recorren todos los numeros.
 Para solucionar el problema se crea una cola de prioridad en la que el top sea el menor numero
 y a partir de ahi, se va calculando la suma hasta el numero correspondiente, y se va sumando al esfuerzo
 para al final del bucle conseguir el esfuerzo total.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>



int esfuerzo(priority_queue<int, vector<int>, greater<int>> cola) {
    
    int esfuerzo = 0, suma = 0;

    while (cola.size() > 1) {

        suma = cola.top();
        cola.pop();
        suma += cola.top();
        cola.pop();

        esfuerzo += suma;
        

        cola.push(suma);        //para ir poniendo los numeros mas grandes al final
    }



    return esfuerzo;
}



bool resuelveCaso() {

    // leer los datos de la entrada
    priority_queue<int, vector<int>, greater<int>> cola;
    int n, numero;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> numero;
        cola.push(numero);
    }
    if (n == 0)
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    int esfuerzo_total = esfuerzo(cola);

    // escribir la solución
    cout << esfuerzo_total << endl;

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
