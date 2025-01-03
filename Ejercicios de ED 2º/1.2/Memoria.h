/*
NOMBRE Y APELLIDOS DE LOS COMPONENTES DEL GRUPO QUE HAN REALIZADO LA PRÁCTICA:
Jorge López Carrión y Abraham Martín Vicente


(si algún componente no ha realizado la práctica, no debe aparecer)

*/
using namespace std;

#ifndef _MEMORIA_H_
#define _MEMORIA_H_

/// Excepción de direccion invalida
class DireccionInvalida {};


template<class T>
class Memoria {
public:
	/**
	 * crea una memoria
	 * @param defecto valor por defecto de las celdas
	 */
	Memoria(const T& defecto) {
		_tam = TAM_INICIAL;
		_defecto = defecto;
		_elementos = new T[TAM_INICIAL];
		for (int i = 0; i < _tam; i++) {
			_elementos[i] = defecto;
		}
	}
	~Memoria() {
		delete[] _elementos;
	}
	Memoria(const Memoria& m) {
		_tam = m._tam;
		_elementos = new T[_tam];
		for (int i = 0; i < _tam; i++) {
			_elementos[i] = m._elementos[i];
		}
	}
	/**
	 * Devuelve el contenido de una celda
	 * @param d dirección de la celda
	 */
	const T& fetch(int d) const {
		if (d >= 0) {
			if (d < _tam)
				return _elementos[d];
			else
				return _defecto;
		}
		else {
			throw DireccionInvalida();
		}
	}

	/**
	 * Almacena un valor en una celda
	 * @param d dirección de la celda
	 * @param v valor a almacenar
	 */
	void load(int d, const T& v) {
		if (d >= 0) {
			if (d > _tam - 1) {
				T* viejo = _elementos;
				_elementos = new T[d+1];
				for (int i = 0; i < d+1; i++) {
					if(i < _tam)
						_elementos[i] = viejo[i];
					else {
						_elementos[i] = _defecto;
					}
				}
				_tam = d+1;
				delete[] viejo;
			}
			_elementos[d] = v;
		}
		else {
			throw DireccionInvalida();
		}
	}
	
	Memoria& operator=(const Memoria& m) {
		if (this != &m) {
			_tam = m._tam;
			delete[] _elementos;
			_elementos = new T[_tam];
		}
		for (int i = 0; i < _tam; i++) {
			_elementos[i] = m._elementos[i];
		}

		return *this;
	}
	

private:
	static const int TAM_INICIAL = 2;
	int _tam;
	int _defecto;
	T* _elementos;
};
#endif


