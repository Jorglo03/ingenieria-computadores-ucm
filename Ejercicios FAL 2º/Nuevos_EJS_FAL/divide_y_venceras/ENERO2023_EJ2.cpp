/*
NOMBRE Y APELLIDOS:

*/

#include <iostream>
using namespace std;


/*
Nota: NO es necesario que especifiques el algoritmo, ni las
funciones auxiliares utilizadas. Pero, en caso de utilizar
una generalización, sí debes describir sus parámetros, 
su resultado, y el próposito de los mismos 

(1) SI UTILIZAS UNA GENERALIZACION, DETALLA AQUÍ SUS PARÁMETROS,
    SU RESULTADO, Y EL PROPÓSITO DE LOS MISMOS 
	Utilizo una generalizacion que devuelve si hay un numero ninu-nifa en el vector
	int a[]=>vector de entrada
	int n=>numero de elementos del vector
	int i=>inicio del tramo que se esta resolviendo
	int f=>final del tramo que se esta resolviendo

(2) DISEÑO (CASOS)
	if (f - i + 1<= 1) {    si hay un elemento, es porque no se ha encontrado ningun numero nifunifa
		return false;
	}
	else {
		int m = (i + f) / 2;		mitad
		if (a[m] != a[0] && a[m] != a[n - 1]) {		si se encuentra que el numero del medio es nifunifa, se devuelve ya true
			return true;
		}
		else {
			if (a[m] == a[0]) {					si es igual que el primero, se busca en la derecha
				return hay_nifunifa_aux(a, n, m+1, f);
			}
			else if (a[m] == a[n - 1]) {		si es igual que el ultimo , se busca en la izquierda
				return hay_nifunifa_aux(a, n, i, m);
			}
		}
	}

(3) JUSTIFICACION DE LA TERMINACION DEL ALGORITMO
	f-i es una expresion de cota, por lo tanto el algoritmo termina

(4) IMPLEMENTACION POR INMERSION DEL ALGORITMO, SI PROCEDE
bool hay_nifunifa_aux(int a[], int n, int i, int f)
	donde a y n son siempre el vector y el numero de elementos inicial que da como datos el problema, 
	e i y f son el principio y el final del subproblema, que se va reduciendo a la mitad en cada llamada recursiva

(5) DETERMINACION DEL COSTE DEL ALGORITMO EN EL PEOR CASO
	T(n) = c0, f - i + 1<= 1
	T(n) = c0 + T(n/2), el resto

	a= 1
	b = 2
	k=0
	a=b^k => O(n^k * log n) = O(log n)

	Por tanto el coste es logaritmico
*/


bool hay_nifunifa_aux(int a[], int n, int i, int f) {
	if (f - i + 1<= 1) {
		return false;
	}
	else {
		int m = (i + f) / 2;
		if (a[m] != a[0] && a[m] != a[n - 1]) {
			return true;
		}
		else {
			if (a[m] == a[0]) {
				return hay_nifunifa_aux(a, n, m+1, f);
			}
			else if (a[m] == a[n - 1]) {
				return hay_nifunifa_aux(a, n, i, m);
			}
		}
	}
}
/**** PROGRAMA DE PRUEBA: NO MODIFICAR ****/

bool hay_nifunifa(int a[], int n) {
	// A IMPLEMENTAR



	return hay_nifunifa_aux(a, n, 0, n-1);

}

/**** PROGRAMA DE PRUEBA: NO MODIFICAR ****/


const static int MAX_ELEMS=1000000;
bool ejecuta_caso() {
  	static int a[MAX_ELEMS];
	int n;
	cin >> n;
	if (n == -1) return false;
	else {
      for (int i=0; i < n; i++) {
		  cin >> a[i];
	  }
	  if (hay_nifunifa(a,n)) {
		  cout << "SI" << endl;
	  }
	  else {
	      cout << "NO" << endl;
	  }	  
      return true;	  
	}
}

int main() {
	while(ejecuta_caso());
}
