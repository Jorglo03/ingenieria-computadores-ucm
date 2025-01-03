// Autor/a: Jorge López Carrión
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado: Visual Studio 2019
// Nombre del problema: PR04 RummyKub
/* Comentario general sobre la solución explicando como se resuelve el problema:
Partiendo del PR03 RummyKub, se añade la funcionalidad de que si se inserta una ficha para añadir, que busque en la funcion "ponerFicha" si la puede
colocar en el tablero, y donde la puede colocar, y ademas se añade la funcionalidad de que si un jugador se queda sin fichas, el programa termine 
dando a ese jugador como ganador del juego.
 */

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int NumeroJugadores = 4;     //Se definen los valores maximos que pueden alcanzar las constantes
const int NumeroFichas = 13;
const int IniciarFichas = 14;
const int MaxFichas = 50;
const int MAX_JUGADAS = NumeroFichas * 2;
const int FichasColores = 8;
const int Colores = 4;

typedef enum { rojo, verde, azul, amarillo, blanco, libre } tColor;         //Se declaran los tipos
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
typedef tFicha tFichasJugadas[NumeroFichas];
typedef struct {
    tFichasJugadas jugada;
    int contador;
}tJugada;
typedef tJugada tJugadas[MAX_JUGADAS];
typedef struct {
    tJugadas jugadas;
    int contador;
}tTablero;


void inicializarBolsa(tBolsa& bolsa, int numfichas);                //Se declaran los prototipos de las funciones
void repartir(tBolsa& bolsa, tSoportes& soportes, int numfichas, int inifichas, int numjugadores);
tFicha robar(tBolsa& bolsa, int numfichas);
void mostrar(const tFicha& ficha);
void mostrar(const tBolsa& bolsa, int numfichas);
void mostrar(const tSoporte& soporte);
void mostrar(const tTablero& tablero);
int nuevaJugada(tSoporte& soporte, tJugada& jugada);
void eliminaFichas(tSoporte& soporte, const tJugada& jugada);
bool jugar(tTablero& tablero, tSoporte& soporte);
bool resuelveCaso();
void ordenarPorNum(tSoporte& soporte);
void ordenarPorColor(tSoporte& soporte);
void mostrarSeries(const tSoporte& soporte);
void mostrarEscaleras(const tSoporte& soporte);
bool ponerFicha(tJugada& jugada, tFicha& ficha);
int buscar(const tJugada& jugada, const tFicha& ficha);
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
    tTablero tablero;
    tablero.contador = 0;
    tBolsa bolsa;
    tSoportes soportes;
    bool jugado = false, ganador = false;

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

    opcion = menu();                //Se lee la opcion con la funcion menu
    while ((opcion != -1) && (ganador == false)) {          //Mientras no se encuentre el centinela -1, que siga ejecutandose con normalidad

        if (opcion == 0) {      //opcion 0
            //comprobar la opcion de si ha jugado o no
            if (jugado == false) {
                soportes[jugador].ficha[soportes[jugador].contador] = robar(bolsa, numfichas);  //Roba una ficha
                soportes[jugador].contador++;       //Se aumenta el contador
                mostrar(soportes[jugador]);
            }

            cout << endl;
            if (jugador == numjugadores - 1) {                      //Se cambia de jugador
                jugador = 0;
            }
            else if (jugador < numjugadores - 1) {
                jugador++;
            }
            jugado = false;

            cout << endl << "Turno para el jugador " << jugador + 1 << " ...";
        }
        else if (opcion == 1) {                     //opcion 1
            ordenarPorColor(soportes[jugador]);     //Se ordena de manera que queden ordenados principalmente por numero y luego por color
            ordenarPorNum(soportes[jugador]);
        }
        else if (opcion == 2) {
            ordenarPorNum(soportes[jugador]);       //Se ordenan de manera que queden ordenados principalmente por color y luego por numero
            ordenarPorColor(soportes[jugador]);
        }
        else if (opcion == 3) {
            ordenarPorNum(soportes[jugador]);       //Se ordenan de manera que queden ordenados principalmente por color y luego por numero
            ordenarPorColor(soportes[jugador]);
            mostrarSeries(soportes[jugador]);       //Se muestran las posibles series
            mostrarEscaleras(soportes[jugador]);    //Se muestran las posibles escaleras
        }
        else if (opcion == 4) {

            mostrar(soportes[jugador]);             //Se muestra el soporte del jugador
            cout << "         ";
            for (int i = 1; i <= soportes[jugador].contador; i++) {
                cout << setw(6) << i << "  ";
            }

            jugado = jugar(tablero, soportes[jugador]); //Se llama a la funcion jugar y se comprueba si ha jugado o no

        }
        mostrar(soportes[jugador]);

        if (soportes[jugador].contador == 0) {      //Si un jugador se ha quedado sin fichas
            ganador = true;                         //Y hay un ganador
            cout << endl << "El jugador " << jugador + 1 << " ha ganado!" << endl;
            do {            //Se leen todos los valores que quedan por leer hasta que llegue al centinela, ya que ha finalizado el juego con un ganador
                cin >> opcion;
            } while (opcion != -1);
        }
        else {
            opcion = menu();                        //Se lee la siguiente opcion
        }
        if (opcion == -1)               //Centinela
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

    cin >> fila;
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
            if (fila == fila_inicial && columna == columna_inicial) {   // no hay mas fichas en toda la bolsa
                aux = false;
            }
        }
    }
    bolsa.bolsa[fila][columna].color = libre;       //Se indica que la ficha indicada no se encuentra en la bolsa
    bolsa.bolsa[fila][columna].numero = -1;

    return ficha;
}

