/**
  NOMBRE Y APELLIDOS:
  USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/
#ifndef _paqueteria_H
#define _paqueteria_H

#include "lista.h"  
#include "DiccionarioHash.h"
#include <string>
using namespace std;

// clases para las excepciones
class EPaqueteDuplicado {};

class EPaqueteInexistente {};

class ENingunPaqueteEnEspera {};

class ENingunCamionEnEspera {};

class EErrorCarga {};

// tipo identificador paquete
typedef unsigned int IdPaquete;  



class Paqueteria {
public:
   Paqueteria();
   void recepciona_paquete(IdPaquete id, string dir, float peso);
   void info_paquete(IdPaquete id, string& dir, float& peso) const;
   void primero_en_fila(IdPaquete& id) const;
   void nuevo_camion(float peso);
   void primer_camion(float& peso) const;
   void elimina(IdPaquete id);
   bool hay_paquetes() const;
   Lista<IdPaquete> carga_camion();
private:
   
	

	typedef struct {
		string _dir;
		float _peso;
	}tInfoPaquete;

	typedef Lista<IdPaquete>::Iterator it_paquetes;

	Lista<float> _camiones;
	DiccionarioHash<IdPaquete, it_paquetes> _dic_iterator;
	Lista<IdPaquete> _lista_paquetes;
	DiccionarioHash<IdPaquete, tInfoPaquete> _paquetes;

};

#endif