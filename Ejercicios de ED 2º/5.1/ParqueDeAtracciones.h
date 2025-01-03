#ifndef _PARQUE_ATRACCIONES_H
#define _PARQUE_ATRACCIONES_H
#include <string>
#include "lista.h"
#include "diccionario.h"
#include "DiccionarioHash.h"
// Realizar los 'include' adicionales
// que se estimen oportunos.

using namespace std;

class EAtraccionYaExiste {};

class ENinioYaRegistrado {};

class EAtraccionNoExiste {};

class ENinioNoRegistrado {};

class EAccesoAtraccion {};

class EConsultaNumViajes {};


class ParqueDeAtracciones {
public:
   ParqueDeAtracciones();
   void an_atraccion(const string& nombre_atraccion);
   void an_ninio(const string& nombre_ninio);
   void poner_en_fila(const string& nombre_ninio, const string& nombre_atraccion);
   void avanzar(const string& nombre_atraccion);
   Lista<string> atracciones_visitadas(const string& nombre_ninio) const;
   int numero_visitas(const string& nombre_ninio,const string& nombre_atraccion) const;
private:
   // Definir la representación que se estime oportuna, así como declarar los métodos
   // auxiliares que se consideren oportunos (si se estima necesario). 
	typedef struct _info{
		string _f_actual = "";
		DiccionarioHash<string, int> _visitadas;
		Diccionario<string, int> _ordenadas;
	} tInfoNinio;
	DiccionarioHash<string, Lista<string>> _atracciones;
	
	DiccionarioHash<string, _info> _ninios_en_parque;  
};

#endif