

// Examen de FP2 del día 15 de julio ed 2021

// NOMBRE Y APELLIDOS: Jorge López Carrión
// email: jorglo03@ucm.es
// Usuario del juez para realizar el examen: FP2-A64



#include "vacunacion.h"
#include <iostream>
#include <fstream>
using namespace std;


void inicializarListaVAcunas(tListaVacunas vacunas) {				//Se solicita memoria dinamica para cada dia del mes
	for (int i = 0; i < DIAS_MES; i++) {
		vacunas[i] = new tInfoVacuna;
	}
}

void cargarVacunasCentros(tListaVacunas vacunas) {
	int aux, j;


	for (int i = 0; i < DIAS_MES; i++) {			//Se recorren todos los dias del mes	
		cin >> vacunas[i]->nombre;					//Se guarda el nombre de la vacuna
		vacunas[i]->centros.contador = 0;			//Se inicializa el contador
		cin >> aux;					
		j = 0;
		while (aux != -1) {							//Mientras no se encuentre el centinela
			vacunas[i]->centros.centros[j].dosis = aux;		//Se guardan los datos de los centros
			cin >> vacunas[i]->centros.centros[j].centro;
			vacunas[i]->centros.contador++;
			cin >> aux;
			j++;
		}
		ordenar(vacunas);
	}
}

void ordenar(tListaVacunas vacunas) {
	tInfoCentro aux2;

	for (int i = 0; i < DIAS_MES; i++) {
		for (int j = 0; j < vacunas[i]->centros.contador - 1; j++) {		//Se ordena los centros por el metodo burbuja
			for (int k = vacunas[i]->centros.contador - 1; k > j; k--) {
				if (vacunas[i]->centros.centros[k].dosis > vacunas[i]->centros.centros[k - 1].dosis) {	//Principalmente por dosis
					aux2 = vacunas[i]->centros.centros[k];
					vacunas[i]->centros.centros[k] = vacunas[i]->centros.centros[k - 1];
					vacunas[i]->centros.centros[k - 1] = aux2;
				}
				else if (vacunas[i]->centros.centros[k].dosis == vacunas[i]->centros.centros[k - 1].dosis) {	//Sino, por orden alfabetico
					if (vacunas[i]->centros.centros[k].centro.compare(vacunas[i]->centros.centros[k - 1].centro) < 0) {
						aux2 = vacunas[i]->centros.centros[k];
						vacunas[i]->centros.centros[k] = vacunas[i]->centros.centros[k - 1];
						vacunas[i]->centros.centros[k - 1] = aux2;
					}
				}
			}
		}
	}
}

void vacunar(tListaVacunas vacunas) {
	tVecinos vecinos;
	string vacuna;
	int dia;

	cout << endl << "Resultados de vacunar" << endl << "---------------------" << endl;
	cin >> vacuna;
	while (vacuna != "XXX") {			//Mientras no se encuentre el centinela, se van asignando a cada ciudadano un lugar para ponerle una dosis
		vecinos.nomVacuna = vacuna;			
		cin >> vecinos.nSuministradas;
		dia = buscar(vacunas, vacuna);
		vecinos.nDia = dia;
		vecinos.nomCentro = vacunas[dia - 1]->centros.centros[0].centro;
		vecinos.nSuministradas++;
		vacunas[dia - 1]->centros.centros[0].dosis--;
		cout << vecinos.nomVacuna << " " << vecinos.nSuministradas << " " << vecinos.nomCentro << " " << vecinos.nDia << endl;
		cin >> vacuna;
	}
}

int buscar(tListaVacunas vacunas, string vacuna) {			//Busca un dia para poder vacunar al ciudadano del pueblo
	int dia = 0, i = 0;
	bool fin = false;

	while(i < DIAS_MES && !fin) {
		if (vacuna == vacunas[i]->nombre) {
			dia = i + 1;
			fin = true;
		}
		i++;
	}

	return dia;
}

void mostrar(tListaVacunas vacunas) {
	int j;

	for (int i = 0; i < DIAS_MES; i++) {		//Se muestran lo vacunas y los centros y dosis de cada una
		cout << vacunas[i]->nombre << " ";
		j = 0;
		while (j < vacunas[i]->centros.contador) {
			cout << vacunas[i]->centros.centros[j].centro << "(" << vacunas[i]->centros.centros[j].dosis << ") -";
			j++;
		}
		cout << endl;
	}
}

void liberarListaCentros(tListaVacunas vacunas) {	//Se libera toda la memoria dinamica solicitada

	for (int i = 0; i < DIAS_MES; i++) {
		delete vacunas[i];
		vacunas[i] = nullptr;
	}
}