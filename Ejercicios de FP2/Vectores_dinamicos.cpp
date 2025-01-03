
// Autor/a: Jorge López Carrión
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado: Visual Studio 2019 y Windows
// Nombre del problema: Vectores dinámicos
/* Comentario general sobre la solución explicando como se resuelve el problema: Primero se guarda espacio en memoria para un array de
punteros y para cada puntero.A continucion, dependiendo si existe o no el objeto, se van aplicando las operaciones dadas y se van creando
los objetos si no existen. Cuando se lee una 'L' se muestra la lista y cuando se lea una 'F'(centinela) se acaba de procesar los datos
y se libera toda la memoria reservada.*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int TamInicial = 3;                   //Se declaran las constantes

typedef struct {
    string nombre;
    int unidades;
} tObjeto;

bool resuelveCaso();                        //Se declaran los prototipos de las funciones
void resolver(int entrada, int cantidad, tObjeto &objeto);

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
void resolver(int entrada, int cantidad, tObjeto &objeto) {
    if (entrada == 'A') {                   //Aumento de cantidad
        objeto.unidades += cantidad;
    }
    else if (entrada == 'R') {              //Disminucion de cantidad
        objeto.unidades -= cantidad;
        if (objeto.unidades < 0) {
            objeto.unidades = 0;
        }

    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    char entrada;
    int contador = 0, cantidad;
    int memoria = TamInicial;
    string nombre;
    int comprobar = -1;
    tObjeto** nuevo;

    tObjeto** objeto = new tObjeto*[memoria];       //Se crea en memoria dinamica un array de punteros
    for (int i = 0; i < memoria; i++) {
        objeto[i] = new tObjeto;
    }
    cin >> entrada;                                 //Se lee la entrada

    while (entrada != 'F') {                        //Mientras no se encuentre el centinela
        if (entrada == 'L') {                       //Se muestra la lista si corresponde con el formato pedido
            for (int i = 0; i < contador; i++) {
                cout << objeto[i]->nombre << " " << objeto[i]->unidades << endl;
            }
            cout << "---" << endl;
        }
        else {
            cin >> nombre;                          //Sino, se lee el nombre del objeto
            for (int i = 0; i < contador; i++) {    //Se busca en el array
                if (objeto[i]->nombre == nombre) {
                    comprobar = i;
                }
            }
            cin >> cantidad;                        //Se lee la cantidad de unidades
            if (comprobar != -1) {                  //Si el nombre se ha encontrado, se accede al objeto correspondiente
                resolver(entrada, cantidad, *objeto[comprobar]);
            }
            else {                                  //Si el objeto no existe, se inicializa y se crea
                if (entrada == 'A') {
                    objeto[contador]->nombre = nombre;
                    objeto[contador]->unidades = 0;
                    resolver(entrada, cantidad, *objeto[contador]);
                    contador++;
                }
            }
            if (contador == memoria) {              //Si hay el mismo numero de objetos que de espacio en memoria reservado
                memoria *= 2;
                nuevo = new tObjeto*[memoria];       //Se aumenta el tamaño del array
                for (int i = 0; i < memoria; i++) {
                    nuevo[i] = new tObjeto;          //Se reserva la memoria
                }
                for (int i = 0; i < contador; i++) {
                    *nuevo[i] = *objeto[i];
                    delete objeto[i];               //Se libera la memoria del anterior array y se sustituye por el nuevo
                    objeto[i] = nuevo[i];
                }
                delete[] objeto;
                objeto = nuevo;
            }
        }
        comprobar = -1;
        cin >> entrada;
    }
    
    //Se libera toda la memoria que se ha reservado
    for (int i = 0; i < memoria; i++) {
        delete objeto[i];
        objeto[i] = nullptr;
    }
    delete[] objeto;
    objeto = nullptr;        
    
    if (entrada == 'F')                             //Centinela
        return false;

    return true;
}
