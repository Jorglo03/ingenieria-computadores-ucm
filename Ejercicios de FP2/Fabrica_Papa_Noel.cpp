
// Autor/a: Jorge López Carrión
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado: C++ y Windows
// Nombre del problema: La fábrica de juguetes de Papa Noel
// Comentario general sobre la solución
// explicando como se resuelve el problema: Se crean las funciones para sobrecargar los operadores y se aplican en el int main para leer las matrices, multiplicar las dos matrices
// e imprimir el resultado

#include <iostream>
#include <fstream>

using namespace std;

const int MAX = 100;                //Se declaran las constantes necesarias

typedef int tMatriz[MAX][MAX];              //Se declaran los tipos definidos
typedef struct {
    int columnas;
    int filas;
    tMatriz matriz;
}tmatriz;

tmatriz operator* (tmatriz const& a, tmatriz const& b);         //Se declaran las funciones necesarias
istream& operator>> (istream& in, tmatriz& m);
ostream& operator<< (ostream& out, tmatriz const& m);
bool resuelveCaso();

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    tmatriz matrizA, matrizB, matrizC;

    cin >> matrizA;                                     //Se leen las matrices
    if (!std::cin)  // fin de la entrada
        return false;
    cin >> matrizB;
    
    matrizC = matrizA * matrizB;                    //Se multiplican las matrices
    
    cout << matrizC;                            //Se imprimen las matrices
    

    return true;
}

tmatriz operator* (tmatriz const& a, tmatriz const& b) {
    tmatriz c;
    c.filas = a.filas;
    c.columnas = b.columnas;

    for (int i = 0; i < a.filas; i++) {                 //Se multiplican las dos matrices
        for (int j = 0; j < b.columnas; j++) {
            c.matriz[i][j] = 0;
            for (int k = 0; k < a.columnas; k++) {
                c.matriz[i][j] = c.matriz[i][j] + a.matriz[i][k] * b.matriz[k][j];      //Se van sumando los elementos necesarios para obtener c como producto de ambas matrices
            }
        }
    }

    return c;
}

istream& operator>> (istream& in, tmatriz& m) {

    in >> m.filas >>  m.columnas;           //Se leen las flas y columnas
    for (int i = 0; i < m.filas; i++) {
        for (int j = 0; j < m.columnas; j++) {
            in >> m.matriz[i][j];               //Se lee la matriz
        }
    }

    return in;
}

ostream& operator<< (ostream& out, tmatriz const& m) {
        
    for (int i = 0; i < m.filas; i++) { 
        for (int j = 0; j < m.columnas; j++) {
            out << m.matriz[i][j];              //Se imprime la matriz en el fichero
            if (j != m.columnas - 1) {
                out << " ";
            }
        }
        out << endl;
    }
    out << endl;

    return out;
}