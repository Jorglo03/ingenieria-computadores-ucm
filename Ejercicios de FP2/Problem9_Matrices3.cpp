
// Autor/a: Jorge López Carrión
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado: C++ y Windows
// Nombre del problema: Jaque de reina. Matrices 3
// Comentario general sobre la solución
// explicando como se resuelve el problema: Primero se lee si hay fichas en cada posicion de la matriz, y se van guardando con el formato
// de tPiezas y se guarda la posicion de la reina. Luego con las direcciones, se recorren todas las casillas a las que da jaque y se
// comprueba si hay piezas por medio. Finalmente, se escribe "JAQUE" si alguna direccion de la reina da al rey y no hay piezas por medio

#include <iostream>             //Se introducen las liberias
#include <fstream>
#include <utility>

using namespace std;

const int NUM = 8;                          //Se declaran las constantes
const int NUM_DIRECCIONES = 8;
const std::pair <int, int > dirs8[NUM_DIRECCIONES] =               
{ { -1 ,0} ,{1 ,0} ,{0 ,1} ,{0 , -1} , {1 ,1} , { -1 ,1} , {1 , -1} , { -1 , -1} };

typedef enum {REINA, REY, OTRA , NADA} tPieza;          //Se declaran los tipos
typedef tPieza tMatriz[NUM][NUM];

void resolver(bool datos);          //Se declaran los prototipos de las funciones
void resuelveCaso();


int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("datos.in");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
   std::ofstream out("datos.out");
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

// función que resuelve el problema
void resolver(bool datos) {
   
    if (datos == false) {                   //Se escribe si esta en jaque o no
        cout << "SIN JAQUE" << endl;
    }
    else if (datos == true) {
        cout << "JAQUE" << endl;
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    tMatriz matriz;
    char pieza;
    int fila, columna, fila_aux, columna_aux, piezas;
    bool comprobar = false;
    
    for (int i = 0; i < NUM; i++) {         //Se leen los datos de la matriz (el tablero)
        for (int j = 0; j < NUM; j++) {
            cin >> pieza;                   //Se guardan las piezas y se asignan en la matriz con el tipo enumerado correspondiente
            if (pieza == '.') {             //No hay pieza
                matriz[i][j] = NADA;
            }
            else if (pieza == 'A') {        //Se encuentra a la reina
                matriz[i][j] = REINA;
                fila = i;                   //Se guardan las coordenadas de la reina
                columna = j;
                fila_aux = fila;
                columna_aux = columna;
            }
            else if (pieza == 'R') {        //Se encuentra a el rey
                matriz[i][j] = REY;
            }
            else if (pieza == 'X') {        //Se encuentra otra pieza
                matriz[i][j] = OTRA;
            }
        }
    }

    for (int i = 0; i < NUM_DIRECCIONES; i++) {     //Se recorren todas las direcciones que alcanza la reina
        fila = fila_aux;                    //Se empiezan a contar las direcciones desde la posicion de la reina
        columna = columna_aux;
        piezas = 0;
        while ((fila < 8 && fila >= 0) && (columna < 8 && columna >= 0)&&(comprobar == false)) {    //Mientras este dentro del tablero
            if (matriz[fila][columna] == OTRA) {                                 // y todavia no se halla encontrado a el rey, se sigue buscando
                piezas++;                                                       //Se cuentan si hay piezas por medio en la direccion que se este ejecutando
            }
            if ((matriz[fila][columna] == REY)&&(piezas == 0)) {                //Si se encuentra el rey y no hay piezas por medio, esta en jaque
                comprobar = true;
            }
            fila = fila + dirs8[i].first;                                       //Se avanza en la direccion correspondiente
            columna = columna + dirs8[i].second;
        }
    }

    resolver(comprobar);                        //Se invoca la funcion resolver

}
