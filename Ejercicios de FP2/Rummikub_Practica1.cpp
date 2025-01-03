//Jorge López Carrión y David Cendejas Rodriguez 1ºA Fundamentos de la Programación 2

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;
										//Se declaran las constantes necesarias
const int NumJugadores = 4;				//Entre	2 y 4
const int NumFichas = 13;				//Entre	8 y 13
const int IniFichas = 14;				//Entre	6 y 14
const int MaxFichas = 50;
const int MAX_JUGADAS = NumFichas * 2;
const int FichasColores = 8;
const int Colores = 4;

typedef enum { rojo, verde, azul, amarillo, blanco, libre } tColor;		//Se declaran los tipos necesarios
typedef struct {
	tColor color;
	int numero;
} tFicha;
typedef tFicha tFichas[MaxFichas];
typedef struct {
	tFichas ficha;
	int contador;
}tSoporte;
typedef tSoporte tSoportes[NumJugadores];
typedef tFicha tArrayBolsa[FichasColores][NumFichas];
typedef struct {
	tArrayBolsa bolsa;
	int contador;
}tBolsa;
typedef tFicha tFichasJugadas[NumFichas];
typedef struct {
	tFichasJugadas jugada;
	int contador;
}tJugada;
typedef tJugada tJugadas[MAX_JUGADAS];
typedef struct {
	tJugadas jugadas;
	int contador;
}tTablero;

int menu();									//Se declaran las prototipos de las funciones
void inicializarBolsa(tBolsa& bolsa);
tFicha robar(tBolsa& bolsa);
void repartir(tBolsa& bolsa, tSoportes& soportes);
void ordenarPorNum(tSoporte& soporte);
void ordenarPorColor(tSoporte& soporte);
int buscar(const tJugada& jugada, const tFicha& ficha);
void eliminaFichas(tSoporte& soporte, const tJugada& jugada);
void iniJugada(tJugada& jugada);
int nuevaJugada(tSoporte& soporte, tJugada& jugada);
bool ponerFicha(tJugada& jugada, tFicha& ficha);
int contarJugadas(tTablero tablero, tJugada jugada, int indJugadas[MAX_JUGADAS], int& contJugadas);
bool jugar(tTablero& tablero, tSoporte& soporte);
int menor(const tSoportes soportes);
bool operator== (tFicha izq, tFicha der);
void mostrar(const tFicha& ficha);
void mostrar(const tBolsa& bolsa);
void mostrar(const tJugada& jugada);
void mostrar(const tTablero& tablero);
void mostrar(const tSoporte& soporte);
void mostrarIndices(int num);
void mostrarSeries(const tSoporte& soporte);
void mostrarEscaleras(const tSoporte& soporte);
void colorTexto(tColor color);

