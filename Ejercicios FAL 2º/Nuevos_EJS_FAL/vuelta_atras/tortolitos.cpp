
#include <iostream>
using namespace std;

const unsigned int MAX_CLIENTES = 10; // maximo numero de clientes
  // Representaci�n de la matriz de afinidades
typedef struct {
	unsigned int n_clientes;                              // numero de clientes. 
	unsigned int afinidades[MAX_CLIENTES][MAX_CLIENTES];  // la matriz se almacena en las 'n_clientes' primeras filas,
														  // 'n_clientes' primeras columnas	                                                      
} tMatrizAfinidad;

typedef struct {
	int afinidad_max;
	int vector[MAX_CLIENTES];
}tSol;

/*

(1) En caso de utilizar una generalizaci�n, indicar su par�metros, y explicar para que
sirven cada uno de ellos

(2) �C�mo son las soluciones parciales de este problema?

(3) �Cu�ndo una soluci�n parcial es viable?

(4) �Cu�ndo una soluci�n parcial es una soluci�n final al problema?

(5) Dada una soluci�n parcial, �c�mo se generan las siguientes soluciones
parciales viables?

(6) An�lisis de casos

(6.1) Caso(s) base


(6.2) Caso(s) recursivos

(7) En caso de utilizar una generalizaci�n, explicar c�mo se define el algoritmo final
a partir de la misma, por inmersi�n.



*/

void VA( const tMatrizAfinidad& as, tSol& sol, int k, tSol& solMejor) {
	if (k == as.n_clientes) { // es solucion
		if (sol.afinidad_max > solMejor.afinidad_max) {	// es una solucion mejor
			solMejor = sol;
		}
	}
	else {	//no es solucion
		for (int i = 0; i < as.n_clientes; i++) {		//recorre todos los clientes
			//si ninguno de los dos tiene pareja, no son el mismo cliente, y son compatibles entre si
			if (sol.vector[i] == -1 && sol.vector[k] == -1 && k != i && as.afinidades[i][k] > 0 && as.afinidades[k][i] > 0) {

				sol.vector[i] = k;		//anoto que el cliente i va con el cliente k
				sol.vector[k] = i;		//anoto que el cliente k va con el cliente i

				sol.afinidad_max += as.afinidades[k][i];		//suma la afinidad de la fila k y columna i

				VA(as, sol, k + 1, solMejor);

				sol.vector[i] = -1;				//hago todas las demarcaciones
				sol.vector[k] = -1;

				sol.afinidad_max = sol.afinidad_max - as.afinidades[k][i];
			}
			else if (sol.vector[k] == i) {		//si estoy en un cliente con pareja que ya esta marcado
								
				sol.afinidad_max += as.afinidades[k][i];	//sumo la afinidad para completa la suma de los dos clientes de la pareja

				VA(as, sol, k + 1, solMejor);		

							
				sol.afinidad_max = sol.afinidad_max - as.afinidades[k][i];	//se hacen las demarcaciones y se restaura
			}
			
		}
	}
	
}

int maxima_afinidad(const tMatrizAfinidad& as) {
	// Punto de entrada al algoritmo: as representa la matriz de afinidades 
	// (ver definici�n de tMatrizAfinidad). Una vez finalizado el algoritmo,
	// deber� devolverse el valor pedido. Pueden definirse todas las 
	// funciones auxiliares que se considere oportuno.
	tSol sol;
	sol.afinidad_max = 0;
	for (int i = 0; i < as.n_clientes; i++) {
		sol.vector[i] = -1;					//se inicializan a -1 ya que no apuntan a ninguno
	}
	tSol solMejor;
	// inicializo coste mejor a una solucion posible
	solMejor.afinidad_max = 0;
	for (int i = 0; i < as.n_clientes; ++i) {
		solMejor.vector[i] = -1;
	}

	VA(as, sol, 0, solMejor);
	return solMejor.afinidad_max;
}


void ejecuta_caso() {
	tMatrizAfinidad as;
	cin >> as.n_clientes;
	for (unsigned int i = 0; i < as.n_clientes; i++) {
		for (unsigned int j = 0; j < as.n_clientes; j++) {
			cin >> as.afinidades[i][j];
		}
	}
	cout << maxima_afinidad(as) << endl;
}


int main() {
	unsigned int num_casos;
	cin >> num_casos;
	for (unsigned int i = 0; i < num_casos; i++) {
		ejecuta_caso();
	}
}