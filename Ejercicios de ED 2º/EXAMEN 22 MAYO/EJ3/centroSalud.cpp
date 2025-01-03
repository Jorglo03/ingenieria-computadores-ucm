/**
  NOMBRE Y APELLIDOS:
  USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/

#include "centroSalud.h"

#include <iostream>
using namespace std;


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
CentroSalud::CentroSalud() {
	// A IMPLEMENTAR

}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
void CentroSalud::annadir_medico(tNumColegiado num_colegiado, tNumPacientes num_pacientes) {
	// A IMPLEMENTAR
    if (_medicos.contiene(num_colegiado)) {
        throw EMedicoExistente();
    }
    else {
        tInfoMedico infoMedico;
        Lista<tCodigoPaciente> _pacientes_citados;
        Diccionario<tNumPacientes, tNombre> _pacientes_vinculados;
        infoMedico._pacientes_citados = _pacientes_citados;
        infoMedico._pacientes_vinculados = _pacientes_vinculados;
        infoMedico._max_personas_atendidas = num_pacientes;
        _medicos.inserta(num_colegiado, infoMedico);
    }
}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
void CentroSalud::annadir_paciente(tCodigoPaciente codigo_id, tNombre nombre, tNumColegiado num_colegiado) {
	 // A IMPLEMENTAR
    DiccionarioHash<tNumColegiado, tInfoMedico>::Iterator it_medicos = _medicos.busca(num_colegiado);
    if (_pacientes.contiene(codigo_id) || it_medicos == _medicos.end()) {
        throw EIncorporacionNoAdmitida();
    }
    else {
        tInfoPaciente infoPaciente;
        infoPaciente._nombre = nombre;
        infoPaciente._medico = num_colegiado;
        it_medicos.valor()._pacientes_vinculados.inserta(codigo_id, nombre);
        infoPaciente._citado = false;
        _pacientes.inserta(codigo_id, infoPaciente);
    }
}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
bool CentroSalud::citar(tCodigoPaciente codigo_id) {
	// A IMPLEMENTAR
    DiccionarioHash<tNumPacientes, tInfoPaciente>::Iterator it_paciente = _pacientes.busca(codigo_id);
    DiccionarioHash<tNumColegiado, tInfoMedico>::Iterator it_medico = _medicos.busca(it_paciente.valor()._medico);

    if (it_paciente != _pacientes.end()) {
        if (it_paciente.valor()._citado || it_medico.valor()._max_personas_atendidas == 0) {
            return false;
        }
        else {
            it_medico.valor()._max_personas_atendidas--;
            it_medico.valor()._pacientes_citados.pon_ppio(it_paciente.clave());
            it_paciente.valor()._citado = true;
            it_paciente.valor()._paciente_citado_it = it_medico.valor()._pacientes_citados.begin();
            return true;
        }
    }
    else {
        throw ECitaNoAdmitida();
    }
}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
const Lista<tCodigoPaciente>& CentroSalud::citados(tNumColegiado num_colegiado) const {
	// A IMPLEMENTAR
    DiccionarioHash<tNumColegiado, tInfoMedico>::ConstIterator cit_medico = _medicos.cbusca(num_colegiado);
    if (cit_medico != _medicos.cend()) {
        return cit_medico.valor()._pacientes_citados;
    }
    else {
        throw EMedicoInexistente();
    }
}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
bool CentroSalud::cancelar_cita(tCodigoPaciente codigo_id) {
	// A IMPLEMENTAR
    DiccionarioHash<tNumPacientes, tInfoPaciente>::Iterator it_paciente = _pacientes.busca(codigo_id);
    

    if (it_paciente != _pacientes.end()) {
        DiccionarioHash<tNumColegiado, tInfoMedico>::Iterator it_medico = _medicos.busca(it_paciente.valor()._medico);
        if (!it_paciente.valor()._citado) {
            return false;
        }
        else {
            it_paciente.valor()._citado = false;
            it_medico.valor()._max_personas_atendidas++;
            it_medico.valor()._pacientes_citados.eliminar(it_paciente.valor()._paciente_citado_it);

            return true;
        }
    }
    else {
        throw ECancelacionNoAdmitida();
    }
}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
Lista<Codigo_y_Nombre> CentroSalud::vinculados(tNumColegiado num_colegiado) const {
    // A IMPLEMENTAR
    Lista<Codigo_y_Nombre> lista;
    Codigo_y_Nombre conjunto;
    DiccionarioHash<tNumColegiado, tInfoMedico>::ConstIterator cit_medicos = _medicos.cbusca(num_colegiado);
    if (cit_medicos != _medicos.cend()) {
        Diccionario<tNumPacientes, tNombre>::ConstIterator cit_pacientes = cit_medicos.valor()._pacientes_vinculados.cbegin();
        while (cit_pacientes != cit_medicos.valor()._pacientes_vinculados.cend()) {
            conjunto.codigo = cit_pacientes.clave();
            conjunto.nombre = cit_pacientes.valor();
            lista.pon_final(conjunto);
            cit_pacientes.next();
        }
        return lista;
    }
    else {
        throw EMedicoInexistente();
    }
}

