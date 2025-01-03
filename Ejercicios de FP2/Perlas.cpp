
// Autor/a: Jorge López Carrión
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado: C++ y Windows
// Nombre del problema: Las perlas de la condesa
// Comentario general sobre la solución
// explicando como se resuelve el problema: Se leen los datos y se ordenan en el array. A continuacion, se escriben 
// de forma simetrica como se indica en el enunciado y se comprueba que se puedan escribir asi.
// Finalmente se indica si se ha podido escribir como se pide, y si se puede, se muestran en pantalla ordenados como se indica

#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

const int MAX = 1000;           //Se declaran las constantes

typedef int tArray[MAX];        //Se declaran los tipos necesarios
typedef struct {
    tArray array;
    int contador;
}tDatos;


bool resuelveCaso();                //Se declaran los prototipos de las funciones
void resolver(tDatos datos);



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


// función que resuelve el problema
void resolver(tDatos datos) {
    int menor, cambio;
    int extra[MAX];
    bool comprobar = true;

    //Se ordena el array de los numeros
    for (int i = 0; i < datos.contador - 1; i++) {      //Se recorre el array
        menor = i;                                      //Se supone el i el menor numero
        for (int j = i + 1; j < datos.contador; j++) {  //a partir del siguiente numero se comprueba cual es el menor numero
            if (datos.array[j] < datos.array[menor]) {      //Se va comprobando cual es el menor numero de los no ordenados
                menor = j;
            }
        }
        cambio = datos.array[i];          //SeThe cambia la posicion del primer numero no ordenado por el menor de lo que quedaban sin ordenar
        datos.array[i] = datos.array[menor];
        datos.array[menor] = cambio;
    }

    for (int i = 0; i < datos.contador / 2; i++) {      //Se escriben de forma simetrica
        extra[i] = datos.array[2 * i];
        extra[datos.contador - 1 - i] = datos.array[(2 * i) + 1];
    }
    extra[datos.contador / 2] = datos.array[datos.contador - 1];        //Se inserta el numero mayor en el centro del array que se recorre

    for (int i = 0; i < datos.contador / 2; i++) {      //Se comprueba que sea simetrico
        if (extra[i] != extra[datos.contador - 1 - i]) {
            comprobar = false;
        }
    }
    if ((comprobar == false) || (extra[datos.contador/2] == extra[(datos.contador/2)-1])) {           //Se escribe "NO" si no es simetrico
        cout << "NO";
    }
    else {
        for (int i = 0; i < datos.contador; i++) {  //Se escriben el conjunto de numeros si es simetrico
            cout << extra[i];
            if (i != datos.contador - 1) {
                cout << " ";
            }
        }
    }
    cout << endl;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    tDatos datos;
    int numero;

    datos.contador = 0;             //Se inicia el contador

    cin >> numero;                  //Se van leyendo numeros hasta que se lea el 0
    datos.array[0] = numero;
    while (numero != 0) {
        if (datos.contador != 0) {
            datos.array[datos.contador] = numero;
        }
        datos.contador++;
        cin >> numero;
    }

    if (datos.array[0] == 0)           //Se escribe el centinela final
        return false;

    resolver(datos);                    //Se invoca la funcion resolver

    return true;
}
