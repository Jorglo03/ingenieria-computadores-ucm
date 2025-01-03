/*
NOMBRE Y APELLIDOS:

IMPORTANTE: Si no se añade el nombre y apellidos,
el ejercicio no se corregirá (puntuará como 0).

*/
#include <iostream>

using namespace std;


const int MAX_PROCESOS = 100;

// Tipo para codificar los datos de entrada
// al problema
typedef struct {
	int t_procesamiento;  // Tiempo de procesamiento 'T' de los procesadores.
						  // Cada procesador permite utizar, como máximo,
						  // 'T' unidades de tiempo.
	int t_procesos[MAX_PROCESOS];  // Unidades de tiempo requeridas por cada proceso. 
	int b_procesos[MAX_PROCESOS];  // Beneficio reportado por cada proceso.
	int n;                         // Número de procesos 'N' (n <= MAX_PROCESOS).
} tEntrada;


/*
IMPORTANTE: Para superar este ejercicio es necesario desarrollar
correctamente los distintos pasos del diseño del algoritmo. No
se tendrá en cuenta la codificación del algoritmo, a menos que
esté acompañada del diseño sistemático del mismo.
*/


/*
(1) En caso de utilizar una generalización, indicar su parámetros, y explicar para que
sirven cada uno de ellos

(2) ¿Cómo son las soluciones parciales de este problema?

(3) ¿Cuándo una solución parcial es viable?

(4) ¿Cuándo una solución parcial es una solución final al problema?

(5) Dada una solución parcial, ¿cómo se generan las siguientes soluciones
parciales viables?

(6) Si estás utilizando algún criterio de poda adicional, explica detalladamente
	el criterio utilizado

(7) Análisis de casos

(7.1) Caso(s) base


(7.2) Caso(s) recursivos

(8) En caso de utilizar una generalización, explicar cómo se define el algoritmo final
a partir de la misma, por inmersión.



*/

/*

2 3
2 1 1
2 2 2
2 5
1 1 1 1 1
1 2 2 1 2
2 4
3 4 1 7
3 5 1 9
6 7
5 3 3 4 5 2 2
9 5 5 4 5 8 3
6 19
5 9 1 8 6 1 2 2 8 7 5 9 5 3 7 4 1 1 9
3 9 8 8 7 8 4 8 6 5 1 7 1 5 3 2 4 3 9
0 0

*/


void max_beneficio_aux(const tEntrada& entrada, int procesador_actual, int& max_beneficio, int beneficio_actual, int tiempo_procesador_1, int tiempo_procesador_2, int maximo_beneficio_restante) {
	if (procesador_actual == entrada.n) {		//CASO BASE
		max_beneficio = beneficio_actual;
	}
	else {										//CASO RECURSIVO
		if (tiempo_procesador_1 - entrada.t_procesos[procesador_actual] >= 0 && beneficio_actual + maximo_beneficio_restante > max_beneficio) {
			max_beneficio_aux(entrada, procesador_actual + 1, max_beneficio, beneficio_actual + entrada.b_procesos[procesador_actual], tiempo_procesador_1 - entrada.t_procesos[procesador_actual], tiempo_procesador_2, maximo_beneficio_restante - entrada.b_procesos[procesador_actual]);
		}	//se prueba a meter en el procesador 1, si queda tiempo de procesamiento suficiente, y si ademas el posible beneficio que queda por conseguir mas que el que se lleva hasta el momento, puede superar al mayor beneficio que tenemos conseguido hasta el momento (poda)

		if (tiempo_procesador_2 - entrada.t_procesos[procesador_actual] >= 0 && beneficio_actual + maximo_beneficio_restante > max_beneficio) {
			max_beneficio_aux(entrada, procesador_actual + 1, max_beneficio, beneficio_actual + entrada.b_procesos[procesador_actual], tiempo_procesador_1, tiempo_procesador_2 - entrada.t_procesos[procesador_actual], maximo_beneficio_restante - entrada.b_procesos[procesador_actual]);
		}	//se prueba a meter en el procesador 2, si queda tiempo de procesamiento suficiente, y si ademas el posible beneficio que queda por conseguir mas que el que se lleva hasta el momento, puede superar al mayor beneficio que tenemos conseguido hasta el momento (poda)

		if (beneficio_actual + (maximo_beneficio_restante - entrada.b_procesos[procesador_actual]) > max_beneficio)
			max_beneficio_aux(entrada, procesador_actual + 1, max_beneficio, beneficio_actual, tiempo_procesador_1, tiempo_procesador_2, maximo_beneficio_restante - entrada.b_procesos[procesador_actual]);
		//se prueba a no meter en ningun procesador si el beneficio que queda por conseguir menos el de esta iteracion(ya que no estamos asignandolo a ningun procesador) mas el beneficio que se lleva hasta el momento, puede superar el maximo beneficio que se ha conseguido (poda)	
	}


}




int max_beneficio(const tEntrada& entrada) {
	// A IMPLEMENTAR: Debe devolver el beneficio máximo
	// que puede conseguirse
	int max_beneficio = 0;
	int maximo_beneficio_restante = 0;
	for (int i = 0; i < entrada.n; i++) {
		maximo_beneficio_restante += entrada.b_procesos[i];
	}

	max_beneficio_aux(entrada, 0, max_beneficio, 0, entrada.t_procesamiento, entrada.t_procesamiento, maximo_beneficio_restante);

	return max_beneficio;
}


/************************************************************/
// Programa de prueba: NO MODIFICAR. Aquellas soluciones que
// modifiquen el código que sigue no se corregirán (puntuarán 0).

bool ejecuta_caso() {
	int t_procesamiento;
	int n_procesos;
	cin >> t_procesamiento >> n_procesos;
	if (t_procesamiento == 0 && n_procesos == 0) {
		return false;
	}
	else {
		tEntrada entrada;
		entrada.n = n_procesos;
		entrada.t_procesamiento = t_procesamiento;
		for (int p = 0; p < n_procesos; p++) {
			cin >> entrada.t_procesos[p];
		}
		for (int p = 0; p < n_procesos; p++) {
			cin >> entrada.b_procesos[p];
		}
		cout << max_beneficio(entrada) << endl;
		return true;
	}
}

int main() {
	while (ejecuta_caso());
	return 0;
}


