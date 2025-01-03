
// Autor/a: Jorge López Carrión
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado: C++ y Windows
// Nombre del problema: PR01 RummyKub
/* Comentario general sobre la solución
 explicando como se resuelve el problema: Primero se inicializa la bolsa y se imprime en el fichero. A continuacion,
 se van obteniendo las fichas, se van repartiendo a los jugadores y, finalmente, se imprimen en el fichero, los datos
 de la bolsa y del soporte de cada jugador, tras haber robado "inifichas" cada jugador     */

#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

const int NumeroJugadores = 4;     //Se definen los valores maximos que pueden alcanzar las constantes
const int NumeroFichas = 13;
const int IniciarFichas = 14;
const int MaxFichas = 50;
const int MAX_JUGADAS = NumeroFichas * 2;
const int FichasColores = 8;
const int Colores = 4;

typedef enum { rojo, verde, azul, amarillo, blanco, libre } tColor;     //Se declaran todos los tipos
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
    int cont;
}tTablero;

void inicializarBolsa(tBolsa& bolsa, int numfichas);
void repartir(tBolsa& bolsa, tSoportes& soportes, int numfichas, int inifichas, int numjugadores);
tFicha robar(tBolsa& bolsa, int numfichas);
void mostrar(const tBolsa& bolsa, int numfichas);
void mostrar(const tSoporte& soporte);
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


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int numfichas, inifichas, numjugadores;
    tBolsa bolsa;
    tSoportes soportes;

    cin >> numfichas;
    if (!std::cin)
        return false;

    cin >> inifichas >> numjugadores;          //Se leen las variables (constantes en la practica)

    inicializarBolsa(bolsa, numfichas);    //Se inicializa la bolsa
    mostrar(bolsa, numfichas);         //Se muestra la bolsa
    cout << endl << "Repartir fichas" << endl << endl;

    repartir(bolsa, soportes, numfichas, inifichas, numjugadores);      //Se reparten las fichas a los jugadores


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
        mostrar(bolsa, numfichas);         //Se muestra tanto la bolsa , como el soporte
        mostrar(soportes[k]);   // tras haber robado el jugador con la posicion k
    }

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
        for(int j = 0; j < numfichas; j++){
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
