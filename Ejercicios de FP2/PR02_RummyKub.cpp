// Autor/a: Jorge López Carrión y David Cendejas Rodriguez
// email: jorglo03@ucm.es y dacendej@ucm.es
// Compilador y S.O. utilizado: Visual Studio 2019
// Nombre del problema: PR02 RummyKub
/* Comentario general sobre la solución
 explicando como se resuelve el problema: Primero se incializa la bolsa y se muestra en pantalla y, tras repartir "inifichas"
  a los jugadores, se vuelve a mostrar como queda la bolsa. Se lee el jugador que empieza. A continuacion se van leyendo las opciones
  que se nos van proporcionando y el programa actua segun la opcion dada. Finalmente, cuando lee el centinela (-1), termina
  el programa */

#include <iostream>
#include <fstream>

using namespace std;

const int NumeroJugadores = 4;     //Se definen los valores maximos que pueden alcanzar las constantes
const int NumeroFichas = 13;
const int IniciarFichas = 14;
const int MaxFichas = 50;
const int MAX_JUGADAS = NumeroFichas * 2;
const int FichasColores = 8;
const int Colores = 4;

typedef enum { rojo, verde, azul, amarillo, blanco, libre } tColor;
typedef struct {
    tColor color;
    int numero;
} tFicha;
typedef tFicha tFichas[MaxFichas];
typedef struct {
    tFichas ficha;
    int contador;
}tSoporte;
typedef tSoporte tSoportes[NumeroJugadores];
typedef tFicha tArrayBolsa[FichasColores][NumeroFichas];
typedef struct {
    tArrayBolsa bolsa;
    int contador;
}tBolsa;
typedef int tJugada[NumeroFichas];
typedef struct {
    tJugada jugada;
    int contador;
}tFichasJugada;
typedef tJugada tJugadas[MAX_JUGADAS];
typedef struct {
    tJugadas jugadas;
    int contador;
}tTablero;


void inicializarBolsa(tBolsa& bolsa, int numfichas);
void repartir(tBolsa& bolsa, tSoportes& soportes, int numfichas, int inifichas, int numjugadores);
tFicha robar(tBolsa& bolsa, int numfichas);
void mostrar(const tBolsa& bolsa, int numfichas);
void mostrar(const tSoporte& soporte);
bool resuelveCaso();
void ordenarPorNum(tSoporte& soporte);
void ordenarPorColor(tSoporte& soporte);
int menu();

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
    int numfichas, inifichas, numjugadores, opcion, jugador;
    tBolsa bolsa;
    tSoportes soportes;

    cin >> numfichas >> inifichas >> numjugadores;          //Se leen las variables (constantes en la practica)
    cout << endl;

    inicializarBolsa(bolsa, numfichas);    //Se inicializa la bolsa
    mostrar(bolsa, numfichas);
    cout << endl << "Fichas de la bolsa con todas las fichas repartidas" << endl << endl;
    repartir(bolsa, soportes, numfichas, inifichas, numjugadores);      //Se reparten las fichas a los jugadores
    cout << endl;

    cin >> jugador;                             //Se lee el jugador que empieza
    jugador--;                                  //Se le resta 1 para tener la posicion del jugador en el array
    cout << "Turno para el jugador " << jugador + 1 << " ...";
    mostrar(soportes[jugador]);

    opcion = menu();                //Se le la opcion con la funcion menu
    while (opcion != -1) {          //Mientras no se encuentre el centinela -1, que siga ejecutandose con normalidad

        if (opcion == 0) {      //opcion 0
            //comprobar la opcion de si ha jugado o no
            soportes[jugador].ficha[soportes[jugador].contador] = robar(bolsa, numfichas);  //Roba una ficha
            soportes[jugador].contador++;                           //Se aumenta el contador
            mostrar(soportes[jugador]);
            if (jugador == numjugadores - 1) {                      //Se cambia de jugador
                jugador = 0;
            }
            else if (jugador < numjugadores - 1) {
                jugador++;
            }

            cout << "Turno para el jugador " << jugador + 1 << " ...";
        }
        else if (opcion == 1) {                     //opcion 1
            ordenarPorColor(soportes[jugador]);     //Se ordena de manera que queden ordenados principalmente por numero y luego por color
            ordenarPorNum(soportes[jugador]);
        }
        else if (opcion == 2) {
            ordenarPorNum(soportes[jugador]);       //Se ordenan de manera que queden ordenados principalmente por color y luego por numero
            ordenarPorColor(soportes[jugador]);
        }
        mostrar(soportes[jugador]);
        opcion = menu();                        //Se lee la siguiente opcion
        if (opcion == -1)                       //centinela
            return false;
    }


    return true;
}


void inicializarBolsa(tBolsa& bolsa, int numfichas) {

    for (int i = 0; i < FichasColores; i++) {       //Se ordena la matriz de la bolsa y se organiza segun su numero y su color
        for (int j = 0; j < numfichas; j++) {
            if (i == 0 || i == 4) {                 //Se marcan las filas en las que las fichas seran del color indicado
                bolsa.bolsa[i][j].color = rojo;
            }
            else if (i == 1 || i == 5) {
                bolsa.bolsa[i][j].color = verde;
            }
            else if (i == 2 || i == 6) {
                bolsa.bolsa[i][j].color = azul;
            }
            else if (i == 3 || i == 7) {
                bolsa.bolsa[i][j].color = amarillo;
            }
            bolsa.bolsa[i][j].numero = j + 1;       //El numero de la dicha correspondiente sera la columna + 1, ya que las fichas empiezan en 1
        }
    }
}

