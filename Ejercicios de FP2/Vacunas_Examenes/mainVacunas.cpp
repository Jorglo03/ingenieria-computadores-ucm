

// Examen de FP2 del día 15 de julio ed 2021

// NOMBRE Y APELLIDOS: Jorge López Carrión
// email: jorglo03@ucm.es
// Usuario del juez para realizar el examen: FP2-A64



#include <iostream>
#include <fstream>
using namespace std;
#include "vacunacion.h"

// Función pedida en el examen
void resuelveCaso();


// NO CAMBIAR LA FUNCIÓN MAIN
int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("vacuna_pueblo.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("vacuna_pueblo_2.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}


void resuelveCaso() {    
    tListaVacunas l;

    inicializarListaVAcunas(l);                 // Se llaman a las funciones necesarias para crear el programa
    cargarVacunasCentros(l);
    cout << "Lista de vacunas ordenadas" << endl << "--------------------------" << endl;
    mostrar(l);
    vacunar(l);
    liberarListaCentros(l);
}


