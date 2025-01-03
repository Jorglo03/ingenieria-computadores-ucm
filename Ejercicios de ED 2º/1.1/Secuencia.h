#ifndef _SECUENCIA_H_
#define _SECUENCIA_H_

/// Excepción de elemento inexistente
class ElementoInvalido {};


template<class T>
class Secuencia {
public:
	Secuencia() {
		_tam = TAM_INICIAL;
		_numElem = 0;
		_elementos = new T[TAM_INICIAL];
	}
	~Secuencia() {
		delete[] _elementos;
	}

	Secuencia(const Secuencia& s) {
		_tam = s._tam;
		_numElem = s._numElem;
		_elementos = new T[_tam];
		for (int i = 0; i < _numElem; i++) {
			_elementos[i] = s._elementos[i];
		}
	}
	void pon(const T& e) {
		_elementos[_numElem] = e;
		_numElem++;
		if (_numElem == _tam) {
			T* viejo = _elementos;
			_tam = _tam * 2;
			_elementos = new T[_tam];
			for (int i = 0; i < _numElem; i++) {
				_elementos[i] = viejo[i];
			}
			delete[] viejo;
		}
	}

	const T& elem(int i) {
		if (i < _numElem && i >= 0) {
			return _elementos[i];
		}
		else {
			throw ElementoInvalido();
		}
	}

	int num_elems() const {
		return _numElem;
	}

	Secuencia& operator= (const Secuencia& s) {
		if (_numElem != s._numElem) {
			_tam = s._tam;
			delete[] _elementos;
			_numElem = s._numElem;
			_elementos = new T[_tam];
		}
		for (int i = 0; i < _tam; i++) {
			_elementos[i] = s._elementos[i];
		}
		return *this;
	}


private:
	static const int TAM_INICIAL = 2;
	int _tam;
	int _numElem;
	T* _elementos;
};


#endif


