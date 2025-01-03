
// Autor/a: Jorge López Carrión 
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado: C++ y Windows
// Nombre del problema: Diversión con matrices. Parte 2
// Comentario general sobre la solución
// explicando como se resuelve el problema: Se leen los datos de la entrada y se guarda la matriz. A continuacion, con un bucle 
// se controlan el numero de instrucciones que se van a leer y se ejecutan segun su funcion. Finalmente, se imprime la matriz
// respuesta en el fichero

#include <iostream>
#include <fstream>
#include <string>

// Introduce más librerías si son necesarias
using namespace std;

const int MAX = 20;         //Se declaran constantes

typedef int tMatriz[MAX][MAX];      //Se declaran tipos
typedef struct {
    int filas; 
    int columnas;
    tMatriz matriz;
}tDatos;

void resolver(tDatos datos);            //Se declaran los prototipos de las funciones
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


// función que resuelve el problema
void resolver(tDatos datos) {
   
    for (int i = 0; i < datos.filas; i++) {           //Se imprime en el archivo la matriz
        for (int j = 0; j < datos.columnas; j++) {
            cout << datos.matriz[i][j];
            if (j != datos.columnas - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << "---" << endl;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    tDatos datos;
    int instrucciones, num_transformacion, aux;
    string transformaciones;

    cin >> datos.filas;             //Se leen las filas y las columnas y se guardan
    cin >> datos.columnas;
   
   if (datos.filas == 0 && datos.columnas == 0)         //Se comprueba que no sea el centinela
      return false;
   else {
       for (int i = 0; i < datos.filas; i++) {          //Se guarda la matriz
           for (int j = 0; j < datos.columnas; j++) {
               cin >> datos.matriz[i][j];
           }
       }
       
       cin >> instrucciones;                        //Se leen el numero de instrucciones y con un bucle se controlan las que se leeran
       for (int i = 0; i < instrucciones; i++) {
           cin >> transformaciones;
           if (transformaciones == "rotarFila") {       //Segun cual sea la instruccion se hará uno función u otra
               cin >> num_transformacion;
               if (num_transformacion >= 0) {           //Segun sea el numero negativo o positivo se ejecutara de una manera u otra
                   num_transformacion--;                //Se ajusta, en este caso la fila, a la fila real de la matriz guardada
                   aux = datos.matriz[num_transformacion][datos.columnas - 1];      //Se intercambian los numeros para que la fila
                   for (int i = datos.columnas - 1; i > 0; i--) {                   //a la derecha
                       datos.matriz[num_transformacion][i] = datos.matriz[num_transformacion][i - 1];
                   }
                   datos.matriz[num_transformacion][0] = aux;
               }
               else if (num_transformacion < 0) {
                   num_transformacion = num_transformacion * (-1);      //Se cambia el numero de signo para leer la fila del dato
                   num_transformacion--;
                   aux = datos.matriz[num_transformacion][0];
                   for (int i = 0; i < datos.columnas - 1; i++) {           //Se intercambian los numeros para que la fila rote hacia la izquierda
                       datos.matriz[num_transformacion][i] = datos.matriz[num_transformacion][i + 1];
                   }
                   datos.matriz[num_transformacion][datos.columnas - 1] = aux;
               }
           }
           else if (transformaciones == "rotarCol") {
               cin >> num_transformacion;
               if (num_transformacion >= 0) {       
                   num_transformacion--;
                   aux = datos.matriz[datos.filas - 1][num_transformacion];
                   for (int i = datos.filas-1; i > 0; i--) {                //Se intercambian los numeros para que la columna rote hacia abajo
                       datos.matriz[i][num_transformacion] = datos.matriz[i - 1][num_transformacion];
                   }
                   datos.matriz[0][num_transformacion] = aux;
               }
               else if (num_transformacion < 0) {
                   num_transformacion = num_transformacion * (-1);
                   num_transformacion--;
                   aux = datos.matriz[0][num_transformacion];
                   for (int i = 0; i < datos.filas - 1; i++) {          //Se intercambian los numeros para que la columna rote hacia arriba
                       datos.matriz[i][num_transformacion] = datos.matriz[i + 1][num_transformacion];
                   }
                   datos.matriz[datos.filas - 1][num_transformacion] = aux;
               }
           }
       }
   }
    resolver(datos);        //Se imprime la matriz en el fichero
     
   return true;
}
