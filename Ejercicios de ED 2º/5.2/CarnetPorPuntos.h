#ifndef _CARNET_POR_PUNTOS_H
#define _CARNET_POR_PUNTOS_H

#include "lista.h"
#include "DiccionarioHash.h"
#include <string>
using namespace std;

class EConductorDuplicado {};
class EConductorNoExiste {};
class EPuntosNoValidos {};

class CarnetPorPuntos {
public:
   void nuevo(const string& dni);
   void quitar(const string& dni, unsigned int puntos);
   void recuperar(const string& dni, unsigned int puntos);
   unsigned int consultar(const string& dni) const;
   unsigned int cuantos_con_puntos(unsigned int puntos) const;
   const Lista<string>& lista_por_puntos(unsigned int puntos) const;
private:
   // A COMPLETAR
	typedef struct info_n_puntos {
		Lista<string> _lista;
	}tInfo;	
	typedef struct info_conductores {
		unsigned int _puntos;
		Lista<string>::Iterator cond_it;
	}tInfo_Cond;
	info_n_puntos _carnet_puntos[16];
	DiccionarioHash<string, info_conductores> _conductores;
};

#endif