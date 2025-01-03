/*
NOMBRE Y APELLIDOS DE LOS COMPONENTES DEL GRUPO QUE HAN REALIZADO LA PRÁCTICA:
Jorge López Carrión y Abraham Martín Vicente

(si algún componente no ha realizado la práctica,
no debe aparecer)

*/


#ifndef _GESTION_ADMISIONES_H
#define _GESTION_ADMISIONES_H

#include <string>
#include "lista.h"
#include "DiccionarioHash.h"
using namespace std;

/** 
Tipo que representa el código de los
pacientes
*/
typedef unsigned int CodigoPaciente;


/**
Excepción que debe levantarse cuando trata de darse de alta
un paciente con un código duplicado
*/
class EPacienteDuplicado {};

/**
Excepción que debe levantarse cuando trata de consultarse los
datos de un paciente a través de un código que no existe.
*/
class EPacienteNoExiste {};

/**
Excepción que debe levantarse cuando trata de consultarse la información
del siguiente paciente a atender, pero no hay pacientes en el sistema.
*/
class ENoHayPacientes {};

/**
Clase que implementa el TAD
*/
class GestionAdmisiones {
public:
   /**
     Constructora: crea un sistema de gestión de admisiones vacío
   */
   GestionAdmisiones();
   /**
     Añade un paciente al sistema. 
	 Levanta la excepción EPacienteDuplicado si ya hay un paciente esperando con el
	 mismo codigo
	 @param codigo El código del paciente
	 @param nombre El nombre del paciente
	 @param edad La edad del paciente
	 @param sintomas Los sintomas del paciente
   */
   void an_paciente(CodigoPaciente codigo, const string& nombre, unsigned int edad, const string& sintomas);
   /**
     Recupera los datos de un paciente, dado su código. 
	 Levanta la excepción EPacienteNoExiste si el código no se corresponde con el
	 de ningún paciente en espera
	 @param codigo El código del paciente
	 @param nombre El nombre del paciente
	 @param edad La edad del paciente
	 @param sintomas Los sintomas del paciente
   */   
   void info_paciente(CodigoPaciente codigo, string& nombre, unsigned int& edad, string& sintomas) const;
   /**
     Recupera el código del siguiente paciente que va a ser atendido.
	 Levanta la excepción ENoHayPacientes en caso de que no haya pacientes en espera.
	 @param codigo El código del paciente
   */   
   void siguiente(CodigoPaciente& codigo) const;
    /**
     Determina si hay pacientes en espera
	 @return true si hay pacientes, false en otro caso.
   */   
   bool hay_pacientes() const;
   /**
     Elimina del sistema todo el rasto de un paciente, dado su código.
	 Si el código no existe, la operación no tiene efecto.
	 @param codigo El codigo del paciente a eliminar. 
   */   
   void elimina(CodigoPaciente codigo);
private:
  // Debe elegirse la representación más adecuada para implementar
  // eficientemente este TAD

	typedef struct {
		string _nombre;
		unsigned int _edad;
		string _sintomas;
		Lista<CodigoPaciente>::Iterator _paciente_it;
	}tInfoPaciente;

	Lista<CodigoPaciente> _a_ser_atendidos;
	DiccionarioHash<CodigoPaciente, tInfoPaciente> _registro;
};

#endif