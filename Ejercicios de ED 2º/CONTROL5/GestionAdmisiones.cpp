#include "GestionAdmisiones.h"


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 O(1).Porque no requiere inicializacion de ningun atributo.
*/
GestionAdmisiones::GestionAdmisiones() {
	// A IMPLEMENTAR

}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 O(1). Porque la obtención del iterador es constante, la creación del struct es constante y la inserción también es constante.
 La consulta de la función contiene solo requiere un acceso, por lo que también es constante.
*/
void GestionAdmisiones::an_paciente(CodigoPaciente codigo, const string& nombre, unsigned int edad, const string& sintomas) {
	// A IMPLEMENTAR
	if (!_registro.contiene(codigo)) {
		tInfoPaciente info;
		info._edad = edad;
		info._nombre = nombre;
		info._sintomas = sintomas;
		_a_ser_atendidos.pon_ppio(codigo);
		info._paciente_it = _a_ser_atendidos.begin();
		_registro.inserta(codigo, info);
	}
	else {
		throw EPacienteDuplicado();
	}
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 O(1). La busqueda utilizando el iterador del diccionario es constante en promedio y la asigación a las variables también es constante.
*/
void GestionAdmisiones::info_paciente(CodigoPaciente codigo, string& nombre, unsigned int& edad, string& sintomas) const {
	// A IMPLEMENTAR
	DiccionarioHash<CodigoPaciente, tInfoPaciente>::ConstIterator cit = _registro.cbusca(codigo);
	if (cit != _registro.cend()) {
		nombre = cit.valor()._nombre;
		edad = cit.valor()._edad;
		sintomas = cit.valor()._sintomas;
	}
	else {
		throw EPacienteNoExiste();
	}
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 O(1). Porque la función es vacia se hace en tiempo constante, y la asignación a la variable también.
*/
void GestionAdmisiones::siguiente(CodigoPaciente& codigo) const {
  // A IMPLEMENTAR
	if (!_a_ser_atendidos.esVacia()) {
		codigo = _a_ser_atendidos.ultimo();
	}
	else {
		throw ENoHayPacientes();
	}
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 O(1). Porque la propia función "esVacia" es constante ya que se mira el número de elementos de la lista.
*/
bool GestionAdmisiones::hay_pacientes() const {  
  // A IMPLEMENTAR
	return !_a_ser_atendidos.esVacia();
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 O(1). Para reducir el número de accesos utilizamos el iterador, ya que en caso de que esté lo eliminaremos, y si no está no haremos nada.
 Todas las funciones utilizadas aquí son constantes.
*/
void GestionAdmisiones::elimina(CodigoPaciente codigo) {
	// A IMPLEMENTAR
	DiccionarioHash<CodigoPaciente, tInfoPaciente>::Iterator it = _registro.busca(codigo);
	if (it != _registro.end()) {
		_a_ser_atendidos.eliminar(it.valor()._paciente_it);
		_registro.borra(codigo);
	}
}
   
