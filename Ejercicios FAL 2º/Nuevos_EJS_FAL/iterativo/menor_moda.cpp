#include <iostream>

using namespace std;

const int TMAX = 1000000;  // No habr� vectores de m�s de un mill�n de elementos



/*

PRECONDICION DE LA FUNCION:
  ---Escribe aqu� la precondici�n de la funci�n.


*/
int menor_moda(const int a[], int n);

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



int menor_moda(const int a[], int n) {
	int num = a[0], repetido = 1, max_repetido = 1, num_anterior = a[0];
	int i = 1;
	while (i < n) {
		if (a[i] == num_anterior)
			repetido++;
		else if (a[i] != num_anterior)
			repetido = 1;
		if (repetido > max_repetido) {
			max_repetido = repetido;
			num = a[i];
		}
		

		num_anterior = a[i];
		i++;
	}

	return num;
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
			cout << menor_moda(a, n) << endl;
		}
	} while (n != -1);
}