/* NO MODIFICAR NADA EN ESE ARCHIVO */

#include <iostream>
#include <sstream>
#include "lista.h"

using namespace std;


void lee_lista(Lista<int>& l, int nelems) {
	for (int i = 0; i < nelems; i++) {
		int v;
		cin >> v;
		l.pon_final(v);
	}
}

bool ejecuta_caso() {
	int k;
	cin >> k;
	if (k != -1) {
		int n;
		cin >> n;
		Lista<int> l;
		lee_lista(l, n);
		try {
			l.k_malea(k);
			l.imprime(cout); cout << "#"; l.imprime_invertida(cout); cout << endl;
		}
		catch (EArgumentoInvalido) {
			cout << "ERROR" << endl;
		}
		return true;
	}
	else {
		return false;
	}
}



int main() {
	while (ejecuta_caso()) {}
	return 0;
}