int buscar(const tJugada& jugada, const tFicha& ficha) {
    int posicion = -1;

    for (int i = 0; i < jugada.contador; i++) {
        if ((ficha.color == jugada.jugada[i].color) && (ficha.numero == jugada.jugada[i].numero)) {
            posicion = i;
        }
    }

    return posicion;
}

void mostrar(const tFicha& ficha) {             //Se muestra la ficha con su color y numero correspondiente

    if (ficha.color == rojo) {
        cout << "rojo " << ficha.numero << "  ";
    }
    else if (ficha.color == verde) {
        cout << "verd " << ficha.numero << "  ";
    }
    else if (ficha.color == azul) {
        cout << "azul " << ficha.numero << "  ";
    }
    else if (ficha.color == amarillo) {
        cout << "amar " << ficha.numero << "  ";
    }
    else if (ficha.color == libre) {
        cout << "    -1" << "  ";
    }
}

void mostrar(const tBolsa& bolsa, int numfichas) {

    cout << "Bolsa..." << endl;
    for (int i = 0; i < FichasColores; i++) {               //Recorriendo la matriz, se escribe toda con su respectivo color y numero
        for (int j = 0; j < numfichas; j++) {
            mostrar(bolsa.bolsa[i][j]);
        }
        cout << endl;
    }
}

void mostrar(const tSoporte& soporte) {

    cout << endl << "Soporte: ";
    for (int i = 0; i < soporte.contador; i++) {        //Se escribe todo el soporte del jugador dado, con su respectivo color y numero
        cout << setw(5);
        mostrar(soporte.ficha[i]);
    }
    cout << endl;
}

