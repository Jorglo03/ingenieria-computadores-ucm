// NOMBRE Y APELLIDOS:
// USUARIO DEL JUEZ:


#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;


/*
Determinar justificadamente la complejidad del algoritmo:
  --- Determinación justificada de la complejidad
	O(n), donde n es el número de nodos en el árbol binario a, ya que en el peor de los casos
	se recorre una sola vez cada nodo del arbol.
*/

void num_correctivos_aux(const Arbin<int>& a, int& num_correctivos, int& nodos, int& suma_derechos) {

	if (!a.esVacio()) {
		int nodos1 = 0, suma_derechos1 = 0;
		int nodos2 = 0, suma_derechos2 = 0;

		if (!a.hijoDer().esVacio() && !a.hijoIz().esVacio()) {
			
			num_correctivos_aux(a.hijoIz(), num_correctivos, nodos1, suma_derechos1);
			num_correctivos_aux(a.hijoDer(), num_correctivos, nodos2, suma_derechos2);
			if (a.raiz() == suma_derechos2 - nodos1) {
				num_correctivos++;
			}
		}
		else if (!a.hijoDer().esVacio()) {
			num_correctivos_aux(a.hijoDer(), num_correctivos, nodos2, suma_derechos2);
			if (a.raiz() == suma_derechos2) {
				num_correctivos++;
			}
		}
		else {
			num_correctivos_aux(a.hijoIz(), num_correctivos, nodos1, suma_derechos1);
		}

		nodos = nodos1 + nodos2 + 1;
		suma_derechos = suma_derechos1 + suma_derechos2 + a.raiz();

	}

}


int num_correctivos(const Arbin<int>& a) {
	// A IMPLEMENTAR
	if (a.esVacio()) {
		return 0;
	}
	else {
		int num_correctivos = 0, nodos, suma_derechos;
		num_correctivos_aux(a, num_correctivos, nodos, suma_derechos);
		return num_correctivos;
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


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		Arbin<int> a = lee_arbol(cin);
		cout << num_correctivos(a) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}