void repartir(tBolsa& bolsa, tSoportes& soportes, int numfichas, int inifichas, int numjugadores) {

    for (int k = 0; k < numjugadores; k++) {            //Para un numero de jugadores indicados
        soportes[k].contador = 0;
        for (int i = 0; i < inifichas; i++) {           //Para un numero de fichas que obtener indicado
            soportes[k].ficha[i] = robar(bolsa, numfichas);        //Se roba la ficha
            soportes[k].contador++;                                             //Se van contando las fichas con el contador
        }
    }
    mostrar(bolsa, numfichas);         //Se muestra la bolsa
}

tFicha robar(tBolsa& bolsa, int numfichas) {

    tFicha ficha;
    int fila, columna, fila_inicial, columna_inicial;
    bool aux = true;
    ficha.numero = -1;
    ficha.color = libre;

    //srand(time(NULL));
    //fila = rand() % FichasColores;
    cin >> fila;
    //columna = rand() % numfichas;
    cin >> columna;
    fila_inicial = fila;
    columna_inicial = columna;


    if (bolsa.bolsa[fila][columna].color != libre) {    //Se hay ficha en la posicion dada, se coge
        ficha = bolsa.bolsa[fila][columna];
    }
    else {
        while ((ficha.color == libre) && (aux == true)) {
            if (fila == FichasColores - 1 && columna == numfichas - 1) {        //ultima casilla
                fila = 0;
                columna = 0;
            }
            else if (columna == numfichas - 1) {       //ultima fila
                columna = 0;
                fila++;
            }
            else {                                      //cualquier otra
                columna++;
            }
            if (bolsa.bolsa[fila][columna].color != libre) {        //Hay ficha en la columna y fila indicada
                ficha = bolsa.bolsa[fila][columna];
            }
            if (fila == fila_inicial && columna == columna_inicial) {   // no hay mas dichas en toda la bolsa
                aux = false;
            }
        }
    }
    bolsa.bolsa[fila][columna].color = libre;       //Se indica que la ficha indicada no se encuentra en la bolsa
    bolsa.bolsa[fila][columna].numero = -1;

    return ficha;
}

void mostrar(const tBolsa& bolsa, int numfichas) {

    cout << "Bolsa..." << endl;
    for (int i = 0; i < FichasColores; i++) {               //Recorriendo la matriz, se escribe toda con su respectivo color y numero
        for (int j = 0; j < numfichas; j++) {
            if (bolsa.bolsa[i][j].color == rojo) {
                cout << "rojo " << bolsa.bolsa[i][j].numero << "  ";
            }
            else if (bolsa.bolsa[i][j].color == verde) {
                cout << "verd " << bolsa.bolsa[i][j].numero << "  ";
            }
            else if (bolsa.bolsa[i][j].color == azul) {
                cout << "azul " << bolsa.bolsa[i][j].numero << "  ";
            }
            else if (bolsa.bolsa[i][j].color == amarillo) {
                cout << "amar " << bolsa.bolsa[i][j].numero << "  ";
            }
            else if (bolsa.bolsa[i][j].color == libre) {
                cout << "    -1" << "  ";
            }
        }
        cout << endl;
    }
}

void mostrar(const tSoporte& soporte) {

    cout << endl << "Soporte: ";
    for (int i = 0; i < soporte.contador; i++) {        //Se escribe todo el soporte del jugador dado, con su respectivo color y numero
        if (soporte.ficha[i].color == rojo) {
            cout << "rojo " << soporte.ficha[i].numero << "  ";
        }
        else if (soporte.ficha[i].color == verde) {
            cout << "verd " << soporte.ficha[i].numero << "  ";
        }
        else if (soporte.ficha[i].color == azul) {
            cout << "azul " << soporte.ficha[i].numero << "  ";
        }
        else if (soporte.ficha[i].color == amarillo) {
            cout << "amar " << soporte.ficha[i].numero << "  ";
        }
    }
    cout << endl << endl;
}

void ordenarPorNum(tSoporte& soporte) {
    tFicha aux;
    int i = 0;
    bool comprobar = true;

    while ((i < soporte.contador - 1) && comprobar) {       //Mediante el metodo de la burbuja mejorado se ordenan los numeros de menor a mayor
        comprobar = false;
        for (int j = soporte.contador - 1; j > i; j--) {         //Se recorren con orden descendente
            if (soporte.ficha[j].numero < soporte.ficha[j - 1].numero) {    //Se comprueba si hay cambios que hacer
                aux = soporte.ficha[j];
                soporte.ficha[j] = soporte.ficha[j - 1];
                soporte.ficha[j - 1] = aux;
                comprobar = true;
            }
        }
        i++;
    }
}

void ordenarPorColor(tSoporte& soporte) {
    tFicha aux;
    int i = 0;
    bool comprobar = true;

    while ((i < soporte.contador - 1) && comprobar) {   //Mediante el metodo de la burbuja mejorado se ordenan los numeros segun estan en el enum ordenados
        comprobar = false;
        for (int j = soporte.contador - 1; j > i; j--) {       //Se recorren con orden descendente
            if (soporte.ficha[j].color < soporte.ficha[j - 1].color) {    //Se comprueba si hay cambios que hacer
                aux = soporte.ficha[j];
                soporte.ficha[j] = soporte.ficha[j - 1];
                soporte.ficha[j - 1] = aux;
                comprobar = true;
            }
        }
        i++;
    }
}

int menu() {
    int opcion;

    cin >> opcion;                  //Se lee la opcion primero para comprobar que no es el centinela
    if (opcion != -1) {             //Se muestra el menu
        cout << "1: Ordenar por num.";
        cout << ", 2: Ordenar por color";
        cout << ", 3: Sugerir";
        cout << ", 4: Poner";
        cout << ", 0: Fin  >>>";
        cout << "  ";
        cout << opcion;
    }
    return opcion;
}
