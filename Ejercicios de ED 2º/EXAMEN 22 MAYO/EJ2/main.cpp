/**
  NOMBRE Y APELLIDOS:
  USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/

#include <iostream>
#include <string>
using namespace std;
#include "Arbin.h"

/*
 COMPLEJIDAD: Determinar justificadamente la complejidad del algoritmo

El algoritmo tiene una complejidad de O(n), donde n es el número de nodos en el árbol de juego. Esto se debe a que cada nodo se visita una vez, y en cada visita se realizan operaciones de tiempo constante.

En la función es_jugable_aux, se realiza una llamada recursiva por cada hijo no vacío del nodo actual. En el peor caso, se recorre todo el árbol, visitando cada nodo una vez.

Por lo tanto, la complejidad del algoritmo es lineal con respecto al número de nodos en el árbol.		 	  
			  
			  
*/

bool es_jugable_aux(const Arbin<int>& juego, int energia, bool& es_ganable, bool& es_perdible) {
	
	if (juego.raiz() == 0) {
		if (energia > 0) {
			es_ganable = true;
			return es_ganable && es_perdible;
		}
		else {
			es_perdible = true;
			return es_ganable && es_perdible;
		}
	}
	else {
		if (energia > 0) {
			if (!juego.hijoDer().esVacio() && !juego.hijoIz().esVacio()) {
				return es_jugable_aux(juego.hijoIz(), energia, es_ganable, es_perdible) ||
					es_jugable_aux(juego.hijoDer(), energia - juego.raiz(), es_ganable, es_perdible);
			}
			else if (!juego.hijoDer().esVacio() ) {
				return es_jugable_aux(juego.hijoDer(), energia - juego.raiz(), es_ganable, es_perdible);
			}
			else {
				return es_jugable_aux(juego.hijoIz(), energia + juego.raiz(), es_ganable, es_perdible);

			}
		}
		else {
			es_perdible = true;
			return es_ganable && es_perdible;
		}
	}
}

bool es_jugable(const Arbin<int>& juego, int energia_inicial) {
	/* A IMPLEMENTAR*/
	
	if (juego.esVacio())
		return true;

	bool es_ganable = false, es_perdible = false;

	return es_jugable_aux(juego, energia_inicial, es_ganable, es_perdible);

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
/*
El formato de la entrada es como sigue:
- Cada línea contiene la descripción del árbol del juego, seguida de la energía inicial. 
- Para describir los árboles se sigue el siguiente convenio:
* Los árboles vacíos se escriben como #
* Los árboles simples se escriben como [c], con c el contenido del nodo.
* Los árboles compuestos se escriben como (IcD), donde:  (i) I es el hijo izquierdo; (ii) c es el contenido de la raíz; (iii) D es el hijo derecho.
El programa imprime SI si el juego es jugable, NO en otro caso.
La entrada termina con una línea que contiene únicamente #.
Ejemplo de entrada / salida:
Entrada:
((#4[0])5([0]4#)) 5
((#4[0])5([0]4#)) 4
((#4[0])5([0]4#)) 6
([0]5[0]) 5
([0]5[0]) 4
([0]5[0]) 6
#
Salida:
SI
NO
NO
SI
SI
NO
*/

bool ejecuta_caso() {
	Arbin<int> a = lee_arbol(cin);
	if (a.esVacio()) return false;
	else {
		int e;
		cin >> e;
		if (es_jugable(a, e)) cout << "SI";
		else cout << "NO";
		cout << endl;
		return true;
	}
}


int main() {
	Arbin<int> arbol;
	while (ejecuta_caso()); 
	return 0;
}