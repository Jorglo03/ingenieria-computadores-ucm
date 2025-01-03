#include <iostream>

using namespace std;

const int TMAX = 2000000;  // No habra vectores de mas de dos millones de elementos


/*

PRECONDICION DE LA FUNCION:
  P (es equivalente a) 0<=n<=tam(a)


*/
int num_chupiguays(const int a[], int n);

/*
POSTCONDICION DE LA FUNCION:
  -- Escribe aqui la postcondicion de la funcion. Para referirte
  -- al resultado puedes usar la pseudovariable 'resul'

  Q (es equivalente a) resul = #j:0<=j<=n:a[j] % (SUMk:0<=k<j:a[k]) == 0


 */


 /*
 DISE�O DEL ALGORITMO:
 -- Especifica cada paso del disenio en cada apartado indicado

 Paso 1. Variables
	La entrada "suma" para la suma de los numeros que preceden al numero a[i], una variable "i" para recorrer
	el array y el resultado "num_chupi"

 Paso 2. Invariante
	#j:0<=j<=i:a[j] % (SUMk:0<=k<j:a[k]) == 0

 Paso 3. Inicializacion
	 Para recorrer todo el array iniciaremos i = 0, la variable suma la comenzaremos en 0 y el resultado
	 tambien, para obtener el resultado total

 Paso 4. Condicion del bucle, y codigo tras el bucle
	El bucle permitira iterar mientras no se haya recorrido todo el array
	Una vez terminado e bucle se consigue la postcondicion, por lo que no hace falta mas codigo

 Paso 5. Cuerpo del bucle
	En el bucle si suma = 0 && a[i] == 0, entonces se suma una a el resultado, sino, la otra opcion es si suma 
	distinto de 0, entonces se comprueba si a[i] % suma == 0, y si se da, se suma uno al resultado
	Finalmente se suma a[i] a la variable suma, y se hace incrementa una a i para seguir recorriendo el array.

 Paso 6. Justificacion de que el algoritmo siempre termina
	En cada iteración incrementamos i. Por tanto, podemos tomar como expresión de cota n – i.

 Paso 7. Complejidad
	La complejidad es de orden n, y en su peor caso tambien es de orden n la complejidad del algoritmo

 */

int num_chupiguays(const int a[], int n) {
	int suma = 0, num_chupi = 0, i = 0;

	while (i < n) {
		if (suma == 0 && a[i] == 0) {
			num_chupi++;
		}
		else if (suma != 0) {
			if (a[i] % suma == 0) {
				num_chupi++;
			}
		}

		suma += a[i];
		i++;
	}

	return num_chupi;
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
			cout << num_chupiguays(a, n) << endl;
		}
	} while (n != -1);
}