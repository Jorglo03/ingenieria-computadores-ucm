/*
NOMBRES Y APELLIDOS DE LOS MIEMBROS DEL GRUPO QUE HAN REALIZADO LA PRACTICA:


Si alguno de los miembros del grupo no ha realizado
la pr�ctica, indicarlo aqu�, junto con el motivo:


*/


#include <iostream>

using namespace std;

static const int MAX_HOSPITALES = 20;
static const int MAX_PACIENTES = 20;

// Representaci�n de los datos de entrada
typedef struct {
	int distancia[MAX_PACIENTES][MAX_HOSPITALES]; // distancia[p][h] es la distancia que separa al paciente 'p'
	                                              // del hospital 'h'
	int capacidad[MAX_HOSPITALES]; // capacidad[i]: N�mero de pacientes que caben en el hospital i.
	int num_hospitales; // N�mero de hospitales
	int num_pacientes; // N�mero de pacientes;
} tEntrada;

/*
(1) �C�mo son las soluciones parciales viables de este problema?

(2) �Cu�ndo una soluci�n es final?

(3) Dada una soluci�n viable, �c�mo se generan nuevas soluciones viables a partir de ella?

(4) �C�mo se representar�n las soluciones en este problema? Describe los distintos elementos
    de informaci�n que las componen, indicando si se representan como par�metros de entrada,
	de entrada/salida (estado global), si se representan impl�citamente...

(5) �Qu� marcadores utiliza el algoritmo? Describe claramente su prop�sito, los elementos
    de informaci�n que los componen, as� como si dichos elementos se representan como par�metros
	de entrada, de entrada/salida (estado global)... 

(6) Si el algoritmo utiliza generalizaci�n, indica como es la misma, describiendo claramente
    el prop�sito de cada par�metro.
	
(7) An�lisis de casos: casos base, casos recursivos

(8) Si el algoritmo utiliza una generalizaci�n, describe c�mo se implementa el algoritmo
    en t�rminos de la misma (inmersi�n)

*/

void min_distancias_aux(const tEntrada& entrada, int& mejor_distancia, int distancia_actual, int paciente_actual, int capacidad[], int min_distancia_posible, const int distancia_minima[]) {
	if (entrada.num_pacientes == paciente_actual) {
		if (distancia_actual < mejor_distancia) {
			mejor_distancia = distancia_actual;
		}
	}
	else {
		for (int i = 0; i < entrada.num_hospitales; i++) {

			if (capacidad[i] > 0 && distancia_actual + entrada.distancia[paciente_actual][i] * 2 + min_distancia_posible - distancia_minima[paciente_actual] * 2 < mejor_distancia) {
				capacidad[i]--;
				min_distancias_aux(entrada, mejor_distancia, distancia_actual + entrada.distancia[paciente_actual][i] * 2, paciente_actual + 1, capacidad, min_distancia_posible - distancia_minima[i],distancia_minima);
				capacidad[i]++;
			}
		}
	}
}



int min_distancias(const tEntrada& entrada) {
	// A IMPLEMENTAR
	int mejor_distancia = 0;
	int distancia_minima[MAX_PACIENTES];
	int min_distancia_posible = 0;

	for (int i = 0; i < entrada.num_pacientes; i++) {
		distancia_minima[i] = entrada.distancia[i][0] * 2;
		int d_max = entrada.distancia[i][0] * 2;
		for (int j = 1; j < entrada.num_hospitales; j++) {
			if (entrada.distancia[i][j] * 2 < distancia_minima[i]) {
				distancia_minima[i] = entrada.distancia[i][j] * 2;
			}
			else if (entrada.distancia[i][j] * 2 > d_max) {
				d_max = entrada.distancia[i][j] * 2;
			}
		}
		mejor_distancia += d_max;
		min_distancia_posible += distancia_minima[i];
	}

	int capacidad[MAX_HOSPITALES];
	for (int i = 0; i < entrada.num_hospitales; i++) {
		capacidad[i] = entrada.capacidad[i];
	}

	min_distancias_aux(entrada, mejor_distancia, 0, 0, capacidad, min_distancia_posible, distancia_minima);


	return mejor_distancia;
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
	cout << min_distancias(entrada) << endl;
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		ejecuta_caso();
	}
}