int main() {
	int jugador, opcion, ganador, pos_ganador, fin_partida = 0, repeticion = -1;
	int sumas[NumJugadores];
	tFicha ficha_robada;
	tSoportes soportes;
	tBolsa bolsa;
	tTablero tablero;
	tablero.contador = 0;
	bool ganar = false, jugado = false;

	srand(time(NULL));

	cout << "---------RUMMIKUB---------" << endl << endl;
	inicializarBolsa(bolsa);
	repartir(bolsa, soportes);

	jugador = rand() % NumJugadores;			//Empieza aleatoriamente un jugador

	cout << "Turno para el jugador " << jugador + 1 << " ..." << endl;
	mostrar(tablero);
	mostrar(soportes[jugador]);

	opcion = menu();				  //Se le la opcion con la funcion menu
	while (ganar == false) {		  //Mientras no haya ganador, que se siga jugando

		switch (opcion) {
		case 0:												//case 0
			if (jugado == false) {							//Si no ha jugado 
				ficha_robada = robar(bolsa);			   	//roba una ficha
				if (ficha_robada.numero != -1) {
					if (soportes[jugador].contador < MaxFichas) {
						soportes[jugador].ficha[soportes[jugador].contador] = ficha_robada;
						soportes[jugador].contador++;           //Se aumenta el contador
						mostrar(soportes[jugador]);
					}
					else {
						cout << "Su soporte esta lleno" << endl;
					}
				}
				else {
					cout << "No hay mas fichas en la bolsa para robar." << endl << endl << endl;	//Si no hay mas fichas en la bolsa
					fin_partida++;							//Se cuentan los turnos que van pasando
					if (fin_partida == NumJugadores) {		//Si juegan todos los jugadores sin hacer jugadas
						ganar = true;						//Entonces hay un ganador del juego
						ganador = menor(soportes);			//Devuelve la menor suma de las todas las fichas de cada soporte

						for (int i = 0; i < NumJugadores; i++) {	//Calcula la suma de todas las fichas de cada soporte y las guarda
							sumas[i] = 0;
							for (int j = 0; j < soportes[i].contador; j++) {
								sumas[i] = sumas[i] + soportes[i].ficha[j].numero;
							}
						}
						for (int i = 0; i < NumJugadores; i++) {		//Se comprueba si hay empate entre varios jugadores		
							if (ganador == sumas[i]) {
								repeticion++;
								pos_ganador = i;
							}
						}
						if (repeticion == 0) {							//Si repeticion == 0, entonces hay un unico ganador
							cout << "Ha ganado el jugador " << pos_ganador + 1 << ", cuyas fichas suman una puntuacion de ";
							cout << ganador << " puntos!" << endl;
						}
						else if (repeticion > 0) {						//Si repeticion > 0, ha habido un empate
							cout << "Ha habido un empate entre los jugadores ";
							for (int i = 0; i < NumJugadores; i++) {	//Se escriben los jugadores que han empatado
								if (ganador == sumas[i]) {
									cout << i + 1 << " ";
								}
							}
							cout << "que han acabado con una puntuacion de " << ganador << " puntos!" << endl;
						}												// y la cantidad de puntos con los que han empatado
					}
				}
			}
			else {					//Si un jugador hace una jugada, se restablece el contador de turnos para terminar el juego
				fin_partida = 0;
			}
			if (ganar == false) {
				jugado = false;
				cout << endl;
				if (jugador == NumJugadores - 1) {                      //Se cambia de jugador
					jugador = 0;
				}
				else if (jugador < NumJugadores - 1) {
					jugador++;
				}
				jugado = false;

				cout << "Turno para el jugador " << jugador + 1 << " ..." << endl;
				mostrar(tablero);
			}

			break;

		case 1:									//Opcion 1
			ordenarPorColor(soportes[jugador]);	//Se ordena de manera que queden ordenados principalmente por numero y luego por color
			ordenarPorNum(soportes[jugador]);

			break;

		case 2:									//Opcion 2
			ordenarPorNum(soportes[jugador]);	//Se ordenan de manera que queden ordenados principalmente por color y luego por numero
			ordenarPorColor(soportes[jugador]);

			break;

		case 3:									//Opcion 3
			mostrarSeries(soportes[jugador]);	//Se muestran todas las series y escaleras que se pueden hacer con el soporte dado
			mostrarEscaleras(soportes[jugador]);

			break;

		case 4:									//Opcion 4
			mostrar(soportes[jugador]);			//Se muestra el soporte del jugador con el indice de cada ficha
			mostrarIndices(soportes[jugador].contador);

			jugado = jugar(tablero, soportes[jugador]);		//Se llama a la funcion jugar y devuelve si ha jugado o no

			break;
		}

		if (ganar == false) {
			mostrar(soportes[jugador]);

			if (soportes[jugador].contador != 0) {			//Si un jugador se ha quedado sin fichas
				opcion = menu();							//Se lee la siguiente opcion
			}
			else {
				ganar = true;								//Y hay un ganador
				cout << endl << "El jugador " << jugador + 1 << " ha ganado!" << endl;
			}
		}
	}

	return 0;
}


