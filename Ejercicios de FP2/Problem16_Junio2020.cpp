// Autor/a: Jorge López Carrión
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado: Visual Studio 2019 y Windows
// Nombre del problema: Problem 16. Junio 2020
/* Comentario general sobre la solución explicando como se resuelve el problema: Se leen tanto las peliculas y todos sus datos relacionados
como las entradas y sus datos. Se procesan los datos calculando el precio y las localidades disponibles y se muestra en pantalla el
resultado. Finalmente, se libera la memora solicitada*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX = 50;     //Se declaran las constantes

typedef struct {        //Se declaran los tipos
    string titulo;
    int precio;
    int anio;
    int disponibles;
} tPeli;
typedef tPeli* tPtrPeli;
typedef struct {
    int contador;
    tPtrPeli peliculas[MAX];
}tListaPelis;

typedef struct {
    string titulo;
    int solicitadas;
}tEntradas;
typedef tEntradas* tPtrEntradas;
typedef struct {
    tPtrEntradas entradas;
    int contador;
}tListaEntradas;
        
bool resuelveCaso();            //Se declaran los prototipos de las funciones
int procesarEntradas(tListaEntradas& entradas, tListaPelis& pelis);
void visualizar(tListaEntradas entradas, tListaPelis pelis);
void liberarMemoria(tListaEntradas entradas, tListaPelis pelis);

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
    string lectura;
    tListaPelis pelis;
    tListaEntradas entradas;
    int i = 0, coste = 0;
    char c;
    
    pelis.contador = 0;
    cin >> lectura;
    while (lectura != "---") {                              //Se leen las peliculas que hay
        pelis.peliculas[pelis.contador] = new tPeli;
        pelis.peliculas[pelis.contador]->titulo = lectura;
        cin >> pelis.peliculas[pelis.contador]->precio;
        cin >> pelis.peliculas[pelis.contador]->anio;
        cin >> pelis.peliculas[pelis.contador]->disponibles;
        pelis.contador++;
        cin >> lectura;
    }
    cin.get(c);                                             //lee el intro

    entradas.contador = 0;
    entradas.entradas = new tEntradas[MAX];
    cin >> lectura;
    while (lectura != "000") {                              //Se leen las entradas que se dan
        entradas.entradas[entradas.contador].titulo = lectura;
        cin >> entradas.entradas[entradas.contador].solicitadas;
        entradas.contador++;
        cin >> lectura;
    }

    coste = procesarEntradas(entradas, pelis);              //Se ejecutan los cambios

    //visualizar(entradas, pelis);

    cout << endl << "   *****   Lista de pelis   *****   " << endl << endl;     //Se muestran las resultados finales
    for (int i = 0; i < pelis.contador; i++) {
        cout << pelis.peliculas[i]->titulo << " - " << pelis.peliculas[i]->precio << " euros - ";
        cout << pelis.peliculas[i]->anio << " - " << pelis.peliculas[i]->disponibles << " localidades disponibles." << endl;
    }

    cout << endl << "  " << "El coste total es: " << coste;

    liberarMemoria(entradas, pelis);
   if (lectura == "000")
      return false;
   
   return true;
}

int procesarEntradas(tListaEntradas& entradas, tListaPelis& pelis) {
    int coste = 0;

    for (int i = 0; i < pelis.contador; i++) {      //Se recorren todas las peliculas
        for (int j = 0; j < entradas.contador; j++) {       //Se recorren las entradas
            if (pelis.peliculas[i]->titulo == entradas.entradas[j].titulo) {        //Si son la misma pelicula
                if (pelis.peliculas[i]->disponibles >= entradas.entradas[j].solicitadas) { //Si hay mas entradas disponibles que solicitadas
                    pelis.peliculas[i]->disponibles -= entradas.entradas[j].solicitadas;    //Se restan las solicitadas a las disponibles
                    coste = coste + entradas.entradas[j].solicitadas * pelis.peliculas[i]->precio;  //Se calcula el precio
                }
                else if (pelis.peliculas[i]->disponibles < entradas.entradas[j].solicitadas) {  //Si hay menos disponibles que solicitadas
                    coste = coste + pelis.peliculas[i]->disponibles * pelis.peliculas[i]->precio;   //Se calcula el precio de las disponibles                                      
                    delete pelis.peliculas[i];                                      //Se libera la memoria solicitada para la pelicula
                    pelis.peliculas[i] = nullptr;
                    for (int k = i; k < pelis.contador - 1; k++) {              //Se quita la pelicula de la lista
                        pelis.peliculas[k] = pelis.peliculas[k + 1];
                    }   
                    pelis.contador--;                                           //Se le resta uno al contador de peliculas
                }
            }
        }
    }

    return coste;
}

void visualizar(tListaEntradas entradas, tListaPelis pelis) {
    //Muestra los datos leidos
    for (int i = 0; i < pelis.contador; i++) {
        cout << pelis.peliculas[i]->titulo << " " << pelis.peliculas[i]->anio << " " << pelis.peliculas[i]->disponibles;
        cout << " " << pelis.peliculas[i]->precio << endl;
    }
    cout << "---" << endl;
    for (int i = 0; i < entradas.contador; i++) {
        cout << entradas.entradas[i].titulo << " " << entradas.entradas[i].solicitadas << endl;
    }
}

void liberarMemoria(tListaEntradas entradas, tListaPelis pelis) {
   
    for (int i = 0; i < pelis.contador; i++) {          //Se libera toda la memoria solicitada
        delete pelis.peliculas[i];
        pelis.peliculas[i] = nullptr;
    }
    delete[] entradas.entradas;
    entradas.entradas = nullptr;
}