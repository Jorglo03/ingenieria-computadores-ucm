#include "CarnetPorPuntos.h"


/**
Implementa aquí los métodos de las clases adicionales
*/

 
/**
Debes completar la implementación de las operaciones de CarnetPorPuntos,
y justificar la complejidad de las mismas.
*/ 

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
void CarnetPorPuntos::nuevo(const string& dni) {
	  // A IMPLEMENTAR
	if (_conductores.contiene(dni)) {
		throw EConductorDuplicado();
	}
	else {
		info_conductores info;
		info._puntos = 15;
		_carnet_puntos[15]._lista.pon_ppio(dni);
		info.cond_it = _carnet_puntos[15]._lista.begin();
		_conductores.inserta(dni, info);			
	}
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
void CarnetPorPuntos::quitar(const string& dni, unsigned int puntos) {
	  // A IMPLEMENTAR
	DiccionarioHash<string, info_conductores>::Iterator cond_it = _conductores.busca(dni);
	if (cond_it != _conductores.end()) {		
		unsigned int actuales = cond_it.valor()._puntos;
		if (actuales != 0 && puntos != 0) {
			unsigned int finales;
			if (puntos > actuales) {
				finales = 0;
			}
			else {
				finales = actuales - puntos;
			}
			_carnet_puntos[actuales]._lista.eliminar(cond_it.valor().cond_it);
			cond_it.valor()._puntos = finales;
			_carnet_puntos[finales]._lista.pon_ppio(cond_it.clave());
			cond_it.valor().cond_it = _carnet_puntos[finales]._lista.begin();
		}		
	}
	else {
		throw EConductorNoExiste();
	}
	
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
void CarnetPorPuntos::recuperar(const string& dni, unsigned int puntos) {
	  // A IMPLEMENTAR
	DiccionarioHash<string, info_conductores>::Iterator cond_it = _conductores.busca(dni);
	if (cond_it != _conductores.end()) {
		unsigned int actuales = cond_it.valor()._puntos;
		if (actuales != 15 && puntos != 0) {
			unsigned int finales;
			if (puntos + actuales > 15) {
				finales = 15;
			}
			else {
				finales = actuales + puntos;
			}
			_carnet_puntos[actuales]._lista.eliminar(cond_it.valor().cond_it);
			cond_it.valor()._puntos = finales;
			_carnet_puntos[finales]._lista.pon_ppio(cond_it.clave());
			cond_it.valor().cond_it = _carnet_puntos[finales]._lista.begin();
		}
	}
	else {
		throw EConductorNoExiste();
	}
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
unsigned int CarnetPorPuntos::consultar(const string& dni) const {
	  // A IMPLEMENTAR
	DiccionarioHash<string, info_conductores>::ConstIterator cond_it = _conductores.cbusca(dni);
	if (cond_it != _conductores.cend()) {
		return cond_it.valor()._puntos;
	}
	else {
		throw EConductorNoExiste();
	}
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
unsigned int CarnetPorPuntos::cuantos_con_puntos(unsigned int puntos) const {
	  // A IMPLEMENTAR
	if (puntos < 0 || puntos > 15) {
		throw EPuntosNoValidos();
	}
	else {
		return _carnet_puntos[puntos]._lista.longitud();
	}
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
const Lista<string>& CarnetPorPuntos::lista_por_puntos(unsigned int puntos) const {
	  // A IMPLEMENTAR
	if (puntos < 0 || puntos > 15) {
		throw EPuntosNoValidos();
	}
	else {		
		return  _carnet_puntos[puntos]._lista;
	}
	
}

