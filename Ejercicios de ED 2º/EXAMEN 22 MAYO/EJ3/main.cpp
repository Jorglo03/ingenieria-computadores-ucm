// NO MODIFIQUES NADA DE LO QUE APARECE EN ESTE FICHERO

#include <iostream>
#include <string>
using namespace std;
#include "centroSalud.h"


void registraMedico(CentroSalud& centro) {
	tNumColegiado id;
	tNumPacientes npac;
	cin >> id >> npac;
	try {
		centro.annadir_medico(id, npac);
		cout << "REGISTRO_MEDICO_OK" << endl;
	}
	catch (EMedicoExistente) {
		cout << "ERROR_ID_MEDICO_DUPLICADO" << endl;
	}
}


void registraPaciente(CentroSalud& centro) {
	tCodigoPaciente codigo;
	tNombre nombre;
	tNumColegiado num_colegiado;
	cin >> codigo >> nombre >> num_colegiado;
	try {
		centro.annadir_paciente(codigo, nombre, num_colegiado);
		cout << "REGISTRO_PACIENTE_OK" << endl;
	}
	catch (ECitaNoAdmitida) {
		cout << "ERROR_REGISTRO_PACIENTE" << endl;
	}
}


void pideCita(CentroSalud& centro) {
	tCodigoPaciente codigo;
	cin >> codigo;
	try {
		bool ok = centro.citar(codigo);
		if (ok) cout << "CITA_OK" << endl;
		else cout << "CITA_NO_OK" << endl;
	}
	catch (ECitaNoAdmitida) {
		cout << "ERROR_REGISTRO_CITA" << endl;
	}
}


void mostrarListaPacientes(const Lista<tCodigoPaciente>& l) {
	Lista<tCodigoPaciente>::ConstIterator it = l.cbegin();
	while (it != l.cend()) {
		cout << it.elem() << " // ";
		it.next();
	}
}

void citados(const CentroSalud& centro) {
	tNumColegiado num_colegiado;
	cin >> num_colegiado;
	try {
		cout << "CITADOS: ";
		mostrarListaPacientes(centro.citados(num_colegiado));
		cout << endl;
	}
	catch (EMedicoInexistente) {
		cout << "ERROR_MEDICO_INEXISTENTE" << endl;
	}
}


void cancelaCita(CentroSalud& centro) {
	tCodigoPaciente codigo;
	cin >> codigo;
	try {
		if (centro.cancelar_cita(codigo))
			cout << "CANCELACION_OK" << endl;
		else 
			cout << "CANCELACION_NO_OK" << endl;
	}
	catch (ECancelacionNoAdmitida) {
		cout << "ERROR_PACIENTE_INEXISTENTE" << endl;
	}
}


void mostrarListaCodigoNombre(const Lista<Codigo_y_Nombre>& l) {
	Lista<Codigo_y_Nombre>::ConstIterator it = l.cbegin();
	while (it != l.cend()) {
		cout << it.elem().codigo << "-" << it.elem().nombre << " // ";
		it.next();
	}
}

void vinculados(const CentroSalud& centro) {
	tNumColegiado num_colegiado;
	cin >> num_colegiado;
	try {
		cout << "VINCULADOS: ";
		mostrarListaCodigoNombre(centro.vinculados(num_colegiado));
		cout << endl;
	}
	catch (EMedicoInexistente) {
		cout << "ERROR_MEDICO_INEXISTENTE" << endl;
	}
}



int main() {
	CentroSalud centro;
	string comando;

	while (cin >> comando) {
		if (comando == "registraMedico") registraMedico(centro);
		else if (comando == "registraPaciente") registraPaciente(centro);
		else if (comando == "pideCita") pideCita(centro);
		else if (comando == "citados") citados(centro);
		else if (comando == "cancelaCita") cancelaCita(centro);
		else if (comando == "vinculados") vinculados(centro);
	}
	return 0;
}


