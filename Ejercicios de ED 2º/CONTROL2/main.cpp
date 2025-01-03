/*
NUMERO DE GRUPO: D24

NOMBRE Y APELLIDOS DE LOS PARTICIPANTES:Jorge López Carrión y Abraham Martín Vicente 

SI ALGUN MIEMBRO DEL GRUPO NO HA PARTICIPADO EN LA PRACTICA,
EXPLICAR EL MOTIVO:

*/

#include "lista.h"
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <string>
using namespace std;


void ornamenta(Lista<int>& l) {
	// A IMPLEMENTAR: Debe modificar 'l' para ornamentarla. 
	// Por tanto, al final de la ejecución, en 'l' debe
	// estar el ornamento de la lista que estaba en este mismo
	// parámetro al inicio de la ejecución.

	l.ordenar();

	Lista<int> impares;
	Lista<int>::ConstIterator cit = l.cbegin();
	Lista<int>::Iterator it = l.begin();
	
	while (cit != l.cend()) {		//Se leen todos lo elementos
		if (cit.elem() % 2 != 0) {
			impares.pon_ppio(cit.elem());		//Los impares se van guardando en otra lista
		}
		else {
			it.set(cit.elem());		//Los pares se van colocando ya en la lista final
			it.next();
		}
		cit.next();
	}
	
	while (it != l.end()) {			//Se terminan colocando los impares en la lista final
		it.set(impares.primero());
		impares.quita_ppio();
		it.next();
	}	
}


/*
A PARTIR DE AQUI CODIGO DE PRUEBA: NO MODIFICAR

*/
void gen_lista_aleatoria(Lista<int>& l, int n) {
	for (int i = 0; i < n; i++) {
		l.pon_final(rand());
	}
}

const int LON_CHEQUEO = 1000000;
void haz_chequeo() {
	int no, n1;
	Lista<int> l;
	gen_lista_aleatoria(l, LON_CHEQUEO);
	l.ordenar();
	gen_lista_aleatoria(l, LON_CHEQUEO);
	ornamenta(l);
	cout << "OK" << endl;
}
void haz_ornamentacion() {
	int num_elems;
	cin >> num_elems;
	Lista<int> l;
	for (int i = 0; i < num_elems; i++) {
		int e;
		cin >> e;
		l.pon_final(e);
	}
	ornamenta(l);
	l.imprime(cout);
	cout << "#";
	l.imprime_invertida(cout);
	cout << endl;
}

bool ejecuta() {
	string comando;
	cin >> comando;
	if (comando == "chequea") {
		haz_chequeo();
		return true;
	}
	else if (comando == "ornamenta") {
		haz_ornamentacion();
		return true;
	}
	return false;
}

int main() {
	srand(time(nullptr));
	while (ejecuta());
	return 0;
}