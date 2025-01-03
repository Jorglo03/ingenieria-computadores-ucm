#include <iostream>

using namespace std;

const int TMAX = 2000000;  // No habr� vectores de m�s de dos millones de elementos


/*

PRECONDICION DE LA FUNCION:
  ---Escribe aqu� la precondici�n de la funci�n.


*/
bool es_gaspariforme(const int a[], int n);

/*
POSTCONDICION DE LA FUNCION:
  -- Escribe aqu� la postcondici�n de la funci�n. Para referirte
  -- al resultado puedes usar la pseudovariable 'resul'




 */


 /*
 DISE�O DEL ALGORITMO:
 -- Especifica cada paso del dise�o en cada apartado indicado

 Paso 1. Variables


 Paso 2. Invariante


 Paso 3. Inicializaci�n



 Paso 4. Condici�n del bucle, y c�digo tras el bucle



 Paso 5. Cuerpo del bucle



 Paso 6. Justificaci�n de que el algoritmo siempre termina



 Paso 7. Complejidad


 */



bool es_gaspariforme(const int a[], int n) {
	/* IMPLEMENTACION: COMPLETA EL CUERPO DE LA FUNCION
	   CON EL CODIGO QUE IMPLEMENTA EL ALGORITMO */
	int i = 0, suma = 0;
	while (i < n) {
		suma += a[i];
		if (i == n - 1) {			//ultimo caso
			if (suma != 0)			//si no es cero, entonces no es gaspariforme
				return false;
		}
		else if (suma <= 0) {		//si alguna suma parcial no es positiva, no es gaspariforme
			return false;
		}


		i++;
	}
	return true;				//caso de 0 elementos, o si consigue salir del bucle, entonces si es gaspariforme
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