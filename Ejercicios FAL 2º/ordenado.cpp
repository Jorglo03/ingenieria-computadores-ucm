//Jorge López Carrión y David Cendejas Rodríguez 2ºD

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

const int TMAX = 1000000;  // No se podrán leer vectores de más de un millón de elementos

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