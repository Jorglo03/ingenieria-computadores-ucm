#include "Memoria.h"
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <string>
using namespace std;



int cont=0;
Memoria<int> valida_copias(Memoria<int> m) {
	Memoria<int> m2(0);
	m2 = m;
	m2 = m2;
	cont++;
	return m2;
}

bool  ejecuta_caso(Memoria<int>& m) {
	m = valida_copias(m);
	string comando;
	cin >> comando;
	if (comando == "load") {
		int d,v;
		cin >> d >> v;
		try {
			m.load(d, v);
			cout << "OK" << endl;
		}
		catch (DireccionInvalida) {
			cout << "DIRECCION_INVALIDA" << endl;
		}
		return true;
	}
	else if (comando == "fetch") {
		int d;
		cin >> d;
		try {
			cout << m.fetch(d) << endl;
		}
		catch (DireccionInvalida) {
			cout << "DIRECCION_INVALIDA" << endl;
		}
		return true;
	}
	else if (comando == "termina") {
		return false;
	}
	return false;
}

void crea_memoria() {
	Memoria<int> m(0);
}

const static int INTENTOS_CREACION = 1024 * 1024;
void valida_liberacion() {
	for (int i = 0; i < INTENTOS_CREACION; i++) {
		crea_memoria();
	}
	cont++;
}

int main() {
	valida_liberacion();
	int defecto;
	cin >> defecto;
	Memoria<int> m(defecto);
	while (ejecuta_caso(m));
	return 0;
}