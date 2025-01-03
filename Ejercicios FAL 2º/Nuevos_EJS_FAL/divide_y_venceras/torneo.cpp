
#include <iostream>

using namespace std;


/*
(1) En caso de utilizar una generalizacion,
determinaci�n de los par�metros de la generalizaci�n.
Determina los par�metros de la generalizaci�n. Para cada par�metro
indica: (i) su tipo; (ii) su nombre; (iii) si es un par�metro
de entrada, de salida, o de entrada / salida; (iv) su prop�sito,
descrito de manera clara y concisa.


(2) An�lisis de casos:

(2.1) Casos base


(2.2) Casos recursivos

(3) En caso de utilizar una generalizacion, definici�n por inmersi�n
del algoritmo. Describe de manera clara y concisa c�mo se lleva a
cabo el algoritmo, en qu� punto o puntos se invoca a la generalizaci�n,
con qu� par�metros reales, y c�mo se genera el resultado
a partir de los devueltos por la generalizaci�n.

(4) An�lisis de la complejidad del algoritmo

*/

bool factible(int enemigos[], int n, int max_duelos, int poder) {	//esta funcion comprueba si con el maximo de duelos que hay, el
	int poder_actual = poder;									//poder que se le pasa como parametro y el array del poder de los 
	int i = 0;														//enemigos, se puede vencer o no, y lo devuelve
	bool factible = true;
	while (i < n && factible) {
		poder_actual -= enemigos[i];
		if (poder_actual < 0) {
			if (max_duelos > 1) {
				max_duelos--;
				poder_actual = poder;
			}
			else {								//si entra aqui, es porque no ha podido vencer con los parametros dados, y devolvera false
				factible = false;
			}
		}
		else {
			i++;
		}

	}
	return factible;
}

int min_poder_aux(int enemigos[], int n, int max_duelos, int min, int max) {
	if (max - min + 1 == 1) {			//CASO BASE (cuando solo hay un elemento)
		return max;						//devuelve max o min, es indiferente ya que en este caso son el mismo valor(porque max - min + 1 == 1)
	}	
	else {								//CASO RECURSIVO
		int m = (max + min) / 2;
		if (factible(enemigos, n, max_duelos, m)) {		//si con los parametros dados se puede vencer, entonces se busca algun valor mas pequeño(ya que tiene que ser el minimo
			return min_poder_aux(enemigos, n, max_duelos, min, m);
		}
		else {											//sino, se busca un valor mas grande
			return min_poder_aux(enemigos, n, max_duelos, m + 1, max);
		}
	}








}
void acotar(int enemigos[], int n, int& min_poder, int& max_poder) {
	min_poder = 0;				//esta funcion SOLO actualiza los valores de max_poder y min_poder
	max_poder = 0;

	for (int i = 0; i < n; i++) {
		min_poder = max(min_poder, enemigos[i]);
		max_poder = max_poder + enemigos[i];
	}
}


int min_poder(int enemigos[], int n, int max_duelos) {
	// Punto de entrada al algoritmo: a implementar
	int max, min;
	acotar(enemigos, n, min, max);		//min = el menor numero(ya que es el menor valor que puede tomar la solucion del problema
										//max = la suma de todos los valores, ya que es el mayor valor que puede tomar la solucion del problema
	return min_poder_aux(enemigos, n, max_duelos, min, max);
}


const int MAX_ENEMIGOS = 1000;
bool ejecuta_caso() {
	int enemigos[MAX_ENEMIGOS];
	int num_enemigos;
	cin >> num_enemigos;
	if (num_enemigos == -1) {
		return false;
	}
	else {
		int max_torneos;
		cin >> max_torneos;
		for (int i = 0; i < num_enemigos; i++) {
			cin >> enemigos[i];
		}
		cout << min_poder(enemigos, num_enemigos, max_torneos) << endl;
		return true;
	}
}

int main() {
	while (ejecuta_caso());
}