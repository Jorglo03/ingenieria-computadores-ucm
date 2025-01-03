#include <iostream>

using namespace std;

/*
DISEÑO DEL ALGORITMO:
El algortimo es utiliza una generalizacion, en la cual tiene como parametros el numero n, dividido / 10, para eliminar
en cada llamada recursiva el digito menos significativo, se le pasa una variable bool, la cual almaceara si, el numero finalmente
es o no sumdivisible, otro parametro que ira guardando la suma de los digitos, y el ultimo parametro que guaradara el numero de digitos.
Se utilizaran variables locales para introducir en las llamadas recursivas para estos parametros
El algoritmo tiene un caso base, si n <= 9, es decir, si ya solo queda un digito, en la cual, se establece el contador de digitos
a 1 y se establece para la variable de calculo de la suma, el numero n, que contendra el digito mas significativo de n incial.
En la llamada recursiva, si n > 9, se crearan unas variables auxiliares y se hara la llamada recursiva, al salir de esta llamada
recursiva, se hara la suma de los digitos  y se incrementara el numero de digitos del valor, y se comprobora el valor actual de resul,
para devolver finalmente en res, si es true o false el resultado.
Definicion por inmersion de sumdivisible:
sumdivisible_aux(n, resul, digito, suma);
el resultado es res.

ANALISIS DE LA COMPLEJIDAD:
Terminacion: n es una cota
Complejidad:
	 Tamaño del problema: n
	 T(n) = co, n<=9
	 T(n) = c1 + T(n/10), n>9
	 T(n) está en O(log n)

	 Tamaño del problema: d, numero de digitos de n
	 T(1) = co
	 T(d) = c1 + T(d-1), n>1
	 O(d^(k+1)) = O(d)

*/

void sumdivisible_aux(int n, bool& res, int& sd, int& nd) {
	if (n <= 9) {
		res = true;
		sd = n;
		nd = 1;
	}
	else {
		bool rp;
		int sdp, ndp;
		sumdivisible_aux(n / 10, rp, sdp, ndp);
		sd = sdp + n % 10;
		nd = ndp + 1;
		res = rp && (sd % nd == 0);
	}

}

bool sumdivisible(int n) {
	bool resul;
	int digito = 1, suma = 0;
	sumdivisible_aux(n, resul, digito, suma);
	return resul;
}   

/* CODIGO DE LECTURA Y EJECUCION DE CASOS DE PRUEBA: 
   NO MODIFICAR */

int main() {
	int n;
	do {
		cin >> n;
		if (n > 0) {
			if (sumdivisible(n)) 
				 cout << "SI" << endl;
			else 
                 cout << "NO" << endl;				
		}
	} while (n > 0);
}
	
	