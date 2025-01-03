#include "Memoria.h"
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <string>
using namespace std;


class Par {
public:
	Par(int x, int y) : _x(x), _y(y) {}
	int val_1() const { return _x;}
	int val_2() const { return _y; }
private:
	int _x;
	int _y;
};


const static int MAX_TAM=100;
Memoria<Par> random_men() {
	unsigned int tam = unsigned(rand() % MAX_TAM);
	Memoria<Par> mem(tam);
	for (unsigned int i = 0; i < tam; i++) {
		if (rand() % 2 == 0) {
			mem.almacena(i, Par(rand(), rand()));
		}
	}
	return mem;
}

int cont=0;
Memoria<Par> valida_copias(Memoria<Par> m) {
	Memoria<Par> m2 = random_men();
	m2 = m;
	m2 = m2;
	cont++;
	return m2;
}

bool ejecuta_caso(Memoria<Par>& m) {
	m = valida_copias(m);
	string comando;
	cin >> comando;
	if (comando == "almacena") {
		int d,x,y;
		cin >> d >> x >> y;
		try {
			m.almacena(d, Par(x,y));
			cout << "OK" << endl;
		}
		catch (EDireccionInvalida) {
			cout << "DIRECCION_INVALIDA" << endl;
		}
		return true;
	}
	else if (comando == "valor") {
		int d;
		cin >> d;
		try {
			Par v = m.valor(d);
			cout << v.val_1() << " " << v.val_2() << endl;
		}
		catch (EDireccionInvalida) {
			cout << "ERROR_DE_LECTURA" << endl;
		}
		catch (ECeldaSinInicializar) {
			cout << "ERROR_DE_LECTURA" << endl;
		}
		return true;
	}
	else if (comando == "inicializada") {
		int d;
		cin >> d;
		try {
			if (m.inicializada(d)) {
				cout << "SI" << endl;
			}
			else {
				cout << "NO" << endl;
			}
		}
		catch (EDireccionInvalida) {
			cout << "DIRECCION_INVALIDA" << endl;
	    }
		return true;
	}
	else if (comando == "termina") {
		return false;
	}
	return false;
}


const static int TAM_MEM_PRUEBA = 1024;
void crea_memoria() {
	Memoria<int> m(TAM_MEM_PRUEBA);
	for(int i=0; i < TAM_MEM_PRUEBA; i++) {
		m.almacena(i,5);
	}	
	Memoria<int> m2(TAM_MEM_PRUEBA);
	for(int i=0; i < TAM_MEM_PRUEBA; i++) {
		m2.almacena(i,5);
	}	
	Memoria<int> m3(1);
	m2 = m3;
}

const static int INTENTOS_CREACION = 1000;
void valida_liberacion() {
	for (int i = 0; i < INTENTOS_CREACION; i++) {
		crea_memoria();
	}
	cont++;
}

int main() {
	valida_liberacion();
	int capacidad;
	cin >> capacidad;
	Memoria<Par> m(capacidad);
	while (ejecuta_caso(m));
	return 0;
}