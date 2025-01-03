
#include <iostream>
using namespace std;

/* Estructura utilizada para almacenar la información de un tema */
typedef struct {
	float tiempo_req;  // tiempo requerido para estudiar el tema
	float nota_prim;   // aportación a la nota de la primera parte
	float nota_sec;    // aportación a la nota de la segunda parte
} tInfoTema;



/*
DISEÑO DEL ALGORITMO

Para superar este ejercicio, aparte de programar el algoritmo, debes
describir aqui detalladamente su diseño (parámetros y variables utilizados,
y su cometido, cometido de los resultados devueltos por las funciones,
idea general del algoritmo, estructura de las soluciones,
análisis de casos, acciones realizadas para cada caso...)





*/

/* temas: Información sobre los temas de los que consta el examen (ver tInfoTema)
   num_temas: Numero de temas de los que consta el examen -su información aparece
			  al principio de info_temas
   tiempo_disponible: Tiempo total disponible para realizar el examen.
   Valor devuelto: La puntuación media máxima que se puede conseguir, o -1 si no
				   es posible aprobar el examen */



void VA(const tInfoTema info_temas[], unsigned int num_temas, float tiempo_disponible, int k, float& nota_maxima, float nota1, float nota2) {
	
	//Estudia el tema

	if (tiempo_disponible >= info_temas[k].tiempo_req) { // Si es valida
		nota1 += info_temas[k].nota_prim;	//se añaden los valores que da por consecuencia estudiar el tema(mas nota y menos tiempo disponible total)
		nota2 += info_temas[k].nota_sec;
		tiempo_disponible -= info_temas[k].tiempo_req;
		if (k == num_temas - 1) { // Es solucion
			if (nota1 >= 5 && nota2 >= 5 && ((nota1+nota2)/2 > nota_maxima)) { //si ha aprobado los dos examenes, y la media es mejor que la nota maxima hasta el momento
				if (((nota1 + nota2) / 2) >= 10)
					nota_maxima = 10;
				else
					nota_maxima = (nota1 + nota2) / 2;
			}
		}
		else {
			VA(info_temas, num_temas, tiempo_disponible, k + 1, nota_maxima, nota1, nota2);
		}
		nota1 -= info_temas[k].nota_prim;	// Recupera el valor de todas
		nota2 -= info_temas[k].nota_sec;
		tiempo_disponible += info_temas[k].tiempo_req;
	}

	// No estudia el tema

	// Siempre es valido
	if (k == num_temas - 1) { // Es solucion
		if (nota1 >= 5 && nota2 >= 5 && ((nota1 + nota2) / 2 > nota_maxima)) { //si ha aprobado los dos examenes, y la media es mejor que la nota maxima hasta el momento
			if (((nota1 + nota2) / 2) >= 10)
				nota_maxima = 10;
			else
				nota_maxima = (nota1 + nota2) / 2;
		}
	}
	else {
		VA(info_temas, num_temas, tiempo_disponible, k + 1, nota_maxima, nota1, nota2);
	}
}






float mejor_puntuacion(const tInfoTema info_temas[], unsigned int num_temas, float tiempo_disponible) {
	/* ESTA FUNCIÓN SERÁ EL PUNTO DE ENTRADA AL ALGORITMO. Puedes, después, utilizar las
	   funciones auxiliares que consideres oportuno, pero debes incluir la justificación para ello
	   en el comentario de descripción detallado del diseño de dicho algoritmo */
	float nota_maxima = -1;
	VA(info_temas, num_temas, tiempo_disponible, 0, nota_maxima, 0 , 0);
	return nota_maxima;
}

/* Código para leer y ejecutar casos de prueba: no debe modificarse */
const unsigned int MAX_TEMAS = 20;

bool procesa_caso() {
	int num_temas;
	tInfoTema info_temas[MAX_TEMAS];
	cin >> num_temas;
	if (num_temas != -1) {
		float tiempo_disponible;
		cin >> tiempo_disponible;
		for (int i = 0; i < num_temas; i++) {
			cin >> info_temas[i].tiempo_req;
			cin >> info_temas[i].nota_prim;
			cin >> info_temas[i].nota_sec;
		}
		cout << mejor_puntuacion(info_temas, num_temas, tiempo_disponible) << endl;
		return true;
	}
	else {
		return false;
	}
}

int main() {
	while (procesa_caso());
}