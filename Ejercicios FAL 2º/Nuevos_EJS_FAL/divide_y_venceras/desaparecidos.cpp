
#include <iostream>
using namespace std;


const int TMAX = 300000;  // No habr� vectores de m�s e 300000 elementos


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



(4)Determina justificadamente la complejidad del algoritmo

(4.1) Determinaci�n de las ecuaciones de recurrencia para la generalizaci�n

(4.2) Resoluci�n utilizando los patrones vistos en clase

(4.3) Determinaci�n justificada de la complejidad del algoritmo final.



*/




int num_perdido_aux(int a[], int n, int i, int f) {

	if (f - i + 1 <= 1) {
		return a[i] - 1;
	}
	else {
		int m = (i + f) / 2;					
		if (a[f] - a[m] == f - m) {
			return num_perdido_aux(a, n, i, m);
		}
		else {
			return num_perdido_aux(a, n, m + 1, f);
		}
	}
}




int num_perdido(int a[], int n) {
	// A IMPLEMENTAR
	int i = 0, f = n - 1;
	return num_perdido_aux(a, n, i, f);
}


/* CODIGO PARA LEER Y EJECUTAR LOS CASOS DE PRUEBA */

bool procesa_caso() {
	static int a[TMAX];
	int n;
	cin >> n;
	if (n == -1) {
		return false;
	}
	else {
		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}
		cout << num_perdido(a, n) << endl;
		return true;
	}
}


int main() {
	while (procesa_caso());
}