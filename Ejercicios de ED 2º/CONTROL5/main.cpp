#include "GestionAdmisiones.h"

#include <iostream>
#include <string>
using namespace std;


void admite(GestionAdmisiones& admisiones) {
	CodigoPaciente codigo;
	string nombre;
	unsigned int edad;
	string sintomas;
	cin >> codigo >> nombre >> edad >> sintomas;
	try {
		admisiones.an_paciente(codigo, nombre, edad, sintomas);
		cout << "OK" << endl;
	}
	catch (EPacienteDuplicado) {
		cout << "CODIGO_PACIENTE_DUPLICADO" << endl;
	}
}

void atiende(GestionAdmisiones& admisiones) {
	try {
		CodigoPaciente codigo_siguiente;
		admisiones.siguiente(codigo_siguiente);
		admisiones.elimina(codigo_siguiente);
		cout << "OK" << endl;
	}
	catch (ENoHayPacientes) {
		cout << "NO_HAY_PACIENTES" << endl;
	}
}

void desiste(GestionAdmisiones& admisiones) {
	CodigoPaciente codigo;
	cin >> codigo;
	admisiones.elimina(codigo);
	cout << "OK" << endl;
}

void muestra_siguiente(GestionAdmisiones& admisiones) {
	CodigoPaciente codigo;
	string nombre;
	unsigned int edad;
	string sintomas;
	try {
		admisiones.siguiente(codigo);
		admisiones.info_paciente(codigo, nombre, edad, sintomas);
		cout << codigo << " " << nombre << " " << edad << " " << sintomas << " " << endl;
	}
	catch (ENoHayPacientes) {
		cout << "NO_HAY_PACIENTES" << endl;
	}
}

void datos_paciente(GestionAdmisiones& admisiones) {
	CodigoPaciente codigo;
	string nombre;
	unsigned int edad;
	string sintomas;
	cin >> codigo;
	try {
		admisiones.info_paciente(codigo, nombre,edad, sintomas);
		cout << nombre << " " << edad << " " << sintomas << endl;
	}
	catch (EPacienteNoExiste) {
		cout << "PACIENTE_NO_EXISTE" << endl;
	}
}

void en_espera(const GestionAdmisiones& admisiones) {
	if (admisiones.hay_pacientes()) 
		cout << "SI" << endl;
	else  
		cout << "NO" << endl;
}


int main() {
	GestionAdmisiones admisiones;
	string comando;
	while(cin >> comando) {
			if (comando == "admite") admite(admisiones);
			else if (comando == "atiende") atiende(admisiones);
			else if (comando == "desiste") desiste(admisiones);
			else if (comando == "siguiente") muestra_siguiente(admisiones);
			else if (comando == "datos") datos_paciente(admisiones);
			else if (comando == "en_espera") en_espera(admisiones);
	}
	return 0;
}