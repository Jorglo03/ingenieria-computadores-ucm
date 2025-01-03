
// Examen de FP2 del día 8 de junio ed 2021

// Nombre y apellidos: Jorge López Carrión	
// Grupo: 1ºA
// email: jorglo03@ucm.es
// Usuario del juez para realizar el examen: FP2-A64





#include <iostream>					//Se declaran las bibliotecas
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

#include "Oposiciones.h"

void cargarOpositores(tListaOpositores& opositores, int& numPlazas) {
	int nota, j;

	cin >> numPlazas >> opositores.contador;			//Se leen el numero de plazas y el numero de opositores
	for (int i = 0; i < opositores.contador; i++) {
		opositores.opositor[i] = new tOpositor;			//Se guarda memoria para cada opositor
		opositores.opositor[i]->aprobados = 0;
		cin >> opositores.opositor[i]->opositor;
		j = 0;
		cin >> nota;
		while (nota >= APROBADO) {						//Se guardan todas las notas de cada opositor
			opositores.opositor[i]->notas[j] = nota;
			opositores.opositor[i]->aprobados++;
			j++;
			cin >> nota;
		}
	}
}

void ordenar(tListaOpositores& opositores) {
	tOpositorPtr aux;

	for (int i = 0; i < opositores.contador - 1; i++){			//Se ordenan de mayor a menor los opositores segun su media por el metodo burbuja
		for (int j = opositores.contador - 1; j > i; j--) {
			if (opositores.opositor[j]->mediaCalificaciones > opositores.opositor[j - 1]->mediaCalificaciones) {
				aux = opositores.opositor[j];
				opositores.opositor[j] = opositores.opositor[j - 1];
				opositores.opositor[j - 1] = aux;
			}
		}
	}
}

void eliminarOrdenado(tListaOpositores& opositores, int posicion) {
	for (int i = posicion; i < opositores.contador - 1; i++) {		//Se elimina el opositor en la posicion dada, liberando la memoria correspondiente
		*opositores.opositor[i] = *opositores.opositor[i + 1];
	}
	delete opositores.opositor[opositores.contador - 1];
	opositores.opositor[opositores.contador - 1] = nullptr;
	opositores.contador--;
}

void candidatosConPlaza(tListaAprobPlaza& aprobados, tListaOpositores& opositores, int numPlazas) {
	int numAprobados = 0;

	cout << endl << "Num. de plazas: " << numPlazas << endl << endl;
	for (int i = 0; i < opositores.contador; i++) {							//Se calcula el numero de aprobados
		if (opositores.opositor[i]->mediaCalificaciones >= 5) {
			numAprobados++;
		}
	}
	if (numPlazas >= numAprobados) {										//Si hay mas plazas que aprobados
		aprobados.opositor = new string[numAprobados];						//Se solicita memoria dinamica
		for (int i = 0; i < opositores.contador; i++) {
			if (opositores.opositor[i]->mediaCalificaciones >= 5) {			//Si ha aprobado el opositor
				aprobados.opositor[aprobados.contador] = opositores.opositor[i]->opositor;	//Se le guarda una plaza
				aprobados.contador++;
				eliminarOrdenado(opositores, i);							//Se le elimina de la lista de opositores
				i--;
			}
		}
	}
	else {
		aprobados.opositor = new string[numPlazas];							//Se solicita memoria dinamica
		for (int i = 0; i < numPlazas; i++) {
			aprobados.opositor[i] = opositores.opositor[0]->opositor;		//Se guarda el nombre del opositor en su plaza
			aprobados.contador++;
			eliminarOrdenado(opositores, 0);								//Se le elimina de la lista de opositores
		}		
	}
}

void mostrarListaOpositores(tListaOpositores opositores) {					//Muestra la lista de opositores con el formato pedido
	for (int i = 0; i < opositores.contador; i++) {
		cout << "Identificador " << opositores.opositor[i]->opositor << " - nota final " << setprecision(6) << opositores.opositor[i]->mediaCalificaciones;
		cout << endl;
	}
}

void mostrarAprobadosConPlaza(tListaAprobPlaza aprobados){					//Muestra la lista de aprobados con plaza con el formato pedido
	for (int i = 0; i < aprobados.contador; i++) {
		cout << "Identificador " << aprobados.opositor[i] << endl;
	}
}

void liberarListaOpositores(tListaOpositores opositores) {					//Libera la memoria solicitada para la lista de opositores
	for (int i = 0; i < opositores.contador; i++) {
		delete opositores.opositor[i];
		opositores.opositor[i] = nullptr;
	}
}

void LiberarListaAprobados(tListaAprobPlaza aprobados) {					//Libera la memoria solicitada para la lista de aprobados
	delete[] aprobados.opositor;
	aprobados.opositor = nullptr;
}