
#include "ParqueDeAtracciones.h"

/*
COMPLEJIDAD: Determina justificadamente la complejidad de la operaci?n.

*/

ParqueDeAtracciones::ParqueDeAtracciones() {
	  // A IMPLEMENTAR	
}

/*
COMPLEJIDAD: Determina justificadamente la complejidad de la operaci?n.

*/
void ParqueDeAtracciones::an_atraccion(const string& nombre_atraccion) {
	  // A IMPLEMENTAR
	if (_atracciones.contiene(nombre_atraccion)) {
		throw EAtraccionYaExiste();
	}
	else {
		Lista<string> _en_cola;
		_atracciones.inserta(nombre_atraccion, _en_cola);
	}
}

/*
COMPLEJIDAD: Determina justificadamente la complejidad de la operaci?n.

*/
void ParqueDeAtracciones::an_ninio(const string& nombre_ninio) {
	  // A IMPLEMENTAR
	if (_ninios_en_parque.contiene(nombre_ninio)) {
		throw ENinioYaRegistrado();
	}
	else {
		tInfoNinio _info;
		_ninios_en_parque.inserta(nombre_ninio, _info);
	}
}

/*
COMPLEJIDAD: Determina justificadamente la complejidad de la operaci?n.

*/
void ParqueDeAtracciones::poner_en_fila(const string& nombre_ninio, const string& nombre_atraccion) {
	  // A IMPLEMENTAR
	DiccionarioHash<string, Lista<string>>::Iterator atr_it = _atracciones.busca(nombre_atraccion);
	DiccionarioHash<string, tInfoNinio>::Iterator ninio_it = _ninios_en_parque.busca(nombre_ninio);
	if (atr_it != _atracciones.end() && ninio_it != _ninios_en_parque.end()
		&& ninio_it.valor()._f_actual =="") {
		atr_it.valor().pon_final(nombre_ninio);
		ninio_it.valor()._f_actual = nombre_atraccion;
	}
	else {
		throw EAccesoAtraccion();
	}
}	

/*
COMPLEJIDAD: Determina justificadamente la complejidad de la operaci?n.

*/
void ParqueDeAtracciones::avanzar(const string& nombre_atraccion) {
	  // A IMPLEMENTAR
	DiccionarioHash<string, Lista<string>>::Iterator atr_it = _atracciones.busca(nombre_atraccion);
	if (atr_it != _atracciones.end()) {
		if (!atr_it.valor().esVacia()) {
			DiccionarioHash<string, tInfoNinio>::Iterator ninio_it;
			ninio_it = _ninios_en_parque.busca(atr_it.valor().primero());			
			ninio_it.valor()._f_actual = "";
			DiccionarioHash<string, int>::Iterator it = ninio_it.valor()._visitadas.busca(nombre_atraccion);
			if (it != ninio_it.valor()._visitadas.end()) {
				it.valor()++;
			}
			else {
				ninio_it.valor()._visitadas.inserta(nombre_atraccion, 1);
				ninio_it.valor()._ordenadas.inserta(nombre_atraccion, 0);
			}
			atr_it.valor().quita_ppio();
		}
	}
	else {
		throw EAtraccionNoExiste();
	}
}

/*
COMPLEJIDAD: Determina justificadamente la complejidad de la operaci?n.

*/
Lista<string> ParqueDeAtracciones::atracciones_visitadas(const string& nombre_ninio) const {
	   // A IMPLEMENTAR
	DiccionarioHash<string, tInfoNinio>::ConstIterator ninio_cit = _ninios_en_parque.cbusca(nombre_ninio);
	
	if (ninio_cit != _ninios_en_parque.cend()) {
		Lista<string> lista;		
		Diccionario<string, int>::ConstIterator ord_cit = ninio_cit.valor()._ordenadas.cbegin();
		while (ord_cit != ninio_cit.valor()._ordenadas.cend()) {
			lista.pon_final(ord_cit.clave());
			ord_cit.next();
		}
		return lista;
	}
	else {
		throw ENinioNoRegistrado();
	}
}
  
/*
COMPLEJIDAD: Determina justificadamente la complejidad de la operaci?n.

*/  
int ParqueDeAtracciones::numero_visitas(const string& nombre_ninio, const string& nombre_atraccion) const {
	    // A IMPLEMENTAR
	DiccionarioHash<string, Lista<string>>::ConstIterator atr_cit = _atracciones.cbusca(nombre_atraccion);
	DiccionarioHash<string, tInfoNinio>::ConstIterator ninio_cit = _ninios_en_parque.cbusca(nombre_ninio);
	if (ninio_cit != _ninios_en_parque.cend() 
		&& atr_cit != _atracciones.cend()) {
		DiccionarioHash<string, int>::ConstIterator info_cit = ninio_cit.valor()._visitadas.cbusca(nombre_atraccion);
		if (info_cit != ninio_cit.valor()._visitadas.cend()) {
			return info_cit.valor();
		}
		else {
			return 0;
		}
	}
	else {
		throw EConsultaNumViajes();
	}
}
   
 