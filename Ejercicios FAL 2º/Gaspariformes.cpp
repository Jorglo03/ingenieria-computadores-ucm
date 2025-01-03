#include <iostream>

using namespace std;

const int TMAX = 2000000;  // No habr� vectores de m�s de dos millones de elementos


/*

PRECONDICION DE LA FUNCION:
  ---Escribe aqu� la precondici�n de la funci�n.
  P (es equivalente a) 0<n<=tam(a)

*/
bool es_gaspariforme(const int a[], int n);

/*
POSTCONDICION DE LA FUNCION:
  -- Escribe aqu� la postcondici�n de la funci�n. Para referirte
  -- al resultado puedes usar la pseudovariable 'resul'

  Q (es equivalente a) resul = PARATODOj: 0 <= j < n-1: (SUMk: 0 <= k <= j: a[k]) > 0 && SUMl: 0 <= l < n: a[l]) = 0

 */


 /*
 DISE�O DEL ALGORITMO:
 -- Especifica cada paso del dise�o en cada apartado indicado

 Paso 1. Variables
	Una variable que contendra el resultado de forma booleana, una variable "i" para recorrer el array, y una variable
	para calcular la sumas parciales

 Paso 2. Invariante
	resul = 0<=i<=n && PARATODOj: 0 <= j < i-1: (SUMk: 0 <= k <= j: a[k]) => 0 && ((i = n-1) -> SUMl: 0 <= l <= i: a[l]) = 0)

 Paso 3. Inicializaci�n
	Se inicia el resultado a true, para ir iterando y comprobando que se va cumpliendo en todos los requisitos la finalidad
	del algoritmo, i se inicializa en 0 para recorrer todo el array, y la suma para calcular las sumas parciales se inicializa
	en 0

 Paso 4. Condici�n del bucle, y c�digo tras el bucle
	La condicion del bucle itera hasta que se recorra todo el array, y tras el bucle, resul ya tendra la solucion, por lo que 
	no hace falta mas codigo

 Paso 5. Cuerpo del bucle
	La condición de continuación del bucle (i<n) garantiza que,inmediatamente antes de comenzar a ejecutar su cuerpo, 
	a[i] tienesentido. Igualmente, ambas condiciones (0<i e i<n) garantizan que, si incrementamos i, se preserva el término 
	del invariante 0<i<=n.
	Primero se suma a[i] a suma y se viola la condicion del bucle, para reestablecerla distinguimo en el bucle
	dos casos: si i < n-1 o si i = n-1
	Si i < n-1, se reestablecera comprobando que suma <= 0, en cambio si i = n-1, se reestablecera comprobando si suma != 0.
	Finalmente se termina reestableciendo incrementando i.


 Paso 6. Justificaci�n de que el algoritmo siempre termina
	En cada iteración incrementamos i. Por tanto, podemos tomar como expresión de cota n – i.

 Paso 7. Complejidad
	La complejidad del algoritmo es de orden n, y en su peor caso tambien es de orden n, que es debido al bucle.

 */



bool es_gaspariforme(const int a[], int n) {
	bool resul = true;
	int i = 0, suma = 0;
	
	while (i < n && resul) {
		suma += a[i];
		if(i < n-1){
			if (suma <= 0) {
				resul = false;
			}
		}
		else if(i == n-1){
			if (suma != 0) {
				resul = false;
			}
		}
		i++;
	}

	return resul;
}


/* CODIGO PARA LEER Y EJECUTAR LOS CASOS DE PRUEBA */

void lee_vector(int a[], int& n) {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
}

int main() {
	static int a[TMAX];
	int n;
	do {
		lee_vector(a, n);
		if (n >= 0) {
			if (es_gaspariforme(a, n))
				cout << "SI" << endl;
			else
				cout << "NO" << endl;
		}
	} while (n >= 0);
}