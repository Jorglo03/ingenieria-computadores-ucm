
#include "Arbin.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int numeroTramosNavegables_aux(const Arbin<int>& cuenca, int& m);

int numeroTramosNavegables(const Arbin<int>& cuenca) {
	// A IMPLEMENTAR
	int m = 0;
	if (!cuenca.esVacio()) {
		numeroTramosNavegables_aux(cuenca.hijoDer(), m);
		numeroTramosNavegables_aux(cuenca.hijoIz(), m);
		return m;
	}
	return 0;
}

int numeroTramosNavegables_aux(const Arbin<int>& cuenca, int& m) {

	if (cuenca.esVacio()) {	//CASO BASE
		return 1;			
	}
	else {															//CASO RECURSIVO
		int caudal;

		if (cuenca.hijoDer().esVacio()) {
			caudal = numeroTramosNavegables_aux(cuenca.hijoIz(), m);
		}
		else if (cuenca.hijoIz().esVacio()) {
			caudal = numeroTramosNavegables_aux(cuenca.hijoDer(), m);
		}
		else {
			caudal = numeroTramosNavegables_aux(cuenca.hijoDer(), m) + numeroTramosNavegables_aux(cuenca.hijoIz(), m);
		}
		caudal += cuenca.raiz();
		if (caudal < 0) {
			caudal = 0;
		}


		if (caudal >= 3) {
			m++;
		}

		return caudal;
	}
}

Arbin<int> leeArbol(istream& in) {
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
		Arbin<int> iz = leeArbol(in);
		int raiz;
		in >> raiz;
		Arbin<int> dr = leeArbol(in);
		in >> c;
		return Arbin<int>(iz, raiz, dr);
	}
	default: return Arbin<int>();
	}
}

int main() {
	Arbin<int> cuenca;
	while (cin.peek() != EOF) {
		cout << numeroTramosNavegables(leeArbol(cin));
		string restoLinea;
		getline(cin, restoLinea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}