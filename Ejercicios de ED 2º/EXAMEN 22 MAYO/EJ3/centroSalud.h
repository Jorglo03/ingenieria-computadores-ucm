/**
  NOMBRE Y APELLIDOS:
  USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/

#ifndef _centroSalud_H
#define _centroSalud_H

#include "lista.h"
#include "DiccionarioHash.h"
#include "diccionario.h"
#include <string>
using namespace std;

// clases para las excepciones
class EMedicoExistente {};  // excepci�n asociada a "annadir_medico"

class EIncorporacionNoAdmitida {}; // excepci�n asociada a "annadir_paciente"

class ECitaNoAdmitida {};  // excepci�n asociada a "citar"

class ECancelacionNoAdmitida {};  // excepci�n asociada a "cancelar_cita"

class EMedicoInexistente {};  // excepci�n asociada a "citados" y "vinculados"



typedef unsigned int tNumColegiado;  // tipo para el n� de colegiado del m�dico
typedef unsigned int tCodigoPaciente;  // tipo para el c�digo de identificaci�n del paciente
typedef unsigned int tNumPacientes; // tipo para el n� m�ximo de pacientes que un m�dico puede atender
typedef string tNombre; // tipo para el nombre del paciente

// clase para la operacion "vinculados"
class Codigo_y_Nombre {
public:
    tCodigoPaciente codigo;
    tNombre nombre;
};


class CentroSalud {
public:
    CentroSalud();
    void annadir_medico(tNumColegiado num_colegiado, tNumPacientes num_pacientes);
    void annadir_paciente(tCodigoPaciente codigo_id, tNombre nombre, tNumColegiado num_colegiado);
    bool citar(tCodigoPaciente codigo_id);
    const Lista<tCodigoPaciente>& citados(tNumColegiado num_colegiado) const;
    bool cancelar_cita(tCodigoPaciente codigo_id);
    Lista<Codigo_y_Nombre> vinculados(tNumColegiado num_colegiado) const;
private:  
    typedef struct {
        tNumPacientes _max_personas_atendidas;
        Lista<tCodigoPaciente> _pacientes_citados;
        Diccionario<tNumPacientes, tNombre> _pacientes_vinculados;
    }tInfoMedico;
    typedef struct {
        tNombre _nombre;
        tNumColegiado _medico;
        Lista<tCodigoPaciente>::Iterator _paciente_citado_it;
        bool _citado;
    }tInfoPaciente;

    DiccionarioHash<tNumColegiado, tInfoMedico> _medicos;
    DiccionarioHash<tNumPacientes, tInfoPaciente> _pacientes;
};

#endif