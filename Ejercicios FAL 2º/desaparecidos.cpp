
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

Un array de enteros (a), es un parametro de entrada que pretende pasar todos los elementos del array del que necesitamos
sacar una soluci�n.
Un numero entero (i), es un parametro de entrada que pretende pasar el indice del inicio del array donde queremos encontrar 
la soluci�n.
Un numero entero (j), es un parametro de entrada que pretende pasar el indice del final de array donde queremos encontrar
la soluci�n.


(2) An�lisis de casos:

(2.1) Casos base
Si estamos mirando un caso con dos elementos, si la resto de esos elementos es 1, pasa a la siguiente, sino, devuelve el menor
numero - 1.

(2.2) Casos recursivos
Se calcula el numero de la mitad y, si la diferencia entre los indices es igual a la diferencia entre los elementos en esos indices,
se pasa al siguiente, sino, se hace la llamada recursiva por la derecha,y sino se obtiene resultado, por la izquierda.

(3) En caso de utilizar una generalizacion, definici�n por inmersi�n
del algoritmo. Describe de manera clara y concisa c�mo se lleva a
cabo el algoritmo, en qu� punto o puntos se invoca a la generalizaci�n,
con qu� par�metros reales, y c�mo se genera el resultado
a partir de los devueltos por la generalizaci�n.

La recursividad por la derecha se invoca en el caso recursivo, con el array, y el principio y el final de la siguiente
llamada recursiva, y la llamada recursiva por la izquierda se llama, cuando la llamada recursiva por la derecha no ha obtenido
soluci�n.


(4)Determina justificadamente la complejidad del algoritmo

Caso base = C0 si n=2:
Caso recursivo = T(n/2) + C1 si n > 2.

O(log n)
*/

int num_perdido_aux(int a[], int i, int f) {

	if (f - i == 1) {
		if (a[f] - a[i] != 1) {
			return a[f] - 1;
		}
		else {
			return 0;
		}
	}
	else {
		int mitad = (f - i) / 2;
		if (f - i == a[f] - a[i]) {
			return 0;
		}
		else {
 			int maxDerecha = num_perdido_aux(a, i+mitad, f);
			if (maxDerecha != 0) {
				return maxDerecha;
			}
			else {
				return num_perdido_aux(a, i, f-mitad);
			}
		}
	}
}

int num_perdido(int a[], int n) {
	int i = 0;
	int f = n - 1;
	return num_perdido_aux(a, i, f);
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