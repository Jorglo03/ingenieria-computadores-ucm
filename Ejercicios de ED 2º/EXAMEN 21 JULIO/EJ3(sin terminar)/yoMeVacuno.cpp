/*
NOMBRE Y APELLIDOS:

USUARIO DomJudge ASIGNADO:

*/

#include "yoMeVacuno.h"


/*
 DETERMINACION DE LA COMPLEJIDAD
 
*/
YoMeVacuno::YoMeVacuno(tAnio anio, tNumVacunas n) {
	 // A IMPLEMENTAR
	_infoVacunas._anio = anio;
	_infoVacunas._n = n;
}

/*
 DETERMINACION DE LA COMPLEJIDAD
 
*/
void YoMeVacuno::fija_Anio_NumVacunas(tAnio anio, tNumVacunas n) {
	 // A IMPLEMENTAR 
	_infoVacunas._anio = anio;
	_infoVacunas._n += n;
}

/*
 DETERMINACION DE LA COMPLEJIDAD
 
*/
void YoMeVacuno::registra_centro(tIdCentro id, tDireccion dir) {
 // A IMPLEMENTAR 
	if (_centros.contiene(id)) {
		throw ECentroDuplicado();
	}
	else {
		Lista<tIdCiudadano> lista;
		tInfoCentro infoCentro;
		infoCentro._dir = dir;
		infoCentro._lista_ciudadanos = lista;
		_centros.inserta(id, infoCentro);
		_centros_ordenados.inserta(id, dir);
	}
}

/*
 DETERMINACION DE LA COMPLEJIDAD
 
*/
void YoMeVacuno::registra_ciudadano(tIdCiudadano id, tAnio anio) {
 // A IMPLEMENTAR 
	if (_ciudadanos.contiene(id)) {
		throw ECiudadanoDuplicado();
	}
	else {
		tInfoCiudadano infoCiudadano;
		infoCiudadano._anio = anio;
		infoCiudadano._cita = false;
		_ciudadanos.inserta(id, infoCiudadano);
	}
}

/*
 DETERMINACION DE LA COMPLEJIDAD
 
*/
void YoMeVacuno::pide_cita(tIdCiudadano id) {
	// A IMPLEMENTAR
	DiccionarioHash<tIdCiudadano, tInfoCiudadano>::ConstIterator cit_ciudadano = _ciudadanos.cbusca(id);
	if (cit_ciudadano != _ciudadanos.cend()) {
		if (cit_ciudadano.valor()._anio != _infoVacunas._anio) {
			throw EAnioErroneo();
		}
		else {
			if (cit_ciudadano.valor()._cita) {
				throw EExisteCita();
			}
			else {
				_lista_total.pon_final(id);
			}
		}
	}
	else {
		throw ECiudadanoInexistente();
	}
}

/*
 DETERMINACION DE LA COMPLEJIDAD
 
*/
bool YoMeVacuno::en_espera() {
	// A IMPLEMENTAR
	return !_lista_total.esVacia();
}

/*
 DETERMINACION DE LA COMPLEJIDAD
 
*/
Lista<Asignacion> YoMeVacuno::atiende_solicitudes() {
	// A IMPLEMENTAR
	Lista<Asignacion> lista;
	if (_centros.esVacio()) {
		throw EErrorDeAtencion();
	}
	else {
		Diccionario<tIdCentro, tDireccion>::ConstIterator cit_centros = _centros_ordenados.cbegin();
		Lista<tIdCiudadano>::Iterator it_ciudadanos = _lista_total.begin();
		Asignacion asignacion;
		while (it_ciudadanos != _lista_total.end() && _infoVacunas._n!= 0) {

			DiccionarioHash <tIdCentro, tInfoCentro>::Iterator it_centros = _centros.busca(cit_centros.clave());
			it_centros.valor()._lista_ciudadanos.pon_final(cit_centros.clave());

			
			asignacion.ponCentro(cit_centros.clave());
			asignacion.ponCiudadano(it_ciudadanos.elem());
			asignacion.ponDireccion(cit_centros.valor());

			lista.pon_final(asignacion);
			
			cit_centros.next();
			if (cit_centros== _centros_ordenados.cend()) {
				cit_centros = _centros_ordenados.cbegin();
			}
			it_ciudadanos.next();
			_lista_total.quita_ppio();
			_infoVacunas._n--;
		}

		return lista;

	}
}

/*
 DETERMINACION DE LA COMPLEJIDAD
 
*/
bool YoMeVacuno::administra_vacuna(tIdCentro idCentro) {
// A IMPLEMENTAR
	







}
