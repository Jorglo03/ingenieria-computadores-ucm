//Jorge L�pez Carri�n y David Cendejas Rodr�guez 2�D

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;



bool esta_ordenado(int a[], int n) {
	bool resultado = true;

  	int i = 0;
	while (resultado && i < n - 1) {
		resultado = (a[i+1] >= a[i]);
		i++;
	}


	return resultado;
}


/* CODIGO PARA LEER Y EJECUTAR LOS CASOS DE PRUEBA - NO MODIFICAR */

const int TMAX = 1000000;  // No se podr�n leer vectores de m�s de un mill�n de elementos

bool ejecuta_caso() {
	static int a[TMAX];
	int n;
	cin >> n;
	if (n == -1 || n > TMAX) {
		return false;
	}
	else {
		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}
		if (esta_ordenado(a, n)) cout << "SI" << endl;
		else cout << "NO" << endl;
		return true;
	}
}

int main() {
	while (ejecuta_caso());
}