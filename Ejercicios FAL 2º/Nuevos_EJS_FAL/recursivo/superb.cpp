/*
NOMBRE Y APELLIDOS:

IMPORTANTE: Si no se a�ade el nombre y apellidos,
el ejercicio no se corregir� (puntuar� como 0).

*/

#include <iostream>

using namespace std;


/*
IMPORTANTE: Para superar este ejercicio es necesario desarrollar
correctamente los distintos pasos del dise�o del algoritmo. No
se tendr� en cuenta la codificaci�n del algoritmo, a menos que
est� acompa�ada del dise�o sistem�tico del mismo.
*/


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

bool es_superb_aux(int v[], int n, int i, int f, int& max1, int& min1) {

	if (f - i + 1 < 3) {			//CASO BASE	//Si la longitud es estricamente menor que 3 (lon = 2,1,0)
		max1 = max(v[i], v[f]);		//se coge el maximo
		min1 = min(v[i], v[f]);		//se coge el minimo
		return true;				//se devuelve true ya que cualquier tramo con lon < 3 es superb
	}
	else {							//CASO RECURSIVO
		bool es;				
		int m = (f + i) / 2, max_inf, min_inf;	//se crean m(mitad del tramo) y el maximo inferior, y minimo inferior, ya que a continuacion vamos a recorrer el tramo inferior(desde i hasta m-1, ya que son los que estan antes del elemento central en el vector)
		es = es_superb_aux(v, n, i, m-1, max_inf, min_inf);		//se comprueba si es superb el tramo anterior al elemento central del vector
		if (es) {											//Si es superb ese tramo, se sigue, sino, directamente se devuelve false
			int max_sup, min_sup;							//Ahora se crean las variables para el maximo superior y el minimo superior, que son el tramo que vamos a recorrer ahora, es decir, los elementos que van de m+1 hasta f, los que estan detras del elemento central en el vector
			es = es_superb_aux(v, n, m + 1, f, max_sup, min_sup);	//se comprueba si es superb el tramo posterior al elemento central del vector
			es = es && abs(min_sup - max_inf) == v[m];			//Se comprueba si el conjunto de los dos elementos es superb
			if (es) {
				max1 = max(max_sup, max_inf); //antes de devolver si ese tramo es superb, se guardan los maximos y minimos del tramo conjunto, para la siguiente iteracion tenerlos guardados
				max1 = max(max1, v[m]);
				min1 = min(min_sup, min_inf);
				min1 = min(min1, v[m]);
			}
			return es;									//finalmente se devuelve si ese tramo era superb o no
		}
		else {
			return false;
		}
	}



}

bool es_superb(int v[], int n) {
	// A IMPLEMENTAR: Devolver true si el vector v[n] es superb,
	// y false si no lo es.
	int i = 0, f = n - 1, max, min;
	return es_superb_aux(v, n, i, f, max, min);
}


/************************************************************/
// Programa de prueba: NO MODIFICAR. Aquellas soluciones que
// modifiquen el c�digo que sigue no se corregir�n (puntuar�n 0).


const static int MAX_ELEMENTS = 10000;

bool ejecuta_caso() {
	int n;
	cin >> n;
	if (n == -1) return false;
	else {
		int v[MAX_ELEMENTS];
		for (int i = 0; i < n; i++) {
			cin >> v[i];
		}
		if (es_superb(v, n)) {
			cout << "SUPERB" << endl;;
		}
		else {
			cout << "NO SUPERB" << endl;
		}
		return true;
	}
}


int main() {
	while (ejecuta_caso());
	return 0;
}