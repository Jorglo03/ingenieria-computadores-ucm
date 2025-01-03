
#include <iostream>

using namespace std;


/*

PRECONDICION DE LA FUNCION:
  ---Escribe aqu� la precondici�n de la funci�n.

*/

int tramo_mas_corto(bool a[], int n, int k);

/*
POSTCONDICION DE LA FUNCION:
  -- Escribe aqu� la postcondici�n de la funci�n. Para referirte
  -- al resultado puedes usar la pseudovariable 'resul'



 */


 /*
 DISE�O DEL ALGORITMO:

 Paso 1. Variables


 Paso 2. Invariante


 Paso 3. Inicializaci�n

 Paso 4. Condici�n del bucle, y c�digo tras el bucle.


 Paso 5. Cuerpo del bucle

 Paso 6. Justificaci�n de que el algoritmo siempre termina.


 Paso 7. Complejidad:


 */



int tramo_mas_corto(bool a[], int n, int k) {
	int tramo_menor = n + 1;		//resultado, en el peor caso es n+1
	int num_unos = 0;				//numero de trues
	int comienza = 0;				//iterador por el principio
	int i = 0;						//iterador por el final

	while (i < n) {
		if (a[i]) {
			num_unos++;
			if (num_unos == 1) {
				comienza = i;		//comienza al encontrar el primer true
			}
			if (num_unos == k) {	//si son el mismo numero de trues que de ks
				if ((i - comienza + 1) < tramo_menor) {	//guardamos la mejor solucion(la longitud mas pequeña entre los k trues que necesitamos)
					tramo_menor = i - comienza + 1;
				}
				comienza++;								//adelantamos la variable de abajo
				num_unos -= 1;							//elimino un true
				while (comienza < n && !a[comienza]) {	//llego con el comienza hasta el siguiente true por debajo
					comienza++;
				}
			}
		}
		i++;
	}
	return tramo_menor;
}

/* CODIGO DE LECTURA Y EJECUCION DE CASOS DE PRUEBA:
   NO MODIFICAR */


void lee_caso(int& n, bool a[], int& k) {
	cin >> n;
	if (n != -1) {
		for (int i = 0; i < n; i++) {
			int elem;
			cin >> elem;
			a[i] = bool(elem);
		}
		cin >> k;
	}
}

const int MAX_TAM = 100;
int main() {
	int n;
	bool a[MAX_TAM];
	int k;
	do {
		lee_caso(n, a, k);
		if (n != -1) {
			cout << tramo_mas_corto(a, n, k) << endl;
		}
	} while (n != -1);
}

