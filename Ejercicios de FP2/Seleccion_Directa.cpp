
// Autor/a: Jorge López Carrión
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado: C++ y Windows
// Nombre del problema: Ordenar secuencias por el método de selección directa
// Comentario general sobre la solución
// explicando como se resuelve el problema: Se leen los numeros hasta que se lea el centinela 0 y, a continuacion,
// mediante el método de selección directa se ordenan todos los numeros de menor a mayor y finalmente
// se escriben en el fichero.

#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

const int MAX = 100;        //Se declaran las constantes

typedef int tArray[MAX];            //Se declaran los tipos
typedef struct {
    int contador;
    tArray numeros;
}tDatos;

void resolver(tDatos datos);            //Se declaran los prototipos de las funciones
void resuelveCaso();

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    int numCasos;                //Se leen el numero de casos de prueba
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

// función que resuelve el problema
void resolver(tDatos datos) {
    int cambio, menor;

    for (int i = 0; i < datos.contador - 1; i++) {      //Se recorre el array
        menor = i;                                      //Se supone el i el menor numero
        for (int j = i + 1; j < datos.contador; j++) {  //a partir del siguiente numero se comprueba cual es el menor numero
            if (datos.numeros[j] < datos.numeros[menor]) {      //Se va comprobando cual es el menor numero de los no ordenados
                menor = j;
            }
        }
        cambio = datos.numeros[i];          //Se cambia la posicion del primer numero no ordenado por el menor de lo que quedaban sin ordenar
        datos.numeros[i] = datos.numeros[menor];
        datos.numeros[menor] = cambio;

    }

    for (int i = 0; i < datos.contador; i++) {      //Se escriben los numeros ordenados
        cout << datos.numeros[i] << " ";
    }
    cout << endl;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    int entrada;                         //Se declaran las variables
    tDatos lista;
    lista.contador = 0;               //Se inicia el contador

    cin >> entrada;              //Se coge el primero valor del fichero del conjunto de numeros a ordenar
    while (entrada != 0) {       //Mientras no se encuentre el centinela 0 que siga leyendo numeros
        lista.numeros[lista.contador] = entrada;     //Se van colocando los numeros en el array
        lista.contador++;                //Se incrementa el contador ya que hay mas numeros en el array
        cin >> entrada;                  //Se le el siguiente numero
    }

    resolver(lista);                 //Se invoca a la funcion
}
