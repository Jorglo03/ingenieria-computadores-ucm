// NOMBRE Y APELLIDOS:
// USUARIO DEL JUEZ:


#include <iostream>
#include <string>
#include "Arbin.h"
using namespace std;



/** INDICA AQUÍ JUSTIFICADAMENTE LA COMPLEJIDAD DEL ALGORITMO
	O(n) ya que se recorre , en el peor de los casos, cada nodo una sola vez
	**/

void numImparColgantes_aux(Arbin<int> a, int& numImparColgantes, int& suma_descendientes, int suma_ancestros) {

	if (a.esVacio()) {
		suma_descendientes = 0;
	}
	else {
		int suma_descendientes1, suma_descendientes2;

		if (a.raiz() % 2 == 1) {
				suma_ancestros += a.raiz();
		}
		if (!a.hijoIz().esVacio() && !a.hijoDer().esVacio()) {
			
			numImparColgantes_aux(a.hijoIz(), numImparColgantes, suma_descendientes1, suma_ancestros);
			numImparColgantes_aux(a.hijoDer(), numImparColgantes, suma_descendientes2, suma_ancestros);
			suma_descendientes = suma_descendientes1 + suma_descendientes2;
		}
		else if (!a.hijoDer().esVacio()) {
			numImparColgantes_aux(a.hijoDer(), numImparColgantes, suma_descendientes1, suma_ancestros);
			suma_descendientes = suma_descendientes1;
		}
		else {
			numImparColgantes_aux(a.hijoIz(), numImparColgantes, suma_descendientes1, suma_ancestros);
			suma_descendientes = suma_descendientes1;
		}

		

		

		if (suma_descendientes > suma_ancestros - a.raiz()) {
			numImparColgantes++;
		}

		if (a.raiz() % 2 == 1) {
			suma_descendientes += a.raiz();
		}
	}

}

int numImparColgantes(Arbin<int> a) {
	// IMPLEMENTA AQUÍ EL SUBPROGRAMA
	if (a.esVacio()) {
		return 0;
	}
	else {
		int numImparColgantes = 0, suma_descendientes, suma_ancestros = 0;
		numImparColgantes_aux(a, numImparColgantes, suma_descendientes, suma_ancestros);
		return numImparColgantes;
	}
	
}



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



void ejecuta_caso() {
	Arbin<int> a = lee_arbol(cin);
	cout << numImparColgantes(a);
	cout << endl;
}


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF) {
		ejecuta_caso();
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}