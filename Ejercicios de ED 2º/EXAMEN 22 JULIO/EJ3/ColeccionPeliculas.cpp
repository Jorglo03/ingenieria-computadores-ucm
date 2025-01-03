// NOMBRE Y APELLIDOS:
// USUARIO DEL JUEZ:

#include "ColeccionPeliculas.h"

#include <iostream>
using namespace std;

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
ColeccionPeliculas::ColeccionPeliculas() {
	// A IMPLEMENTAR
};

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
void ColeccionPeliculas::an_categoria(const tCategoria& c) {
	// A IMPLEMENTAR
	if (_categorias.contiene(c)) {
		throw ECategoriaDuplicada();
	}
	else {
		tInfoCategoria infoCategoria;
		Diccionario<tPelicula, tCategoria> orden_peliculas;
		Lista<tPelicula> peliculas_de_la_categ;
		Lista<tPelicula>::Iterator it_pelicula;
		DiccionarioHash<tPelicula, tCategoria> peliculas;

		infoCategoria._peliculas_de_la_categ = peliculas_de_la_categ;
		infoCategoria._orden_peliculas = orden_peliculas;
		infoCategoria._it_pelicula = it_pelicula;
		infoCategoria._peliculas = peliculas;

		_categorias.inserta(c, infoCategoria);
	}
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
void ColeccionPeliculas::an_pelicula(const tCategoria& c, const tPelicula& p) {
	// A IMPLEMENTAR
	DiccionarioHash<tCategoria, tInfoCategoria>::Iterator it_categorias = _categorias.busca(c);
	if (it_categorias != _categorias.end()) {
		DiccionarioHash<tPelicula, tCategoria>::ConstIterator cit_peliculas = it_categorias.valor()._peliculas.cbusca(p);
		if (cit_peliculas != it_categorias.valor()._peliculas.cend()) {
			throw EPeliculaDuplicada();
		}
		else {
			it_categorias.valor()._peliculas.inserta(p, c);
			it_categorias.valor()._orden_peliculas.inserta(p, c);
			it_categorias.valor()._peliculas_de_la_categ.pon_ppio(p);
			it_categorias.valor()._it_pelicula = it_categorias.valor()._peliculas_de_la_categ.begin();
			DiccionarioHash<tPelicula, tInfoPelicula>::Iterator it_pelis = _dic_peliculas.busca(p);
			if (it_pelis != _dic_peliculas.end()) {
				it_pelis.valor().inserta(c, true);
			}
			else {
				DiccionarioHash<tCategoria, bool> cats;
				cats.inserta(c, true);
				_dic_peliculas.inserta(p, cats);
			}
		}
		
	}
	else {
		throw ECategoriaNoExiste();
	}
}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
Lista<tPelicula> ColeccionPeliculas::lista_por_nombre(const tCategoria& c) const {
	// A IMPLEMENTAR
	Lista<tPelicula> lista_peliculas;
	DiccionarioHash<tCategoria, tInfoCategoria>::ConstIterator cit_categorias = _categorias.cbusca(c);
	if (cit_categorias != _categorias.cend()) {
		Diccionario<tPelicula, tCategoria>::ConstIterator cit_peliculas = cit_categorias.valor()._orden_peliculas.cbegin();
		while (cit_peliculas != cit_categorias.valor()._orden_peliculas.cend()) {
			lista_peliculas.pon_final(cit_peliculas.clave());
			cit_peliculas.next();
		}
		return lista_peliculas;
	}
	else {
		throw ECategoriaNoExiste();
	}
}
	
/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
Lista<tPelicula> ColeccionPeliculas::lista_cronologicamente(const tCategoria& c) const {
	// A IMPLEMENTAR
	Lista<tPelicula> lista_peliculas;
	DiccionarioHash<tCategoria, tInfoCategoria>::ConstIterator cit_categorias = _categorias.cbusca(c);
	if (cit_categorias != _categorias.cend()) {
		Lista<tPelicula>::ConstIterator cit_peliculas = cit_categorias.valor()._peliculas_de_la_categ.cbegin();
		while (cit_peliculas != cit_categorias.valor()._peliculas_de_la_categ.cend()) {
			lista_peliculas.pon_final(cit_peliculas.elem());
			cit_peliculas.next();
		}
		return lista_peliculas;
	}
	else {
		throw ECategoriaNoExiste();
	}
}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
void ColeccionPeliculas::elimina_pelicula(const tPelicula& p) {
	// A IMPLEMENTAR
	DiccionarioHash<tPelicula, tInfoPelicula>::ConstIterator cit_pelicula = _dic_peliculas.cbusca(p);
	if (cit_pelicula != _dic_peliculas.cend()) {
		DiccionarioHash<tCategoria, bool>::ConstIterator it_cats_peli = cit_pelicula.valor().cbegin();
		while (it_cats_peli != cit_pelicula.valor().cend()) {
			DiccionarioHash<tCategoria, tInfoCategoria>::Iterator it_cat = _categorias.busca(it_cats_peli.clave());
			it_cat.valor()._orden_peliculas.borra(p);
			it_cat.valor()._peliculas.borra(p);
			it_cat.valor()._peliculas_de_la_categ.eliminar(it_cat.valor()._it_pelicula);
			it_cats_peli.next();
		}
		_dic_peliculas.borra(p);
	}

}

