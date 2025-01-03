#include "lista.h"
#include "DiccionarioHash.h"
#include <iostream>
#include <string>
using namespace std;


typedef struct {
	int x;
	double val;
} tEntrada;

typedef Lista<tEntrada> tVector;


double producto_escalar(const tVector& u, const tVector& v) {
	// A IMPLEMENTAR
	DiccionarioHash<int, double> dic;
	tVector::ConstIterator vect_it = u.cbegin();
	DiccionarioHash<int, double>::Iterator dic_it;
	while (vect_it != u.cend()) {
		dic_it = dic.busca(vect_it.elem().x);
		if (dic_it != dic.end()) {
			dic_it.valor()*= vect_it.elem().val;
		}
		else {			
			dic.inserta(vect_it.elem().x, vect_it.elem().val);
		}
		vect_it.next();		
	}
	vect_it = v.cbegin();	
	double result = 0;
	while (vect_it != v.cend()) {
		dic_it = dic.busca(vect_it.elem().x);
		if (dic_it != dic.end()) {
			double temp = vect_it.elem().val * dic_it.valor();			
			result += temp;
		}
		vect_it.next();
	}
	return result;
}

bool leeVector(tVector& v) {
	if (cin.peek() == '(') {
		char sep;
		cin >> sep;
		while (cin.peek() != ')') {
			tEntrada e;
			unsigned int i;
			double val;
			cin >> e.x >> sep >> e.val;
			if (cin.peek() != ')') {
				cin >> sep;
			}
			v.pon_final(e);
		}
		cin >> sep;
		return true;
	}
	else return false;
}
void saltaLinea() {
	string s;
	getline(cin, s);
}

int main() {
	bool fin = false;
	while (!fin) {
		tVector u;
		tVector v;
		if (leeVector(u)) {
			leeVector(v);
			saltaLinea();
			cout << producto_escalar(u, v) << endl;
		}
		else {
			fin = true;
		}
	}
}