void mostrar(const tTablero& tablero) {                 //Se escribe, con todas las jugadas que hay en el tablero numeradas
    cout << endl << endl << "Tablero:" << endl;
    if (tablero.contador != 0) {
        for (int i = 0; i < tablero.contador; i++) {
            cout << setw(2) << i + 1 << ": ";
            for (int j = 0; j < tablero.jugadas[i].contador; j++) {
                mostrar(tablero.jugadas[i].jugada[j]);
            }
            cout << endl;
        }
    }
    else {
        cout << "No hay jugadas" << endl;
    }
    cout << endl;
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

void mostrarSeries(const tSoporte& soporte) {
    tSoporte aux, serie;
    serie.contador = 0;

    for (int i = 0; i < soporte.contador; i++) {        //Se pasa el soporte a un array auxiliar
        aux.ficha[i] = soporte.ficha[i];
    }
    aux.contador = soporte.contador;
    ordenarPorColor(aux);
    ordenarPorNum(aux);                     //Se ordena principalmente por numero y a mismo numero, por color

    for (int i = 0; i < aux.contador - 1; i++) {        //Se recorre el array
        if (((aux.ficha[i].color != aux.ficha[i + 1].color) && (aux.ficha[i].numero == aux.ficha[i + 1].numero)) && (serie.contador == 0)) {
            serie.ficha[serie.contador] = aux.ficha[i];         //Si dos numeros cumplen los requisitos para ser una posible serie y son los primeros
            serie.contador++;                                   //se introducen los dos en el array "serie"
            serie.ficha[serie.contador] = aux.ficha[i + 1];
            serie.contador++;
        }
        else if ((aux.ficha[i].color != aux.ficha[i + 1].color) && (aux.ficha[i].numero == aux.ficha[i + 1].numero)) {
            serie.ficha[serie.contador] = aux.ficha[i + 1];     //Si dos numeros cumplen los requisitos para ser una posible serie y no son los primeros
            serie.contador++;                                   //se introduce en el array "serie" el segundo
            if ((i == aux.contador - 2) && (serie.contador > 2)) {
                cout << endl;
                for (int j = 0; j < serie.contador; j++) {
                    mostrar(serie.ficha[j]);
                }
            }
        }
        else if ((aux.ficha[i].color == aux.ficha[i + 1].color) && (aux.ficha[i].numero == aux.ficha[i + 1].numero)) {
            aux.ficha[i + 1].numero = -1;      //Si hay dos fichas exactamente iguales, que pase al siguiente numero y ese se lo salte, ya que no sirve, pero puede
        }                                      // seguir habiendo una serie
        else {
            if (serie.contador > 2) {           //Si hay mas de dos fichas que cumplan la opcion de que puedan hacer una serie, se escriben
                cout << endl;
                for (int j = 0; j < serie.contador; j++) {
                    mostrar(serie.ficha[j]);
                }
            }
            serie.contador = 0;         //Se inicializa el contador a 0 para que vuelva a buscar nuevas series
        }
    }
}

void mostrarEscaleras(const tSoporte& soporte) {
    tSoporte aux, escalera;
    escalera.contador = 0;

    for (int i = 0; i < soporte.contador; i++) {     //Se pasa el soporte a un array auxiliar
        aux.ficha[i] = soporte.ficha[i];
    }
    aux.contador = soporte.contador;
    ordenarPorNum(aux);
    ordenarPorColor(aux);           //Se ordena principalmente por color, y a mismo color, por numero

    for (int i = 0; i < aux.contador - 1; i++) {
        if (((aux.ficha[i].color == aux.ficha[i + 1].color) && (aux.ficha[i].numero == aux.ficha[i + 1].numero - 1)) && (escalera.contador == 0)) {
            escalera.ficha[escalera.contador] = aux.ficha[i];       //Si dos numeros cumplen los requisitos para ser una posible escalera y son los primeros
            escalera.contador++;                                    //se introducen los dos en el array "escalera"
            escalera.ficha[escalera.contador] = aux.ficha[i + 1];
            escalera.contador++;
        }
        else if ((aux.ficha[i].color == aux.ficha[i + 1].color) && (aux.ficha[i].numero == aux.ficha[i + 1].numero - 1)) {
            escalera.ficha[escalera.contador] = aux.ficha[i + 1];     //Si dos numeros cumplen los requisitos para ser una posible escalera y no son los primeros
            escalera.contador++;                                    //se introduce el segudo en el array "escalera"
            if ((i == aux.contador - 2) && (escalera.contador > 2)) {
                cout << endl;
                for (int j = 0; j < escalera.contador; j++) {
                    mostrar(escalera.ficha[j]);
                }
            }
        }
        else if ((aux.ficha[i].color == aux.ficha[i + 1].color) && (aux.ficha[i].numero == aux.ficha[i + 1].numero)) {
            aux.ficha[i + 1].numero = -1;       //Si hay dos fichas exactamente iguales, que pase al siguiente numero y ese se lo salte, ya que no sirve, pero puede
        }                                       // seguir habiendo una serie 
        else {
            if (escalera.contador > 2) {        //Si hay mas de dos fichas que cumplan la opcion de ser una escalera, se escriben
                cout << endl;
                for (int j = 0; j < escalera.contador; j++) {
                    mostrar(escalera.ficha[j]);
                }
            }
            escalera.contador = 0;       //Se inicializa el contador a 0 para que vuelva a buscar nuevas escaleras
        }
    }
}

int nuevaJugada(tSoporte& soporte, tJugada& jugada) {
    int num_fichas = 0, posicion;
    bool verificar = true;

    jugada.contador = 0;        //Se inicializa a 0 el contador            

    cout << endl << endl << "    " << "Fichas (0 al final): ";
    do {                                     //Con este bucle
        cin >> posicion;                     //Se leen las posiciones de las fichas
        cout << posicion << " ";
        if (posicion != 0) {
            jugada.jugada[num_fichas] = soporte.ficha[posicion - 1];       //Se introducen en la jugada las fichas que dadas 
            num_fichas++;
        }
    } while (posicion != 0);


    return num_fichas;       //Devuelve el numero de fichas de la jugada
}

void eliminaFichas(tSoporte& soporte, const tJugada& jugada) {
    int posicion;

    for (int i = 0; i < jugada.contador; i++) {         //Se recorre las fichas de la jugada
        for (int j = 0; j < soporte.contador; j++) {
            if ((jugada.jugada[i].numero == soporte.ficha[j].numero) && (jugada.jugada[i].color == soporte.ficha[j].color)) {
                posicion = j;
            }
        }
        for (int j = posicion; j < soporte.contador - 1; j++) {     //Se elimina la ficha del soporte
            soporte.ficha[j] = soporte.ficha[j + 1];
        }
        soporte.contador--;         //Se le resta 1 al contador del soporte
    }
}

bool ponerFicha(tJugada& jugada, tFicha& ficha) {
    int tipo_jugada = 0, aux = 0, repetida;
    bool poner_ficha = true, eq_color = false;

    for (int i = 0; i < jugada.contador - 1; i++) {           //Se comprueba si es serie o escalera
        if ((jugada.jugada[i].color != jugada.jugada[i + 1].color) && (jugada.jugada[i].numero == jugada.jugada[i + 1].numero)) {
            tipo_jugada = 1;          //Es una serie
        }
        else if ((jugada.jugada[i].color == jugada.jugada[i + 1].color) && (jugada.jugada[i].numero == jugada.jugada[i + 1].numero - 1)) {
            tipo_jugada = 2;        //Es una escalera
        }           //No hay mas opciones ya que la jugada, al estar en el tablero, tiene que ser correcta
    }

    repetida = buscar(jugada, ficha);       //Se comprueba que la ficha no este en la jugada
    if (repetida == -1) {   //No esta en la jugada
        if (tipo_jugada == 1) {             //Si es una serie
            for (int i = 0; i < jugada.contador; i++) {
                if (ficha.color == jugada.jugada[i].color) {
                    eq_color = true;            //Se comprueba que el color de la ficha no se repita
                }
            }

            if (((eq_color == false) && (ficha.numero == jugada.jugada[0].numero)) && (jugada.contador < 4)) {  //Si no se repite y se podria colocar
                for (int i = 0; i < jugada.contador; i++) {     //Se coloca la ficha de manera que se quede toda la jugada (serie) ordenada por color
                    if ((ficha.color < jugada.jugada[i].numero) && (aux == 0)) {
                        for (int j = jugada.contador; j > i; j--) {
                            jugada.jugada[j] = jugada.jugada[j - 1];
                        }
                        jugada.jugada[i] = ficha;
                        aux++;
                    }
                }
                jugada.contador++;      //Se le suma uno al contador por la ficha añadida
            }
            else {
                poner_ficha = false;            //No se puede meter la ficha
            }
        }
        else {                          //Si es una escalera
            if (((ficha.numero == jugada.jugada[0].numero - 1) && (ficha.color == jugada.jugada[0].color)) && (jugada.contador < 13)) {
                for (int i = jugada.contador; i > 0; i--) {                             //Se puede meter la ficha por el principio de la escalera
                    jugada.jugada[i] = jugada.jugada[i - 1];
                }
                jugada.jugada[0] = ficha;
                jugada.contador++;
            }
            else if (((ficha.numero == jugada.jugada[jugada.contador - 1].numero + 1) && (ficha.color == jugada.jugada[jugada.contador - 1].color)) && (jugada.contador < 13)) {
                jugada.jugada[jugada.contador] = ficha;                                 //Se puede meter la ficha por el final de la escalera
                jugada.contador++;
            }
            else {
                poner_ficha = false;                                                //No se puede meter la ficha en la jugada
            }
        }
    }

    return poner_ficha;
}

bool jugar(tTablero& tablero, tSoporte& soporte) {
    bool jugar = false, verificar = true, poner_ficha;
    int comprobar = -1, tablero_jugada;
    tJugada jugada;
    

    jugada.contador = nuevaJugada(soporte, jugada);            //Se llama a la funcion nuevaJugada

    //Se comprueba si puede ser una serie
    if (jugada.contador > 2 && jugada.contador < 5) {         //Se comprueba el numero de fichas que hay
        for (int i = 0; i < jugada.contador - 1; i++) {
            if ((jugada.jugada[i].color != jugada.jugada[i + 1].color) && (jugada.jugada[i].numero == jugada.jugada[i + 1].numero)) {
                comprobar = 1;
            }
            else {
                verificar = false;                  //Si verificar es falso, es porque no es una serie
            }
        }
    }
    //Si no es serie, se comprueba que sea escalera
    if (jugada.contador > 2 && jugada.contador < 13) {          //Se comprueba el numero de fichas que hay
        if (verificar == false) {
            comprobar = 2;
            verificar = true;                       //Se parte de la base de que es una escalera y se comprueba si es cierto
            for (int i = 0; i < jugada.contador - 1; i++) {
                if ((jugada.jugada[i].color == jugada.jugada[i + 1].color) && (jugada.jugada[i].numero == jugada.jugada[i + 1].numero - 1)) {
                    comprobar = 2;
                }
                else {
                    verificar = false;                          //Si verificar es falso, es porque no es una escalera
                }
            }
        }
    }
    //Si no es nada de lo anterior, se comprueba si es una sola ficha a introducir
    if (jugada.contador == 1) {
        for (int i = 0; i < tablero.contador; i++) {
            jugar = false;
            poner_ficha = ponerFicha(tablero.jugadas[i], jugada.jugada[0]);     //Se coloca la ficha si se puede
            if (poner_ficha == true) {
                jugar = true;
                comprobar = 0;                  //Se indica que es una ficha colocada
                tablero_jugada = i;
            }
        }
    }
    if (verificar == false) {
        comprobar = -1;
    }

    if (comprobar != -1) {          //Si es una jugada valida
        cout << endl << "Jugada: ";     //Se muestra la jugada
        for (int i = 0; i < jugada.contador; i++) {
            mostrar(jugada.jugada[i]);
        }

        if (comprobar == -1) {                               //Se escribe si ha hecho serie, escalera, ficha colocada o nada
            cout << " - No es una jugada correcta! Prueba de nuevo...";
        }
        else if (comprobar == 1) {
            cout << " - Serie correcta!";
        }
        else if (comprobar == 2) {
            cout << " - Escalera correcta!";
        }
        else if (comprobar == 0) {
            cout << endl << "Jugadas del tablero donde poner la ficha: " << tablero_jugada + 1 << "  -> Colocada!" << endl;
        }

        jugar = true;                               //Se devuelve true, si la jugada es correcta
        tablero.jugadas[tablero.contador].contador = 0;
        if (comprobar != 0) {
            for (int i = 0; i < jugada.contador; i++) {     //Se introduce la jugada en el tablero
                tablero.jugadas[tablero.contador].jugada[i] = jugada.jugada[i];
                tablero.jugadas[tablero.contador].contador++;
            }
            tablero.contador++;
        }
        eliminaFichas(soporte, jugada);             //Se eliminan las fichas del soporte
        mostrar(tablero);                           //Se muestra el tablero
    }

    return jugar;
}

int menu() {
    int opcion;

    cout << endl;
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
