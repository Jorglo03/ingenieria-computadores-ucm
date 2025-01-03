
// Examen de FP2 del día 8 de junio ed 2021

// Nombre y apellidos: Jorge López Carrión	
// Grupo: 1ºA
// email: jorglo03@ucm.es
// Usuario del juez para realizar el examen: FP2-A64


#include <fstream>
#include <iostream>
using namespace std;

#include "Oposiciones.h"


bool resuelveCaso();


// NO CAMBIAR LA FUNCIÓN MAIN
int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("opositores.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("opositores_2.out");
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



bool resuelveCaso() {
    tListaOpositores opositores;
    tListaAprobPlaza aprobados;
    int numPlazas, j;
    float suma = 0;
    aprobados.contador = 0;

    cargarOpositores(opositores,numPlazas);                         //Se cargan los datos

    for (int i = 0; i < opositores.contador; i++) {                 //Se calcula la media de las calificaciones de cada opositor
        if (opositores.opositor[i]->aprobados == MAX_EJERCICIOS) {
            j = 0;
            suma = 0;
            while (j < MAX_EJERCICIOS) {
                suma = suma + opositores.opositor[i]->notas[j];
                j++;
            }
            opositores.opositor[i]->mediaCalificaciones = suma / 7;
        }
        else {
            opositores.opositor[i]->mediaCalificaciones = 0;
        }
    }
        
    ordenar(opositores);                                            //Se ordenan los opositores de mayor a menor media

    cout << "Lista con todos los opositores ordenados por calific. media" << endl << endl;
    mostrarListaOpositores(opositores);                             //Se muestra la lista de opositores
    
    candidatosConPlaza(aprobados, opositores, numPlazas);           //Se organizan los candidatos con plaza
    
    cout <<"Lista de opositores que no tienen plaza y suspensos" << endl << endl;
    mostrarListaOpositores(opositores);                             //Se muestra la lista de opositores
    cout << endl << "Lista de opositores que tienen plaza" << endl << endl;
    mostrarAprobadosConPlaza(aprobados);                            //Se muestra la lista de aprobados con plaza

    liberarListaOpositores(opositores);                             //Se libera toda la memoria solicitada
    LiberarListaAprobados(aprobados);
    
    return true;
}
