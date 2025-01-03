// Autor/a: Jorge López Carrión
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado: Visual Studio 2019 y Windows
// Nombre del problema: Problem 17. Sept 2020
/* Comentario general sobre la solución explicando como se resuelve el problema: Primero, se leen todos los datos de los jugadores
y todos los fichajes que se dan. A continuacion se muestran los datos guardados y se actualiza la lista segun se puedan o no hacer los
fichajes. Luego se muestan los datos ta actualizados y finalmente se elimina la memoria dinamica solicitada*/

#include <iostream>     //Bibliotecas necesarias
#include <fstream>
#include <string>

using namespace std;

const int MAX = 50;     //Se declaran las constantes
const int MAX2 = 20;

typedef struct {       //Se declaran los tipos
    string identificador;
    string nombre;
    string equipo;
    float precio;
} tJugador;
typedef tJugador* tPtrJugador;
typedef struct {
    int contador;
    tPtrJugador jugador;
}tListaJugadores;

typedef struct {
    string jugador;
    string equipo;
    float dinero;
}tFichaje;
typedef tFichaje* tPtrFichaje;
typedef struct {
    tPtrFichaje fichaje[MAX2];
    int contador;
}tListaFichajes;

bool resuelveCaso();        //Se declaran los prototipos de las funciones
float hazFichajes(tListaJugadores& jugadores, tListaFichajes& fichajes);
void delMemoria(tListaJugadores& jugadores, tListaFichajes& fichajes);
void visualizar(tListaJugadores jugadores, tListaFichajes fichajes);

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
    tListaJugadores jugadores;
    tListaFichajes fichajes;
    string aux;
    char c;
    int numCasos1, numCasos2;
    float precio;
    jugadores.contador = 0; fichajes.contador = 0;

    jugadores.jugador = new tJugador[MAX];      //Se crea el array en memoria dinamica

    cin >> numCasos1;                           //Se leen el numero de jugadores
    for (int i = 0; i < numCasos1; i++) {       //Se guarda toda la informacion de los jugadores 
        cin >> jugadores.jugador[i].identificador;
        cin.get(c);
        getline(cin, jugadores.jugador[i].nombre);
        getline(cin, jugadores.jugador[i].equipo);
        cin >> jugadores.jugador[i].precio;
        jugadores.contador++;                   //Se va contando el numero de jugadores
    }
    cin >> aux;                                 //Se quitan "--" y el intro
    cin.get(c);

    cin >> numCasos2;                           //Se lee el numero fichajes
    for (int i = 0; i < numCasos2; i++) {       //Se guarda toda la informacion de los fichajes
        fichajes.fichaje[i] = new tFichaje;
        cin >> fichajes.fichaje[i]->jugador;
        cin.get(c);
        getline(cin, fichajes.fichaje[i]->equipo);
        cin >> fichajes.fichaje[i]->dinero;
        fichajes.contador++;
    }
   
    visualizar(jugadores, fichajes);            //Se muestran los jugadores y fichajes que se quieren hacer

    precio = hazFichajes(jugadores, fichajes);  //Devuelve el precio total de los fichajes

    cout << "Y ahora veamos el total y como quedan las listas" << endl << endl;
    cout << "El total de los fichajes es " << precio << " millones de euros" << endl << endl;

    visualizar(jugadores, fichajes);            //Se muestran los jugadores y los fichajes una vez ejecutados los posibles

    delMemoria(jugadores, fichajes);            //Se libera toda la memoria solicitada
    cin.get(c);                                 //Se quita el intro
   if (!std::cin) 
      return false;
   
   return true;
}

float hazFichajes(tListaJugadores& jugadores, tListaFichajes& fichajes) {
    float precio = 0;

    for (int i = 0; i < jugadores.contador; i++) {          //Se leen los jugadores
        for (int j = 0; j < fichajes.contador; j++) {       //Se leen los fichajes
            if (jugadores.jugador[i].identificador == fichajes.fichaje[j]->jugador) {       //Si se trata del mismo jugador
                if (fichajes.fichaje[j]->dinero >= jugadores.jugador[i].precio) {           //Si se puede comprar
                    precio += fichajes.fichaje[j]->dinero;                                  //Se suma el precio a la suma de fichajes
                    jugadores.jugador[i].equipo = fichajes.fichaje[j]->equipo;              //Se cambia el equipo del jugador
                    delete fichajes.fichaje[j];                                             //Se libera la memoria correspondiente
                    fichajes.fichaje[j] = nullptr; 
                    for (int k = j; k < fichajes.contador - 1; k++) {                       //Se elimina el fichaje
                        fichajes.fichaje[k] = fichajes.fichaje[k + 1];
                    }
                    fichajes.contador--;                                                    //Se le resta 1 al contador
                }
            }
        }
    }

    return precio;
}

void delMemoria(tListaJugadores& jugadores, tListaFichajes& fichajes) {
    
    delete[] jugadores.jugador;                 //Se libera toda la memoria dinamica solicitada para los jugadores y fichajes
    jugadores.jugador = nullptr;
    for (int i = 0; i < fichajes.contador; i++) {
        delete fichajes.fichaje[i];
        fichajes.fichaje[i] = nullptr;
    }
}

void visualizar(tListaJugadores jugadores, tListaFichajes fichajes) {

    cout << "********* LISTA DE JUGADORES *********" << endl;   //Se muestra la lista de jugadores con el formato correspondiente
    for (int i = 0; i < jugadores.contador; i++) {
        cout << jugadores.jugador[i].identificador << " - ";
        cout << jugadores.jugador[i].nombre << " " << jugadores.jugador[i].equipo << " ";
        cout << jugadores.jugador[i].precio << " mill. euros" << endl;
    }
    cout << endl;

    cout << "*********  LISTA DE FICHAJES  *********" << endl;  //Se muestra la lista de fichajes con el formato correspondiente
    for (int i = 0; i < fichajes.contador; i++) {
        cout << fichajes.fichaje[i]->jugador << " - ";
        cout << fichajes.fichaje[i]->equipo << " " << fichajes.fichaje[i]->dinero << " mill. euros" << endl;
    }
    cout << endl << endl;
}