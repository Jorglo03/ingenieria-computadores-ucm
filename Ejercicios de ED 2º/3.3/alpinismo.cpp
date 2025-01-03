#include "Arbin.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void tiempoAyuda_aux(const Arbin<char>& falda, int& sol, int pos);

int tiempoAyuda(const Arbin<char>& falda) {
	// A IMPLEMENTAR
	int m = 0;
	if (falda.esVacio())
		return 0;
	tiempoAyuda_aux(falda, m, 0);
	return m;
}


void tiempoAyuda_aux(const Arbin<char>& falda, int& sol, int pos) {
	if (falda.hijoDer().esVacio() && falda.hijoIz().esVacio()) {		//CASO BASE
		if (falda.raiz() == 'X')
			sol += pos * 2;
	}
	else {										//CASO RECURSIVO
		if (!falda.hijoIz().esVacio())
			tiempoAyuda_aux(falda.hijoIz(), sol, pos+1);
		if (!falda.hijoDer().esVacio())
			tiempoAyuda_aux(falda.hijoDer(), sol, pos+1);
		if (falda.raiz() == 'X')
				sol += pos * 2;
	}

}

Arbin<char> leeArbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<char>();
	case '[': {
		char raiz;
		in >> raiz;
		in >> c;
		return Arbin<char>(raiz);
	}
	case '(': {
		Arbin<char> iz = leeArbol(in);
		char raiz;
		in >> raiz;
		Arbin<char> dr = leeArbol(in);
		in >> c;
		return Arbin<char>(iz, raiz, dr);
	}
	default: return Arbin<char>();
	}
}

int main() {
	Arbin<char> falda;
	while (cin.peek() != EOF) {
		cout << tiempoAyuda(leeArbol(cin));
		string restoLinea;
		getline(cin, restoLinea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}