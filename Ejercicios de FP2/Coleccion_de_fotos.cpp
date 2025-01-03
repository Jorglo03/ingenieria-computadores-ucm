
// Autor/a: Jorge López Carrión
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado: Visual Studio 2019 y Windows
// Nombre del problema: Colección de fotos (implementación con vectores)
/* Comentario general sobre la solución explicando como se resuelve el problema: Se leen el numero de casos, se asigna a cada foto un
espacio en memoria , se leen los titulos y los temas de las fotos y se ordenan segun indica el ejercicio. Se muestran los datos con el
formato dado.*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX = 50;
const int MAX1 = 200;

typedef int tMatriz[MAX][MAX];
typedef struct {
    string titulo;
    string tema;
    tMatriz matriz;
}tFoto;
typedef tFoto *tColeccion[MAX1];

bool resuelveCaso();
void ordenarTitulo(tColeccion& puntero, int numCasos);
void ordenarTema(tColeccion& arrayPtr, int numCasos);

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
    tColeccion arrayPtr;
    tColeccion arrayPtr2;
    int numCasos;
    char aux;

    cin >> numCasos;
    cin.get(aux);

    while (numCasos != 0) {
        for (int i = 0; i < numCasos; i++) {
            arrayPtr[i] = new tFoto;                    //Se reserva espacio en memoria
            arrayPtr2[i] = new tFoto;
            getline(cin, arrayPtr[i]->titulo);          //Se leen los datos
            arrayPtr2[i]->titulo = arrayPtr[i]->titulo;
        }
        for (int i = 0; i < numCasos; i++) {
            getline(cin, arrayPtr[i]->tema);            //Se leen los datos
            arrayPtr2[i]->tema = arrayPtr[i]->tema;
        }
        for (int i = 0; i < numCasos; i++) {
            for (int j = 0; j < MAX; j++) {
                for (int k = 0; k < MAX; k++) {
                    arrayPtr[i]->matriz[j][k] = 3;      //Se igualan todos los datos de la matriz a 3
                    arrayPtr2[i]->matriz[j][k] = 3;
                }
            }
        }

        ordenarTitulo(arrayPtr, numCasos);              //Se ordenan por titulo
        for (int i = 0; i < numCasos; i++) {
            cout << arrayPtr[i]->titulo << endl;
        }
        cout << endl;

        ordenarTitulo(arrayPtr2, numCasos);
        ordenarTema(arrayPtr2, numCasos);               //Se ordenan por tema principalmente, y luego por titulo

        for (int i = 0; i < numCasos; i++) {
            cout << arrayPtr2[i]->tema << " - " << arrayPtr2[i]->titulo << endl;
        }
        cout << endl;

        cin >> numCasos;
        cin.get(aux);
    }

    for (int i = 0; i < numCasos; i++) {               //Se libera el espacio en memoria
        delete arrayPtr2[i];
        arrayPtr2[i] = nullptr;
        delete arrayPtr[i];
        arrayPtr[i] = nullptr;
    }

    if (numCasos == 0)
        return false;

   return true;
}

void ordenarTitulo(tColeccion& arrayPtr, int numCasos) {
    tFoto* aux;

    for (int i = 0; i < numCasos; i++) {                    //Se ordenan por el metodo de burbuja los titulos de las fotos
        for (int j = 0; j < numCasos - 1; j++) {
            if (arrayPtr[j]->titulo.compare(arrayPtr[j + 1]->titulo) > 0) {
                aux = arrayPtr[j];
                arrayPtr[j] = arrayPtr[j + 1];
                arrayPtr[j + 1] = aux;
            }
        }
    }
}

void ordenarTema(tColeccion& arrayPtr, int numCasos) {
    tFoto* aux;

    for (int i = 0; i < numCasos; i++) {                    //Se ordenan por el metodo de burbuja los temas de las fotos
        for (int j = 0; j < numCasos - 1; j++) {
            if (arrayPtr[j]->tema.compare(arrayPtr[j + 1]->tema) > 0) {
                aux = arrayPtr[j];
                arrayPtr[j] = arrayPtr[j + 1];
                arrayPtr[j + 1] = aux;
            }
        }
    }
}
