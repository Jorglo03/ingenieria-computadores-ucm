
// Examen de FP2 del día 8 de junio ed 2021

// Nombre y apellidos: Jorge López Carrión	
// Grupo: 1ºA
// email: jorglo03@ucm.es
// Usuario del juez para realizar el examen: FP2-A64



#ifndef Oposiciones_h
#define Oposiciones_h

#include <string>
using namespace std;

const int MAX_OPOSITORES = 100;		//Se declaran las constantes necesarias
const int MAX_EJERCICIOS = 7;
const int APROBADO = 5;

typedef struct {					//Se declaran los tipos necesarios
	string opositor;
	int notas[MAX_EJERCICIOS];
	int aprobados;
	float mediaCalificaciones;
}tOpositor;

typedef tOpositor *tOpositorPtr;
typedef struct {
	int contador;
	tOpositorPtr opositor[MAX_OPOSITORES];
}tListaOpositores;

typedef struct {
	string* opositor;
	int contador;
}tListaAprobPlaza;

void cargarOpositores(tListaOpositores& opositores, int& numPlazas);		//Se declaran los prototipos de las funciones
void ordenar(tListaOpositores& opositores);
void eliminarOrdenado(tListaOpositores& opositores, int posicion);
void candidatosConPlaza(tListaAprobPlaza& aprobados, tListaOpositores& opositores, int numPlazas);
void mostrarListaOpositores(tListaOpositores opositores);
void mostrarAprobadosConPlaza(tListaAprobPlaza aprobados);
void liberarListaOpositores(tListaOpositores opositores);
void LiberarListaAprobados(tListaAprobPlaza aprobados);

#endif