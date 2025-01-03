// NO MODIFIQUES NADA DE LO QUE APARECE EN ESTE FICHERO

#include <iostream>
#include <string>
using namespace std;
#include "ColeccionPeliculas.h"


void an_categoria(ColeccionPeliculas& col) {
	string c;
	cin >> c;
	try {
		col.an_categoria(c);
		cout << "OK" << endl;
	}
	catch (ECategoriaDuplicada) {
		cout << "CATEGORIA DUPLICADA" << endl;
	}
}

void an_pelicula(ColeccionPeliculas& col) {
	string c, p;
	cin >> c >> p;
	try {
		col.an_pelicula(c,p);
		cout << "OK" << endl;

	}
	catch (ECategoriaNoExiste) {
		cout << "CATEGORIA NO EXISTE" << endl;
	}
	catch (EPeliculaDuplicada) {
		cout << "PELICULA DUPLICADA" << endl;
	}
}

void lista_por_nombre(const ColeccionPeliculas& col) {
	string c;
	cin >> c;
	try {
		Lista<tPelicula> peliculas = col.lista_por_nombre(c);
		for (int i = 0; i < peliculas.longitud(); i++) {
			cout << "[" << peliculas.elem(i) << "]";
		}
		cout << endl;
	}
	catch (ECategoriaNoExiste) {
		cout << "CATEGORIA NO EXISTE" << endl;
	}
}

void lista_cronologicamente(const ColeccionPeliculas& col) {
	string c;
	cin >> c;
	try {
		Lista<tPelicula> peliculas = col.lista_cronologicamente(c);
		for (int i = 0; i < peliculas.longitud(); i++) {
			cout << "[" << peliculas.elem(i) << "]";
		}
		cout << endl;
	}
	catch (ECategoriaNoExiste) {
		cout << "CATEGORIA NO EXISTE" << endl;
	}
}

void elimina_pelicula(ColeccionPeliculas& col) {
	string c;
	cin >> c;
	col.elimina_pelicula(c);
	cout << "OK" << endl;
}


int main() {
	ColeccionPeliculas col;
	string comando;

	while (cin >> comando) {
		if (comando == "an_categoria") an_categoria(col);
		else if (comando == "an_pelicula") an_pelicula(col);
		else if (comando == "lista_por_nombre") lista_por_nombre(col);
		else if (comando == "lista_cronologicamente") lista_cronologicamente(col);
		else if (comando == "elimina_pelicula") elimina_pelicula(col);

	}
	return 0;
}


