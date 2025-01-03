/*
NOMBRE Y APELLIDOS DE LOS COMPONENTES DEL GRUPO QUE HAN
REALIZADO LA PRÁCTICA:Jorge López Carrión y Abraham Martín Vicente

(si algún componente no ha realizado la práctica,
no debe aparecer)

*/

#include "lista.h"
#include <iostream>
#include <string>
#include "diccionario.h"
#include "DiccionarioHash.h"

using namespace std;


typedef Lista<string> tTexto; // Representación del texto

typedef Lista<int> tFirma;    // Representación de la firma



void construye_firma(const tTexto& texto, tFirma& firma) {
	// A implementar: en 'firma' debe almacenarse la firma de 'texto'
	DiccionarioHash<string, int> dicHash;
	Lista<string>::ConstIterator lcit = texto.cbegin();
	DiccionarioHash<string, int>::Iterator dicHash_it;
	Diccionario<int, string> dic;
	Diccionario<int, string>::Iterator dic_it;
	DiccionarioHash<string, int>::ConstIterator dicHash_cit;
	Diccionario<int, string>::ConstIterator dic_cit;

	if (texto.esVacia()) {
		firma.pon_final(0);
	}
	else {
		while (lcit != texto.cend()) {
			dicHash_it = dicHash.busca(lcit.elem());
			if (dicHash_it != dicHash.end()) {
				dicHash_it.valor()++;
			}
			else {
				dicHash.inserta(lcit.elem(), 1);
			}

			lcit.next();
		}

		dicHash_cit = dicHash.cbegin();

		while (dicHash_cit != dicHash.cend()) {
			dic_it = dic.busca(dicHash_cit.valor());
			if (dic_it == dic.end()) {
				dic.inserta(dicHash_cit.valor(), dicHash_cit.clave());
			}
			dicHash_cit.next();
		}

		dic_cit = dic.cbegin();
		while (dic_cit != dic.cend()) {
			firma.pon_final(dic_cit.clave());
			dic_cit.next();
		}
	}
}

// NO MODIFICAR
bool lee_texto(tTexto& texto) {
	int n;
	cin >> n;
	if (n == -1) return false;
	else {
		for (int i = 0; i < n; i++) {
			string palabra;
			cin >> palabra;
			texto.pon_final(palabra);
		}
		return true;
	}
}

bool ejecuta_caso() {
	tTexto texto;
	if (lee_texto(texto)) {
		tFirma firma;
		construye_firma(texto, firma);
		for (int i = 0; i < firma.longitud(); i++) {
			cout << firma.elem(i) << " ";
		}
		cout << endl;
		return true;
	}
	else {
		return false;
	}
}


int main() {
	while (ejecuta_caso());
}