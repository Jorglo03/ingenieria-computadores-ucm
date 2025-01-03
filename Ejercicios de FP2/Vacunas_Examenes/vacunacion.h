

// Examen de FP2 del día 15 de julio ed 2021

// NOMBRE Y APELLIDOS: Jorge López Carrión
// email: jorglo03@ucm.es
// Usuario del juez para realizar el examen: FP2-A64

#ifndef vacunacion_h
#define vacunacion_h

#pragma once
#include <string>
using namespace std;

const int MAX_CENTROS = 6;		//Se declaran las constantes necesarias
const int DIAS_MES = 31;

typedef struct {				//Se declaran los tipos necesarios
	int dosis;
	string centro;
}tInfoCentro;
typedef struct {
	int contador;
	tInfoCentro centros[MAX_CENTROS];
}tListaCentros;

typedef struct {
	string nombre;
	tListaCentros centros;
}tInfoVacuna;
typedef tInfoVacuna* tVacunaPtr;
typedef	tVacunaPtr tListaVacunas[DIAS_MES];

typedef struct {
	string nomVacuna;
	int nSuministradas;
	int nDia;
	string nomCentro;
}tVecinos;


void inicializarListaVAcunas(tListaVacunas vacunas);		//Se declaran los prototipos de las funciones
void cargarVacunasCentros(tListaVacunas vacunas);
void vacunar(tListaVacunas vacunas);
void mostrar(tListaVacunas vacunas);
void liberarListaCentros(tListaVacunas vacunas);
void ordenar(tListaVacunas vacunas);
int buscar(tListaVacunas vacunas, string vacuna);

#endif 