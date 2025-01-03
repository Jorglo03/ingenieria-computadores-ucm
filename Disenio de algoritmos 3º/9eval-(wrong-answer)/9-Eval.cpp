/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión y Raúl Arellano Jorge
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "Solucion.h"  // propios o los de las estructuras de datos de clase

using namespace std;

typedef struct {
    int pueblo;
    int dist;
}Pueblo;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 El coste del algoritmo esta en el orden de O(n log n)
 Leemos todos los datos y ponemos las aristas en las dos direcciones ya que las carreteras se pueden recorrer en ambas direcciones.
 Hacemos Dijkstra desde las dos plantas, que son la 0 y n-1, desde los cuales se sacan los vectores de distancias minimas.
 Se guardan en un vector la diferecia de distancias entre cada pueblo y las dos plantas y se ordenan de mayor a menor-
 Finalmente, se va buscando que se vaya cogiendo la que tiene menor con respecto a una de las dos plantas, en la que
 hay mayor diferencia de distancia, hasta que una de las dos plantas haya cubierto la mitad, y ya se insertan todas en la otra

 Para la demostracion por reduccion de diferencia:
 Supongamos que existe una solución óptima diferente que selecciona una configuración diferente de la mitad
 de los pueblos.
 Identifiquemos el primer pueblo en el que las soluciones voraz y óptima no son iguales.
 Supongamos que este es el pueblo i.
 Construyamos una nueva solución que sea igual a la solución voraz hasta el pueblo i y luego utilice 
 la configuración óptima a partir del pueblo i+1.
 Comparemos las distancias totales de ambas soluciones.
 Para los pueblos hasta i, ambas soluciones son iguales porque hasta este punto, están basadas en
 la solución voraz.
 Para los pueblos desde i+1, la solución óptima no puede ser mejor que la solución voraz porque el 
 algoritmo voraz selecciona las mitades más grandes en términos de distancias absolutas.
 Hemos demostrado que la nueva solución es al menos tan buena como la solución voraz. 
 Esto contradice la suposición de que existe una solución óptima diferente.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool operator>(const Pueblo& p1, const Pueblo& p2) {
    return p1.dist > p2.dist;
}


bool resuelveCaso() {

    // leer los datos de la entrada
    int n, m;
    cin >> n >> m;

    if (!std::cin)  // fin de la entrada
        return false;
    DigrafoValorado<int> dgv(n);
    for (int i = 0; i < m; i++) {
        int v, w, valor;
        cin >> v >> w >> valor;
        dgv.ponArista({ v - 1,w - 1,valor });
        dgv.ponArista({ w - 1,v - 1,valor });
    }
    // resolver el caso posiblemente llamando a otras funciones
    Solucion<int> s1(dgv, 0);
    Solucion<int> s2(dgv, n - 1);
    vector<int> v_norte = s1.vect();
    vector<int> v_sur = s2.vect();
    vector<Pueblo> dist_abs(n - 2);

    for (int i = 0; i < n - 2; i++) {
        dist_abs[i].dist = abs(v_norte[i + 1] - v_sur[i + 1]);
        dist_abs[i].pueblo = i + 1;
    }

    sort(dist_abs.begin(), dist_abs.end(), greater<Pueblo>());

    long long suma = 0;

    int num_pueblos_norte = 0, num_pueblos_sur = 0;

    for (int i = 0; i < n - 2; i++) {
        int pueblo = dist_abs[i].pueblo;
        int distancia_norte = v_norte[pueblo];
        int distancia_sur = v_sur[pueblo];

        if (num_pueblos_sur >= ((n - 2) / 2)) { //sur
            num_pueblos_norte++;
            suma += distancia_norte;
        }
        else if (num_pueblos_norte >= ((n - 2) / 2)) { // norte
            num_pueblos_sur++;
            suma += distancia_sur;
        }
        else {
            if (distancia_norte < distancia_sur) { //norte
                num_pueblos_norte++;
                suma += distancia_norte;
            }
            else {              //sur
                num_pueblos_sur++;
                suma += distancia_sur;
            }
        }
    }

    // escribir la solución
    cout << suma * 2 << "\n";
    
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