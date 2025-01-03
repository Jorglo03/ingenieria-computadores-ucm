/*
NUMERO DE GRUPO: D24

NOMBRE Y APELLIDOS DE LOS PARTICIPANTES: Abraham Martín Vicente y Jorge López Carrión

SI ALGUN MIEMBRO DEL GRUPO NO HA PARTICIPADO EN LA PRACTICA, EXPLICAR EL MOTIVO:

*/


#include "Arbin.h"
#include <iostream>
#include <string>
using namespace std;



/* Puedes implementar aquí las funciones auxiliares que consideres
   oportuno */

/*
COMPLEJIDAD: Determina justificadamente la complejidad del procedimiento 

	O(n). Ya que en el peor caso, cada nodo se recorre una sola vez hasta llegar a las hojas.
	Si en algún nodo no hoja detectamos que no es rentable, no continua por esa rama.

*/

void mejor_renta_aux(const Arbin<int>& a, bool& es_rentable, int& renta_maxima, int renta_actual) {
	if (a.hijoIz().esVacio() && a.hijoDer().esVacio()) {	//CASO BASE
		renta_actual += a.raiz();
		if (renta_actual > 0) {
			if (renta_maxima < renta_actual) {
				renta_maxima = renta_actual;
			}
			es_rentable = true;
		}
	}
	else {													//CASO RECURSIVO
		renta_actual += a.raiz();
		if (renta_actual > 0) {
			if (!a.hijoIz().esVacio())
				mejor_renta_aux(a.hijoIz(), es_rentable, renta_maxima, renta_actual);
			if (!a.hijoDer().esVacio())
				mejor_renta_aux(a.hijoDer(), es_rentable, renta_maxima, renta_actual);
		}
	}
}


void mejor_renta(Arbin<int> a, bool& es_rentable, int& renta_maxima) {
	es_rentable = false;
	renta_maxima = 0;
	if(!a.esVacio())
		mejor_renta_aux(a, es_rentable, renta_maxima, 0);
	
}

/* Codigo de prueba: no modificar */

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

void muestra_solucion(bool rentable, int renta_max) {
  if (rentable) {
	 cout << renta_max << endl; 
  }	
  else {
	 cout << "NO_RENTABLE " << endl; 
  }
}

int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		Arbin<int> a = lee_arbol(cin);
		bool es_rentable;
		int renta_maxima;
		mejor_renta(a,es_rentable,renta_maxima);
		muestra_solucion(es_rentable,renta_maxima);
		string resto_linea;
		getline(cin, resto_linea);
	}
    return 0;       
}