/*
NOMBRE Y APELLIDOS:

USUARIO DomJudge ASIGNADO:

*/

#include <iostream>
#include <string>
using namespace std;
#include "Arbin.h"


/*
   DETERMINACION JUSTIFICADA DE LA COMPLEJIDAD:
	  
	  
	  
*/
void num_imparBalanceados_aux(const Arbin<int>& a, int& num_impars, int &nodos_impar_balanceados) {
	if (a.esVacio()) {
		num_impars = 0;
	}
	else {
		int num_impars_izq = 0, num_impars_der = 0;

		if (!a.hijoDer().esVacio() && !a.hijoIz().esVacio()) {
			num_imparBalanceados_aux(a.hijoDer(), num_impars_der, nodos_impar_balanceados);
			num_imparBalanceados_aux(a.hijoIz(), num_impars_izq, nodos_impar_balanceados);
			num_impars += num_impars_der + num_impars_izq;
		}
		else if (!a.hijoDer().esVacio()) {
			num_imparBalanceados_aux(a.hijoDer(), num_impars_der, nodos_impar_balanceados);
			num_impars += num_impars_der;

		}
		else {
			num_imparBalanceados_aux(a.hijoIz(), num_impars_izq, nodos_impar_balanceados);
			num_impars += num_impars_izq;
		}
		
		if (num_impars_der == num_impars_izq) {
			nodos_impar_balanceados++;
		}

		if (a.raiz() % 2 == 1) {
			num_impars++;
		}

		
	}

}


int num_imparBalanceados(const Arbin<int>& a) {
	// A IMPLEMENTAR
	if (a.esVacio()) {
		return 0;
	}
	else {
		int num_impars, nodos_impar_balanceados = 0;
		num_imparBalanceados_aux(a, num_impars, nodos_impar_balanceados);
		return nodos_impar_balanceados;
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