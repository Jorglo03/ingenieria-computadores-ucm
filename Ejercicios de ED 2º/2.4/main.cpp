/*
NUMERO DE GRUPO: D24

NOMBRE Y APELLIDOS DE LOS PARTICIPANTES: Jorge López Carrión y Abraham Martín Vicente

SI ALGUN MIEMBRO DEL GRUPO NO HA PARTICIPADO EN LA PRACTICA,
EXPLICAR EL MOTIVO:

*/


#include <iostream>
using namespace std;
#include <string>

#include "lista.h"
#include "pila.h"
// Incluir otros TADs que se consideren necesarios,
// asi como el resto de definiciones auxiliares que
// se considere oportuno.

 bool esVocal(Lista<char>::ConstIterator it) {
	return (it.elem() == 'a' || it.elem() == 'A' || it.elem() == 'e' || it.elem() == 'E'
		|| it.elem() == 'i' || it.elem() == 'I' || it.elem() == 'o' || it.elem() == 'O'
		|| it.elem() == 'u' || it.elem() == 'U');
}

void invierteSecuenciasNoVocales(Lista<char> &mensaje) {
	// A IMPLEMENTAR
	Pila<char> pila;
	Lista<char>::ConstIterator cit = mensaje.cbegin();		//Para recorrer la lista solo leyendo las letras
	Lista<char>::Iterator it = mensaje.begin();				//Para recorrer la lista escribiendo en la lista

	if(!mensaje.esVacia()){
		while (cit != mensaje.cend()) {
			if (esVocal(cit)) {								//Si es vocal
				while (!pila.esVacia()) {					//Mientras haya elementos en la pila
					it.set(pila.cima());					//Se insertan las consonantes en la lista
					pila.desapila();						//Se van eliminando de la pila
					it.next();
				}
				cit.next();									
				it.next();
			}
			else {											//Si NO es vocal
				pila.apila(cit.elem());						//Se apila la consonante en la pila para luego escribirlas 
				cit.next();
				if (cit == mensaje.cend()) {				//Si es el ultimo caso, se tienen que insertar las consonantes que lleve desde la ultima vocal
					while (!pila.esVacia()) {				//Mientras haya elementos en la pila
						it.set(pila.cima());				//Se insertan las consonantes en la lista
						pila.desapila();					//Se van eliminando de la pila
						it.next();
					}
				}
			}
		}	
	}
}



// CODIGO ADICIONAL: NO MODIFICAR
 
  // Imprime la lista por la salida estandar,
  // tanto leída desde el principio hasta el final
  // como leída desde el final hasta el principio.
void imprime(Lista<char>& l) {
	l.imprime(cout);
	cout << "#";
	l.imprime_invertida(cout);
	cout << endl;
}


// Codifica el mensaje
void codifica(Lista<char>& mensaje) {
	invierteSecuenciasNoVocales(mensaje);
	mensaje.enredar();
}

  // Transforma la linea en una lista de caracteres
void construyeMensaje(const string& linea, Lista<char>& mensaje) {
	for(unsigned int i=0; i < linea.size(); i++)
		mensaje.pon_final(linea[i]);  
}

int main() {
	string linea;
	while(getline(cin,linea)) {
	   Lista<char> mensaje;
	   construyeMensaje(linea,mensaje);
       codifica(mensaje);
	   imprime(mensaje);
	}
	return 0;
}	
