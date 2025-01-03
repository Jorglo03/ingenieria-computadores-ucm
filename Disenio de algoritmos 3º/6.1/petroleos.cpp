
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge L�pez Carri�n
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "ConjuntosDisjuntos.h"  // propios o los de las estructuras de datos de clase

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

    // leer los datos de la entrada
    int f, c;
    int largestBlobSize = 0; // Tama�o de la mancha m�s grande
    cin >> f >> c;

    if (!std::cin)  // fin de la entrada
        return false;

    ConjuntosDisjuntos cd(f * c);

    vector<vector<char>> mar(f, vector<char>(c));
    char l;
    cin.get(l);
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            cin.get(l);
            mar[i][j] = l;
        }
        cin.get(l);
    }
    
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            // Verificar si la celda es contaminada
            if (mar[i][j] == '#') {
                // Verificar las 8 celdas adyacentes (horizontal, vertical y diagonal)
                const int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
                const int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

                for (int k = 0; k < 8; k++) {
                    int newRow = i + dx[k];
                    int newCol = j + dy[k];

                    // Verificar si la celda adyacente est� dentro de los l�mites y es contaminada
                    if (newRow >= 0 && newRow < f && newCol >= 0 && newCol < c && mar[newRow][newCol] == '#') {
                        // Unir las dos celdas
                        int currentCell = i * c + j;
                        int adjacentCell = newRow * c + newCol;
                        cd.unir(currentCell, adjacentCell);
                    }
                }
                if (largestBlobSize < cd.cardinal(i*c+j))
                   largestBlobSize = cd.cardinal(i * c + j);
            }
        }
    }

    cout << largestBlobSize << " ";

    int e;
    cin >> e;

    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        mar[a][b] = '#';
        // resolver el caso posiblemente llamando a otras funciones
        const int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
        const int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

        for (int k = 0; k < 8; k++) {
            int newRow = a + dx[k];
            int newCol = b + dy[k];

            // Verificar si la celda adyacente est� dentro de los l�mites y es contaminada
            if (newRow >= 0 && newRow < f && newCol >= 0 && newCol < c && mar[newRow][newCol] == '#') {
                // Unir las dos celdas
                int currentCell = a * c + b;
                int adjacentCell = newRow * c + newCol;
                cd.unir(currentCell, adjacentCell);
            }
        }
        if (largestBlobSize < cd.cardinal(a * c + b))
            largestBlobSize = cd.cardinal(a * c + b);
        cout << largestBlobSize << " ";
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
