/*
Número de grupo: D24

Nombre y apellidos de los autores de la práctica (si alguno de los miembros del grupo
no hay realizado la práctica, no debe incluirse su nombre):
	Abraham Martín Vicente y Jorge López Carrión


*/

using namespace std;

#ifndef _MEMORIA_H_
#define _MEMORIA_H_

/// Excepción de direccion invalida
class EDireccionInvalida {};

/// Excepción de celda sin inicializar
class ECeldaSinInicializar {};

template<class T>
class Memoria {

public:
	/**
	 * crea una memoria con 'capacidad' celdas.
	 */
	Memoria(unsigned int capacidad) {
		_cap = capacidad;
		_elem = new T * [_cap];
		this->inicializa();
	}
	Memoria(const Memoria& m) {
		_cap = m._cap;
		_elem = new T * [_cap];
		for (int i = 0; i < _cap; i++) {
			if (m.inicializada(i)) {
				_elem[i] = new T(m.valor(i));
			}
			else {
				_elem[i] = nullptr;
			}
		}
	}
	~Memoria() {
		if (_elem != nullptr) {
			for (int i = 0; i < _cap; i++) {
				if (this->inicializada(i)) {
					delete _elem[i];
				}
			}
			delete[] _elem;
		}

	}

	/**
	 * Devuelve el valor almacenado en la celda 'd'.
	 * Si 'd' está fuera de rango, levanta EDireccionInvalida.
	 * Si la celda 'd' no está inicializada, levanta ECeldaSinInicializar.
	 */
	const T& valor(unsigned int d) const {
		if (d < _cap) {
			if (this->inicializada(d)) {
				return *_elem[d];
			}
			else {
				throw ECeldaSinInicializar();
			}
		}
		else {
			throw EDireccionInvalida();
		}
	}

	/**
	 * Almacena 'v' en la celda 'd'.
	 * Si 'd' está fuera de rango, levanta EDireccionInvalida.
	 */
	void almacena(unsigned  d, const T& v) {
		if (d < _cap) {
			if (this->inicializada(d)) {
				delete _elem[d];
				_elem[d] = new T(v);
			}
			else {
				_elem[d] = new T(v);
			}
		}
		else {
			throw EDireccionInvalida();
		}
	}

	/**
	 * Devuelve 'true' si la celda 'd' está inicializada.
	 * En otro caso devuelve 'false'.
	 * Si 'd' está fuera de rango, levanta EDireccionInvalida.
	 */
	bool inicializada(unsigned int d) const {
		if (d < _cap) {
			if (_elem[d] != nullptr) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			throw EDireccionInvalida();
		}
	}

	/* Implementar el resto de operaciones y métodos necesarios
	   para que la implementación funcione */
	Memoria& operator =(const Memoria& m) {
		if (this != &m) {
			if (this->_elem != nullptr) {
				for (int i = 0; i < _cap; i++) {
					if (this->inicializada(i)) {
						delete _elem[i];
					}
				}
				delete[] _elem;
			}

			_cap = m._cap;
			_elem = new T * [_cap];
			for (int i = 0; i < _cap; i++) {
				if (m.inicializada(i)) {
					_elem[i] = new T(m.valor(i));
				}
				else {
					_elem[i] = nullptr;
				}
			}
		}

		return *this;
	}
	void inicializa() {
		for (int i = 0; i < _cap; i++) {
			_elem[i] = nullptr;
		}
	}

private:
	/* Declarar los campos necesarios para representar los
	   valores de este TAD, así como las operaciones auxiliares
	   que se consideren oportunas */
	T** _elem;
	int _cap;

};


#endif