int menu() {												//Menu del programa
	int opcion;

	do {
		cout << "1: Ordenar por num.";
		cout << ", 2: Ordenar por color";
		cout << ", 3: Sugerir";
		cout << ", 4: Poner";
		cout << ", 0: Fin >>> ";
		cin >> opcion;
	} while (opcion < 0 || opcion > 4);

	return opcion;											//Devuelve la opcion escogida
}


void inicializarBolsa(tBolsa& bolsa) {

	for (int i = 0; i < FichasColores; i++) {				//Se ordena la matriz de la bolsa y se organiza segun su numero y su color
		for (int j = 0; j < NumFichas; j++) {
			if (i == 0 || i == 4) {							//Se marcan las filas en las que las fichas seran del color indicado
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
			bolsa.bolsa[i][j].numero = j + 1;	//El numero de la ficha correspondiente sera la columna+1, ya que las fichas empiezan en 1
		}
	}
}

tFicha robar(tBolsa& bolsa) {
	tFicha ficha;
	int fila, columna, fila_inicial, columna_inicial;
	bool aux = true;
	ficha.numero = -1;
	ficha.color = libre;

	fila = rand() % FichasColores;							//Se escogen aleatoriamente las fichas para robar
	columna = rand() % NumFichas;
	fila_inicial = fila;
	columna_inicial = columna;

	if (bolsa.bolsa[fila][columna].color != libre) {		//Se hay ficha en la posicion dada, se coge
		ficha = bolsa.bolsa[fila][columna];
	}
	else {
		while ((ficha.color == libre) && (aux == true)) {
			if (fila == FichasColores - 1 && columna == NumFichas - 1) {        //Si esta en la ultima casilla
				fila = 0;
				columna = 0;
			}
			else if (columna == NumFichas - 1) {       //Si esta en la ultima fila
				columna = 0;
				fila++;
			}
			else {                                     //Si esta en cualquier otra casilla
				columna++;
			}
			if (bolsa.bolsa[fila][columna].color != libre) {					//Hay ficha en la columna y fila indicada
				ficha = bolsa.bolsa[fila][columna];
			}
			if (fila == fila_inicial && columna == columna_inicial) {			//Si no hay mas dichas en toda la bolsa
				aux = false;
			}
		}
	}
	bolsa.bolsa[fila][columna].color = libre;			//Se indica que la ficha indicada no se encuentra en la bolsa
	bolsa.bolsa[fila][columna].numero = -1;

	return ficha;										//Devuelve la ficha escogida
}

void repartir(tBolsa& bolsa, tSoportes& soportes) {

	for (int k = 0; k < NumJugadores; k++) {            //Para un numero de jugadores indicados
		soportes[k].contador = 0;
		for (int i = 0; i < IniFichas; i++) {           //Para un numero de fichas que obtener indicado
			soportes[k].ficha[i] = robar(bolsa);        //Se roba la ficha
			soportes[k].contador++;                     //Se van contando las fichas con el contador
		}
	}
}

void ordenarPorNum(tSoporte& soporte) {
	tFicha aux;
	int i = 0;
	bool comprobar = true;

	//Mediante el metodo de la burbuja mejorado se ordenan los numeros de menor a mayor
	while ((i < soporte.contador - 1) && comprobar) {
		comprobar = false;
		for (int j = soporte.contador - 1; j > i; j--) {						//Se recorren con orden descendente
			if (soporte.ficha[j].numero < soporte.ficha[j - 1].numero) {		//Se comprueba si hay cambios que hacer
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

	//Mediante el metodo de la burbuja mejorado se ordenan los colores segun estan en el enum ordenados
	while ((i < soporte.contador - 1) && comprobar) {
		comprobar = false;
		for (int j = soporte.contador - 1; j > i; j--) {		//Se recorren con orden descendente
			if (soporte.ficha[j].color < soporte.ficha[j - 1].color) {			//Se comprueba si hay cambios que hacer
				aux = soporte.ficha[j];
				soporte.ficha[j] = soporte.ficha[j - 1];
				soporte.ficha[j - 1] = aux;
				comprobar = true;
			}
		}
		i++;
	}
}

int buscar(const tJugada& jugada, const tFicha& ficha) {
	int posicion = -1;											//Devuelve -1 si no esta la ficha en la jugada

	for (int i = 0; i < jugada.contador; i++) {					//Busca la posicion de la ficha en el array y devuelve la posicion
		if ((ficha.color == jugada.jugada[i].color) && (ficha.numero == jugada.jugada[i].numero)) {
			posicion = i;
		}
	}
	return posicion;
}

void eliminaFichas(tSoporte& soporte, const tJugada& jugada) {
	int posicion = 0;

	for (int i = 0; i < jugada.contador; i++) {					//Se recorre la jugada
		for (int j = 0; j < soporte.contador; j++) {
			if (jugada.jugada[i] == soporte.ficha[j]) {
				posicion = j;									//Se busca la posicion de la ficha en el soporte
			}
		}
		for (int j = posicion; j < soporte.contador - 1; j++) {
			soporte.ficha[j] = soporte.ficha[j + 1];			//Se elimina la ficha (de la cual tenemos la posicion) de la soporte
		}
		soporte.contador--;
	}
}

void iniJugada(tJugada& jugada) {								//Se inicializan todos los numeros de la ficha de la jugada
	for (int i = 0; i < jugada.contador; i++) {
		jugada.jugada[i].numero = -1;
	}
	jugada.contador = 0;
}

int nuevaJugada(tSoporte& soporte, tJugada& jugada) {
	int num_fichas = 0, posicion;
	bool repeticion = false;
	tSoporte soporte_aux;

	for (int i = 0; i < soporte.contador; i++) {
		soporte_aux.ficha[i] = soporte.ficha[i];
	}

	iniJugada(jugada);											//Se inicializa la jugada

	cout << endl << "Fichas (0 al final): ";
	do {														//Con este bucle
		cin >> posicion;										//Se leen las posiciones de las fichas

		if (soporte_aux.ficha[posicion - 1].numero == -1) {
			cout << "Error, no repita fichas ya puestas en la jugada" << endl;
			repeticion = true;
		}
		else if (posicion != 0 && (posicion > 0 && posicion <= soporte.contador)) {	//La ficha esta en el soporte y es distinta de 0
			jugada.jugada[num_fichas] = soporte_aux.ficha[posicion - 1];			//Se introducen en la jugada las fichas escogidas
			soporte_aux.ficha[posicion - 1].numero = -1;
			num_fichas++;
		}
	} while (posicion != 0);

	if (repeticion == true) {
		num_fichas = 0;
	}

	return num_fichas;       //Devuelve el numero de fichas de la jugada
}

bool ponerFicha(tJugada& jugada, tFicha& ficha) {
	int tipo_jugada = 0, repetida;
	bool poner_ficha = true, eq_color = false;

	repetida = buscar(jugada, ficha);       //Se comprueba que la ficha no este en la jugada

	if (repetida == -1) {					//Si no esta en la jugada
		for (int i = 0; i < jugada.contador - 1; i++) {						//Se comprueba si es serie o escalera
			if ((jugada.jugada[i].color != jugada.jugada[i + 1].color) && (jugada.jugada[i].numero == jugada.jugada[i + 1].numero)) {
				tipo_jugada = 1;			//Es una serie
			}
			else if ((jugada.jugada[i].color == jugada.jugada[i + 1].color) && (jugada.jugada[i].numero == jugada.jugada[i + 1].numero - 1)) {
				tipo_jugada = 2;			//Es una escalera
			}								//No hay mas opciones ya que la jugada, al estar en el tablero, tiene que ser correcta
		}

		if (tipo_jugada == 1) {             //Si es una serie
			for (int i = 0; i < jugada.contador; i++) {
				if (ficha.color == jugada.jugada[i].color) {
					eq_color = true;		//Se comprueba que el color de la ficha no se repita
				}
			}

			if ((eq_color == false) && (ficha.numero == jugada.jugada[0].numero)) {  //Se puede colocar la ficha
				jugada.jugada[jugada.contador] = ficha;
				jugada.contador++;			//Se le suma uno al contador por la ficha añadida
			}
			else {
				poner_ficha = false;		//No se colocar meter la ficha
			}
		}
		else {								//Si es una escalera
			if ((ficha.numero == jugada.jugada[0].numero - 1) && (ficha.color == jugada.jugada[0].color)) {
				for (int i = jugada.contador; i > 0; i--) {			//Se puede meter la ficha por el principio de la escalera
					jugada.jugada[i] = jugada.jugada[i - 1];
				}
				jugada.jugada[0] = ficha;
				jugada.contador++;
			}
			else if ((ficha.numero == jugada.jugada[jugada.contador-1].numero + 1) && (ficha.color == jugada.jugada[jugada.contador-1].color)) {
				jugada.jugada[jugada.contador] = ficha;				//Se puede meter la ficha por el final de la escalera
				jugada.contador++;
			}
			else {
				poner_ficha = false;		//No se puede meter la ficha en la jugada
			}
		}
	}
	else {
		poner_ficha = false;
	}

	return poner_ficha;						//Devuelve si la ficha se puede meter en la jugada
}
//Cuenta el numero de jugadas en las que se puede introducir una ficha
int contarJugadas(tTablero tablero, tJugada jugada, int indJugadas[MAX_JUGADAS], int& contJugadas) { 

	for (int i = 0; i < tablero.contador; i++) {
		if (ponerFicha(tablero.jugadas[i], jugada.jugada[0])) {
			if (contJugadas == 0) {
				cout << endl << "La ficha se puede insertar en la/s jugada/s  ";
			}
			indJugadas[contJugadas] = i;		//Escribe las psibles jugadas y las guarda
			cout << "(" << i + 1 << ")  ";
			contJugadas++;
		}
	}

	return contJugadas;			//Devuelve las jugadas en las que se pueden introducir la ficha
}

bool jugar(tTablero& tablero, tSoporte& soporte) {
	bool jugar = false, verificar = false, poner_ficha, comprobarPonFicha = false;
	int comprobar = -1, num_jugada, numJugadas_posibles, contJugadas = 0;;
	int indJugadas[MAX_JUGADAS];
	tJugada jugada;
	tJugada aux;
	aux.contador = 4;	//Se inicializa a 4 ya que son el mayor numero de fichas con las que se puede hacer una serie
	iniJugada(aux);

	jugada.contador = nuevaJugada(soporte, jugada);			//Se llama a la funcion nuevaJugada
	cout << "Jugada: ";
	mostrar(jugada);

	//Se comprueba si puede ser una serie
	if ((jugada.contador > 2 && jugada.contador < 5) && ((tablero.contador < MAX_JUGADAS) && (tablero.contador >= 0))) {
		verificar = true;
		for (int i = 0; i < jugada.contador - 1; i++) {
			if ((jugada.jugada[i].color != jugada.jugada[i + 1].color) && (jugada.jugada[i].numero == jugada.jugada[i + 1].numero)) {
				if (aux.contador == 0) {	//Si son las primeras se guardan las dos fichas en el array auxiliar
					aux.jugada[jugada.jugada[i].color] = jugada.jugada[i];
					aux.contador++;
					aux.jugada[jugada.jugada[i + 1].color] = jugada.jugada[i + 1];
					aux.contador++;
					comprobar = 1;
				}
				else {
					if (aux.jugada[jugada.jugada[i + 1].color].numero == -1) {	//Se comprueba que no se repita el color
						aux.jugada[jugada.jugada[i + 1].color] = jugada.jugada[i + 1];
						aux.contador++;											//Se guarda
					}
					else {
						verificar = false;										//No es una serie
					}
				}
			}
			else {
				verificar = false;							//Si verificar es falso, es porque no es una serie
			}
		}
	}
	//Si no es serie, se comprueba que sea escalera
	if ((jugada.contador > 2 && jugada.contador < 13) && ((tablero.contador < MAX_JUGADAS) && (tablero.contador >= 0))) {
		if (verificar == false) {
			comprobar = 2;
			verificar = true;		//Se parte de la base de que es una escalera y se comprueba si es cierto
			for (int i = 0; i < jugada.contador - 1; i++) {
				if ((jugada.jugada[i].color == jugada.jugada[i + 1].color) && (jugada.jugada[i].numero == jugada.jugada[i + 1].numero - 1)) {
					comprobar = 2;
				}
				else {
					verificar = false;					//Si verificar es falso, es porque no es una escalera
				}
			}
		}
	}
	//Si no es nada de lo anterior, se comprueba si es una sola ficha a introducir
	if (jugada.contador == 1) {
		verificar = true;
		numJugadas_posibles = contarJugadas(tablero, jugada, indJugadas, contJugadas);	
		if (numJugadas_posibles >= 1) {				//Se cuentan en cuantas jugadas se puede ingresar
			comprobar = 0;
		}
		else {
			verificar = false;
		}
	}

	if (verificar == false) {						//No es una jugada correcta
		comprobar = -1;
	}

	if (comprobar != -1) {								//Si es una jugada valida
		if (comprobar == 1) {
			cout << " - Serie correcta!" << endl;		//Se escribe si ha hecho serie, escalera o ficha colocada
		}
		else if (comprobar == 2) {
			cout << " - Escalera correcta!" << endl;
		}
		else if (comprobar == 0) {						//Si es una sola ficha a colocar
			if (numJugadas_posibles == 1) {				//Si solo se puede colocar en una jugada, se coloca
				for (int i = 0; i < tablero.contador; i++) {
					ponerFicha(tablero.jugadas[i], jugada.jugada[0]);
				}
				cout << " -> Ficha colocada!" << endl;
			}
			else {						//Si se puede colocar en varias jugadas se pregunta en que jugada debe ser colocada
				cout << endl << "Introduzca en la jugada en la que quiere insertar la ficha: ";
				do {
					poner_ficha = false;
					cin >> num_jugada;						
					for (int i = 0; i < contJugadas; i++) {		//Se comprueba si es una jugada correcta
						if (indJugadas[i] == num_jugada - 1) {
							comprobarPonFicha = true;
						}
					}
					if (comprobarPonFicha == true) {			//Si es correcta, se pone la ficha en la jugada
						ponerFicha(tablero.jugadas[num_jugada - 1], jugada.jugada[0]);
						cout << "Ficha colocada!" << endl;
						poner_ficha = true;
					}
					else {
						cout << "Esa jugada no esta disponible, introduzca otra: "; //Si no es correcta, se vuelve a pedir
					}
				} while (poner_ficha == false);
			}
		}

		jugar = true;										//Se devuelve true, si la jugada es correcta
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
	else {
		if ((tablero.contador < MAX_JUGADAS) && (tablero.contador >= 0)) {
			cout << " - No es una jugada correcta! Prueba de nuevo..." << endl << endl;
		}
		else {
			cout << " - No se pueden insertar mas jugadas nuevas, rellena las jugadas creadas con nuevas fichas." << endl << endl;
		}
	}

	return jugar;				//Devuelve true o false, dependiendo el jugador ha jugado o no
}

int menor(const tSoportes soportes) {
	int ganador;
	int sumas[NumJugadores];

	for (int i = 0; i < NumJugadores; i++) {		//Calcula la suma de todas las fichas de cada soporte y las guarda
		sumas[i] = 0;
		for (int j = 0; j < soportes[i].contador; j++) {
			sumas[i] = sumas[i] + soportes[i].ficha[j].numero;
		}
	}

	ganador = sumas[0];
	for (int i = 1; i < NumJugadores; i++) {		//Comprueba cual es la menor suma entre todos los soportes
		if (ganador > sumas[i]) {
			ganador = sumas[i];
		}
	}

	return ganador;			//Devuelve la minima suma entre todos las fichas de cada soporte
}

bool operator== (tFicha izq, tFicha der) {			//Convierte el operador == para la igualdad entre fichas
	bool operador;

	if ((izq.color == der.color) && (izq.numero == der.numero)) {
		operador = true;
	}
	else {
		operador = false;
	}

	return operador;		//Devuelve true o false si es correcto o no
}

void mostrar(const tFicha& ficha) {					//Muestra las fichas, ocupando 2 espacios y con dos espacios mas de margen

	colorTexto(ficha.color);						//Se escriben con el color determinado para cada ficha
	cout << setw(2) << ficha.numero << "  ";
	colorTexto(blanco);
}
void mostrar(const tBolsa& bolsa) {					//Muestra la bolsa

	cout << "Bolsa..." << endl;
	for (int i = 0; i < FichasColores; i++) {		//Recorriendo la matriz, se escribe toda con su respectivo color y numero
		for (int j = 0; j < NumFichas; j++) {
			mostrar(bolsa.bolsa[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

void mostrar(const tJugada& jugada) {				//Muestra las fichas de la jugada dada

	if (jugada.contador != 0) {
		for (int i = 0; i < jugada.contador; i++) {
			mostrar(jugada.jugada[i]);
		}
	}
	else {
		cout << " Sin fichas ";
	}
}

void mostrar(const tTablero& tablero) {			//Muestra las fichas del tablero

	cout << endl << "Tablero:";
	if (tablero.contador != 0) {
		cout << endl;
		for (int i = 0; i < tablero.contador; i++) {
			cout << setw(2) << i + 1 << ": ";	//Indica que jugada del tablero es
			for (int j = 0; j < tablero.jugadas[i].contador; j++) {
				mostrar(tablero.jugadas[i].jugada[j]);
			}
			cout << endl;
		}
		cout << endl;
	}
	else {
		cout << " No hay jugadas" << endl;
	}
	cout << endl;
}

void mostrar(const tSoporte& soporte) {			//Muestra el soporte dado

	cout << "Soporte: ";
	if (soporte.contador != 0) {
		for (int i = 0; i < soporte.contador; i++) {
			mostrar(soporte.ficha[i]);
		}
	}
	else {
		cout << "Vacio";
	}
	cout << endl;
}

void mostrarIndices(int num) {					//Muestra los indices de los soportes desde 1 hasta num

	cout << "        ";
	for (int i = 1; i <= num; i++) {
		cout << setw(3) << i << " ";
	}
}

void mostrarSeries(const tSoporte& soporte) {	//Muestra las posibles series con el soporte dado
	tSoporte aux, serie;
	serie.contador = 0;

	for (int i = 0; i < soporte.contador; i++) {        //Se pasa el soporte a un array auxiliar
		aux.ficha[i] = soporte.ficha[i];
	}
	aux.contador = soporte.contador;
	ordenarPorColor(aux);
	ordenarPorNum(aux);									//Se ordena principalmente por numero y a mismo numero, por color

	for (int i = 0; i < aux.contador - 1; i++) {        //Se recorre el array
		if (((aux.ficha[i].color != aux.ficha[i + 1].color) && (aux.ficha[i].numero == aux.ficha[i + 1].numero)) && (serie.contador == 0)) {
			serie.ficha[serie.contador] = aux.ficha[i];	//Si dos numeros cumplen los requisitos para ser una posible serie 
			serie.contador++;							// y son los primeros se introducen los dos en el array "serie"
			serie.ficha[serie.contador] = aux.ficha[i + 1];
			serie.contador++;
		}
		else if ((aux.ficha[i].color != aux.ficha[i + 1].color) && (aux.ficha[i].numero == aux.ficha[i + 1].numero)) {
			serie.ficha[serie.contador] = aux.ficha[i + 1];	//Si dos numeros cumplen los requisitos para ser una posible serie
			serie.contador++;								// y no son los primerosse introduce en el array "serie" el segundo
			if ((i == aux.contador - 2) && (serie.contador > 2)) {	//Se imprimen en pantalla si son los ultimos y pueden formar serie
				for (int j = 0; j < serie.contador; j++) {
					mostrar(serie.ficha[j]);
				}
				cout << endl;
			}
		}
		else if (aux.ficha[i] == aux.ficha[i + 1]) {				//Si son la misma ficha
			if ((i == aux.contador - 2) && (serie.contador > 2)) {	//Se imprimen en pantalla su son los ultimos y pueden formar serie
				for (int j = 0; j < serie.contador; j++) {
					mostrar(serie.ficha[j]);
				}
				cout << endl;
			}
		}
		else {
			if (serie.contador > 2) {		//Si hay mas de dos fichas que cumplan la opcion de que puedan hacer una serie, se escriben
				for (int j = 0; j < serie.contador; j++) {
					mostrar(serie.ficha[j]);
				}
				cout << endl;
			}
			serie.contador = 0;				//Se inicializa el contador a 0 para que vuelva a buscar nuevas series
		}
	}
}

void mostrarEscaleras(const tSoporte& soporte) {	//Muestra las posibles escaleras con el soporte dado
	tSoporte aux, escalera;
	escalera.contador = 0;

	for (int i = 0; i < soporte.contador; i++) {     //Se pasa el soporte a un array auxiliar
		aux.ficha[i] = soporte.ficha[i];
	}
	aux.contador = soporte.contador;
	ordenarPorNum(aux);
	ordenarPorColor(aux);							//Se ordena principalmente por color, y a mismo color, por numero

	for (int i = 0; i < aux.contador - 1; i++) {
		if (((aux.ficha[i].color == aux.ficha[i + 1].color) && (aux.ficha[i].numero == aux.ficha[i + 1].numero - 1)) && (escalera.contador == 0)) {
			escalera.ficha[escalera.contador] = aux.ficha[i];	//Si dos numeros cumplen los requisitos para ser una posible escalera
			escalera.contador++;								// y son los primeros se introducen los dos en el array "escalera"
			escalera.ficha[escalera.contador] = aux.ficha[i + 1];
			escalera.contador++;
		}
		else if ((aux.ficha[i].color == aux.ficha[i + 1].color) && (aux.ficha[i].numero == aux.ficha[i + 1].numero - 1)) {
			escalera.ficha[escalera.contador] = aux.ficha[i + 1];	//Si dos numeros cumplen los requisitos para ser una posible escalera
			escalera.contador++;									// y no son los primeros se introduce el segundo en el array "escalera"
			if ((i == aux.contador - 2) && (escalera.contador > 2)) {	//Se imprimen en pantalla si son los ultimos y pueden formar escalera
				for (int j = 0; j < escalera.contador; j++) {
					mostrar(escalera.ficha[j]);
				}
				cout << endl;
			}
		}
		else if (aux.ficha[i] == aux.ficha[i + 1]) {				//Si son la misma ficha
			if ((i == aux.contador - 2) && (escalera.contador > 2)) {
				for (int j = 0; j < escalera.contador; j++) {
					mostrar(escalera.ficha[j]);
				}
				cout << endl;
			}
		}
		else {
			if (escalera.contador > 2) {	//Si hay mas de dos fichas que cumplan la opcion de ser una escalera, se escriben
				for (int j = 0; j < escalera.contador; j++) {
					mostrar(escalera.ficha[j]);
				}
				cout << endl;
			}
			escalera.contador = 0;			//Se inicializa el contador a 0 para que vuelva a buscar nuevas escaleras
		}
	}
}

void colorTexto(tColor color) {				//Cambia el texto al color dado

	switch (color) {
	case amarillo:
		cout << "\033[1;40;33m";
		break;
	case azul:
		cout << "\033[40;34m";
		break;
	case rojo:
		cout << "\033[40;31m";
		break;
	case verde:
		cout << "\033[40;32m";
		break;
	case blanco:
		cout << "\033[40;37m";
		break;
	}
}