/*
NOMBRE Y APELLIDOS DE LOS COMPONENTES DEL GRUPO QUE HAN
REALIZADO LA PRÁCTICA: Jorge López Carrión y Abraham Martín Vicente


(si algún componente no ha realizado la práctica,
no debe aparecer)

*/



#include <iostream>
#include <string>
using namespace std;
#include "Arbin.h"


int num_imparBalanceados_aux(const Arbin<int>& a, int& num);

/*
   DETERMINACION JUSTIFICADA DE LA COMPLEJIDAD:
   O(n). Ya que se recorre cada hoja del árbol una sola vez.

                                                                                      
*/
int num_imparBalanceados(const Arbin<int>& a) {
	// A IMPLEMENTAR
	int num = 0;
	if (a.esVacio()) {
		return 0;
	}
	else {
		num_imparBalanceados_aux(a, num);
		return num;
	}
}

int num_imparBalanceados_aux(const Arbin<int>& a, int& num) {
	if (a.hijoDer().esVacio() && a.hijoIz().esVacio()) {			//CASO BASE
		num++;
		if (a.raiz() % 2 != 0) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {										//CASO RECURSIVO

		int num_izq=0, num_der=0;
		if (!a.hijoIz().esVacio())
			num_izq = num_imparBalanceados_aux(a.hijoIz(), num);
		if (!a.hijoDer().esVacio())
			num_der = num_imparBalanceados_aux(a.hijoDer(), num);

		if (num_izq == num_der) {
			num++;
		}
		if (a.raiz() % 2 != 0) {
			return num_izq + num_der + 1;
		}
		return num_izq + num_der;

	}
}


// NO MODIFICAR NADA A PARTIR DE AQUI

Arbin<int> lee_arbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<int>();
	case '[': {
		int raiz;
		in >> raiz;
		in >> c;
		return Arbin<int>(raiz);
	}
	case '(': {
		Arbin<int> iz = lee_arbol(in);
		int raiz;
		in >> raiz;
		Arbin<int> dr = lee_arbol(in);
		in >> c;
		return Arbin<int>(iz, raiz, dr);
	}
	default: return Arbin<int>();
	}
}


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF) {
		Arbin<int> a = lee_arbol(cin);
		cout << num_imparBalanceados(a) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}