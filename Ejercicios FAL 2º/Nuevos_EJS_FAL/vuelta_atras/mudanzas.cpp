
#include <iostream>

using namespace std;

const int MAX_OBJS = 20;

// Lista con los objetos a portar 
typedef struct {
	int tamanios[MAX_OBJS];  // Array en cuyas primeras posiciones se guardan
							 // los tamaños de los objetos
	int n_objetos;           // Numero de objetos
} tObjetos;



/*

(1) En caso de utilizar una generalización, indicar su parámetros, y explicar para que
sirven cada uno de ellos

(2) ¿Cómo son las soluciones parciales de este problema?

(3) ¿Cuándo una solución parcial es viable?

(4) ¿Cuándo una solución parcial es una solución final al problema?

(5) Dada una solución parcial, ¿cómo se generan las siguientes soluciones
parciales viables?

(6) Análisis de casos

(6.1) Caso(s) base


(6.2) Caso(s) recursivos

(7) En caso de utilizar una generalización, explicar cómo se define el algoritmo final
a partir de la misma, por inmersión.



*/


void min_numero_de_cajas_aux(const tObjetos& objetos, int capacidad_caja, int objeto_actual, int cajas[], int num_cajas_usadas, int& mejor_num_cajas_usadas) {
	if (objetos.n_objetos == objeto_actual) {		//ya se han introducido todos los objetos en cajas
		if (mejor_num_cajas_usadas > num_cajas_usadas)	//Si es un numero mejor de cajas que el conseguido hasta el momento
			mejor_num_cajas_usadas = num_cajas_usadas;
	}
	else {
		//se inserta en una caja ya existente
		for (int i = 0; i < num_cajas_usadas; i++) {
			if (cajas[i] + objetos.tamanios[objeto_actual] <= capacidad_caja) {
				cajas[i] += objetos.tamanios[objeto_actual];
				if (num_cajas_usadas < mejor_num_cajas_usadas)	//poda
					min_numero_de_cajas_aux(objetos, capacidad_caja, objeto_actual + 1, cajas, num_cajas_usadas, mejor_num_cajas_usadas);
				
				cajas[i] -= objetos.tamanios[objeto_actual];
			}
		}
		//caja nueva
		if (num_cajas_usadas < mejor_num_cajas_usadas) {		//poda
			if (objetos.tamanios[objeto_actual] > 0) {
				cajas[num_cajas_usadas] += objetos.tamanios[objeto_actual];
				num_cajas_usadas++;

				min_numero_de_cajas_aux(objetos, capacidad_caja, objeto_actual + 1, cajas, num_cajas_usadas, mejor_num_cajas_usadas);

				num_cajas_usadas--;
				cajas[num_cajas_usadas] -= objetos.tamanios[objeto_actual];
			}
			else {		//si el objeto pesa 0, no hay caja nueva
				min_numero_de_cajas_aux(objetos, capacidad_caja, objeto_actual + 1, cajas, num_cajas_usadas, mejor_num_cajas_usadas);
			}
		}
	}

}

int min_numero_de_cajas(const tObjetos& objetos, int capacidad_caja) {
    int cajas_usadas[MAX_OBJS];

	for (int i = 0; i < objetos.n_objetos; i++) {
		cajas_usadas[i] = 0;
	}
	int mejor_num_cajas_usadas = objetos.n_objetos;

    min_numero_de_cajas_aux(objetos, capacidad_caja, 0, cajas_usadas, 0, mejor_num_cajas_usadas);

	return mejor_num_cajas_usadas;
}

/* CODIGO PARA LEER Y EJECUTAR LOS CASOS DE PRUEBA */

bool ejecuta_caso() {
	int capacidad;
	cin >> capacidad;
	if (capacidad != -1) {
		tObjetos objetos;
		cin >> objetos.n_objetos;
		for (int i = 0; i < objetos.n_objetos; i++) {
			cin >> objetos.tamanios[i];
		}
		cout << min_numero_de_cajas(objetos, capacidad) << endl;
		return true;
	}
	else {
		return false;
	}
}

int main() {
	while (ejecuta_caso());
}