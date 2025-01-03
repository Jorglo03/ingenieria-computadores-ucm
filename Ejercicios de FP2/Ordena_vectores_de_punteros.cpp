// Autor/a: Jorge López Carrión
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado: Visual Studio 2019 y Windows
// Nombre del problema: Ordena vectores de punteros (Implementación con memoria dinámica)
/* Comentario general sobre la solución explicando como se resuelve el problema: Se crea en memoria dinamica un array de punteros
 tras leerse el numero de casos. Se leen todos los datos restantes y se van guardando. Se ordena y se muestran los datos con el formato dado
 y finalmente se libera la memoria y los punteros apuntan a nullptr. */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX = 50;                 //Declaracion de constantes necesarias
const int MAX1 = 200;

typedef int tMatriz[MAX][MAX];      //Declarancion de los tipos necesarios
typedef struct {
    string titulo;
    string tema;
    tMatriz matriz;
}tFoto;


bool resuelveCaso();                //Declaracion de los prototipos de las funciones
void ordenarTitulo(tFoto* arrayPtr, int numCasos);
void ordenarTema(tFoto* arrayPtr, int numCasos);

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


bool resuelveCaso() {
    int numCasos;
    char aux;
    string prueba;
    cin >> numCasos;
    cin.get(aux);

    tFoto* arrayPtr = new tFoto[numCasos];        //Se crea en memoria dinamica 2 vectores dinamicos de punteros
    tFoto* arrayPtr2 = new tFoto[numCasos];

    while (numCasos != 0) {
        for (int i = 0; i < numCasos; i++) {
            for (int j = 0; j < MAX; j++) {
                for (int k = 0; k < MAX; k++) {
                    arrayPtr[i].matriz[j][k] = 3;      //Se igualan todos los datos de la matriz a 3
                    arrayPtr2[i].matriz[j][k] = 3;
                }
            }
        }
        for (int i = 0; i < numCasos; i++) {
            getline(cin, arrayPtr[i].titulo);         //Se leen los datos
            arrayPtr2[i].titulo = arrayPtr[i].titulo;
        }
        for (int i = 0; i < numCasos; i++) {
            getline(cin, arrayPtr[i].tema);            //Se leen los datos
            arrayPtr2[i].tema = arrayPtr[i].tema;
        }


        ordenarTitulo(arrayPtr, numCasos);              //Se ordenan por titulo
        for (int i = 0; i < numCasos; i++) {            //Y se muestran
            cout << arrayPtr[i].titulo << endl;
        }
        cout << endl;

        ordenarTitulo(arrayPtr2, numCasos);
        ordenarTema(arrayPtr2, numCasos);               //Se ordenan por tema principalmente, y luego por titulo

        for (int i = 0; i < numCasos; i++) {            //Y se muestran
            cout << arrayPtr2[i].tema << " - " << arrayPtr2[i].titulo << endl;
        }
        cout << endl;

        cin >> numCasos;
        cin.get(aux);
    }

    delete[] arrayPtr2;           //Se libera la memoria
    arrayPtr2 = nullptr;
    delete[] arrayPtr;
    arrayPtr = nullptr;


    if (numCasos == 0)
        return false;

    return true;
}

void ordenarTitulo(tFoto* arrayPtr, int numCasos) {
    tFoto aux;

    for (int i = 0; i < numCasos; i++) {                    //Se ordenan por el metodo de burbuja los titulos de las fotos
        for (int j = 0; j < numCasos - 1; j++) {
            if (arrayPtr[j].titulo.compare(arrayPtr[j + 1].titulo) > 0) {
                aux = arrayPtr[j];
                arrayPtr[j] = arrayPtr[j + 1];
                arrayPtr[j + 1] = aux;
            }
        }
    }
}

void ordenarTema(tFoto* arrayPtr, int numCasos) {
    tFoto aux;

    for (int i = 0; i < numCasos; i++) {                    //Se ordenan por el metodo de burbuja los temas de las fotos
        for (int j = 0; j < numCasos - 1; j++) {
            if (arrayPtr[j].tema.compare(arrayPtr[j + 1].tema) > 0) {
                aux = arrayPtr[j];
                arrayPtr[j] = arrayPtr[j + 1];
                arrayPtr[j + 1] = aux;
            }
        }
    }
}
