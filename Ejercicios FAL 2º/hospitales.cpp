/*
NOMBRES Y APELLIDOS DE LOS MIEMBROS DEL GRUPO QUE HAN REALIZADO LA PRACTICA:

Jorge López Carrión


Si alguno de los miembros del grupo no ha realizado la práctica, indicarlo aquí, junto con el motivo:
David Cendejas Rodríguez no ha realizado esta práctica.

*/

#include <iostream>

using namespace std;

static const int MAX_HOSPITALES = 20;
static const int MAX_PACIENTES = 20;

// Representación de los datos de entrada
typedef struct {
	int distancia[MAX_PACIENTES][MAX_HOSPITALES]; // distancia[p][h] es la distancia que separa al paciente 'p' del hospital 'h'
	  
	int capacidad[MAX_HOSPITALES]; // capacidad[i]: Número de pacientes que caben en el hospital i.
	int num_hospitales; // Número de hospitales
	int num_pacientes; // Número de pacientes;
} tEntrada;

typedef struct {
	int capacidad[MAX_HOSPITALES];
} tMarcador;


int min_distancia(const tEntrada& entrada);
void mejor_recorrido(tEntrada datos, int i, tMarcador& marcador, bool& hay_distancia, int distancia, int& mejor_distancia);


/*
(1) ¿Cómo son las soluciones parciales viables de este problema?

	Para que se de una solucion parcial de este problema tiene que tener hueco disponible el hospital que estemos analizando, lo cual lo consideramos con
	los marcadores de capacidad del hospital.

(2) ¿Cuándo una solución es final?
	
	Es una solucion final si i == entrada.num_pacientes, y si entra la primera vez, es decir que hay_distancia == false, y se parte de esa solucion, o si
	distancia < mejor_distancia, que en este caso se tiene que reemplazar la solucion mejor que teniamos, ya que habremos encontrado una mejor solucion 
	para el problema.


(3) Dada una solución viable, ¿cómo se generan nuevas soluciones viables a partir de ella?
	
	Se van recorriendo los hospitales, siempre que tengan hueco y se va actualizando la distancia que llevamos recorrida, siempre que no sea mayor que la 
	mejor_distancia que teniamos hasta ese momento. Se va incrementando en uno la variable contadora, hasta que lleguemos al caso de que i == entrada.num_pacientes,
	y entonces si se puede se actualiza la mejor_distancia hasta el momento.


(4) ¿Cómo se representarán las soluciones en este problema? Describe los distintos elementos
    de información que las componen, indicando si se representan como parámetros de entrada,
	de entrada/salida (estado global), si se representan implícitamente...
	
	Las soluciones de este problema representaran posibles soluciones a el problema general, y nos quedaremos con la mas eficaz, que se actualizara en el caso
	base, al comprobar si la distancia que llevamos es menor que la que teniamos antes guardado como "mejor_distancia".

(5) ¿Qué marcadores utiliza el algoritmo? Describe claramente su propósito, los elementos
    de información que los componen, así como si dichos elementos se representan como parámetros
	de entrada, de entrada/salida (estado global)... 

	El algoritmo utiliza marcadores que son una struct llamada tMarcador, en la que se utiliza un marcador para controlar la capacidad de un hospital, 
	es decir, si le queda capacidad, o ya no, que por tanto no se deberia tener en cuenta.

(6) Si el algoritmo utiliza generalización, indica como es la misma, describiendo claramente el propósito de cada parámetro.
	
	El algoritmo utiliza generalizacion con la funcion
	proc minimo_recorrido(in tEntrada entrada,in int i,inout tMarcador marcador,inout bool hay_distancia,in int distancia,in int mejor_distancia).
	"entrada" contiene los datos de entrada que introduce el usuario, "i" es una variable de entrada que lleva el conteo para saber si ya hemos llegado al caso base
	e i == entrada.num_pacientes, "marcador" es el marcador del problema, "hay_distancia" es una variable de entrada y salida que se pondra a true la primera vez que
	i == entrada.num_pacientes, y por tanto haya una mejor_solucion, "distancia" llevara la distancia que se lleve actualmente mientras se ejecuta el algoritmo,
	y "mejor_solucion" sera una variable de entrada y salida ya que sera la solucion, que contendra la menor distancia que haya encontrado el algortimo.

(7) Análisis de casos: casos base, casos recursivos
	
	CASO BASE:
	if (i == entrada.num_pacientes):
		Si es la primera vez que i == entrada.num_pacientes (!hay_distancia) o distancia < mejor_distancia, entonces se indica que ya hay una distancia guardada
		y se guarda la distancia que se lleva recorrida como mejor_distancia.
	CASO RECURSIVO:
		Se recorren todos los hospitales, haciendo las marcaciones pertinentes al principio y al final del bucle y llamando a la funcion recursiva mejor_recorrido

(8) Si el algoritmo utiliza una generalización, describe cómo se implementa el algoritmo en términos de la misma (inmersión)

	La inmersión se ejecuta al final de la funcion min_distancia, donde se le pasa como parametros
	entrada(entrada que introduce el usuario), 0(variable contadora), marcador, hay_distancia(false al principio), 
	0 (distancia que se lleva hasta ese momento), mejor_distancia (sera la solucion del problema).

*/


void mejor_recorrido(tEntrada entrada, int i, tMarcador& marcador, bool& hay_distancia, int distancia, int& mejor_distancia) {

	if (i == entrada.num_pacientes) {
		if (!hay_distancia || distancia < mejor_distancia) {

			mejor_distancia = distancia;		
			hay_distancia = true;

		}
	}
	else {
		for (int hospital = 0; hospital < entrada.num_hospitales; hospital++) {
			if (marcador.capacidad[hospital] > 0) {

				marcador.capacidad[hospital]--;		//marcar

				mejor_recorrido(entrada, i + 1, marcador, hay_distancia, distancia + entrada.distancia[i][hospital], mejor_distancia);
				
				marcador.capacidad[hospital]++;		//desmarcar

			}
		}
	}
}

int min_distancia(const tEntrada& entrada) {
	tMarcador marcador;
	int sol = 0;
	int mejor_distancia = 0;
	bool hay_distancia = false;

	for (int i = 0; i < entrada.num_hospitales; i++) {
		marcador.capacidad[i] = entrada.capacidad[i];
	}
	
	mejor_recorrido(entrada, 0, marcador, hay_distancia, 0, mejor_distancia);
	sol = 2 * mejor_distancia;		 //ida y vuelta

	return sol;
}

/*** A PARTIR DE AQUI NO MODIFICAR EL CODIGO ***/

void ejecuta_caso() {
	tEntrada entrada;
	cin >> entrada.num_pacientes >> entrada.num_hospitales;
	for (int h = 0; h < entrada.num_hospitales; h++) {
		cin >> entrada.capacidad[h];
    }
	for (int p = 0; p < entrada.num_pacientes; p++) {
		for (int h = 0; h < entrada.num_hospitales; h++) {
			cin >> entrada.distancia[p][h];
 		}
	}
	cout << min_distancia(entrada) << endl;
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		ejecuta_caso();
	}
}