//Jorge López Carrión y David Cendejas Rodriguez 2ºD

#include <iostream>

using namespace std;

const int TMAX = 1000000;  // No habrá vectores de más de un millón de elementos


/*

PRECONDICION DE LA FUNCION: 

  P (es equivalente a) 0<n<=1000000 (y) a[i] <= a[i+1]
  

*/

 
int misterio(const int a[], int n) {
	int i = 0, valor = a[0], cuenta = 1, aux = 1;
	bool comprobar = true;

	while (i < n - 1) {
		if (a[i] == a[i + 1]) {
			cuenta++;
			if (cuenta > aux) {
				valor = a[i];
				comprobar = true;
			}
		}
		else {
			if (comprobar) {
				aux = cuenta;
			}
			cuenta = 1;
			comprobar = false;
		}
		i++;
	}

	return valor;
} 

/* COMPLEJIDAD:
   El orden de complejidad del algoritmo en el peor caso es de orden n.
   El algoritmo se basa en un bucle que depende de n y de una variable bool, por tanto en el peor caso,
   el coste del algoritmo es de complejidad lineal
*/


/* CODIGO PARA LEER Y EJECUTAR LOS CASOS DE PRUEBA. NO MODIFICAR */

void lee_vector(int a[], int & n) {
	cin >> n; 
   for (int i=0; i < n; i++) {
	   cin >> a[i]; 
   }   
}

int main() {
	static int a[TMAX];
	int n;
   do {
	   lee_vector(a,n); 
	   if (n>=0) {
		   cout << misterio(a, n) << endl;
	   }
   }
   while (n != -1);
}