
#include <iostream>

using namespace std;


/*
DISEÑO DEL ALGORITMO:
-- Describe con claridad, justificando las decisiones de diseño realizadas,
-- el funcionamiento de tu algoritmo. Especifica claramente el cometido de cada
-- parámetro (en caso de que utilices una generalización), los casos base, y los
-- casos recursivos

ANALISIS DE LA COMPLEJIDAD:
-- Determina justificadamente el orden de complejidad del algoritmo diseñado.
-- Escribe y resuelve las ecuaciones de recurrencia.

*/
bool sumdivisibles_aux(int n, int& digitos, int& suma) {
	//voy desde un digito a más digitos
	if (n <= 9) {			//CASO BASE
		digitos = 1;
		suma = n;
		return true;
	}
	else {					//CASO RECURSIVO
		bool sumdivisible;
		sumdivisible = sumdivisibles_aux(n / 10, digitos, suma);
		digitos++;
		suma += n % 10;	//desde un digito, va añadiendo la suma a la que va habiendo mas digitos
		return sumdivisible && (suma % digitos) == 0;//Devuelve si hasta ese digito es sumdivisible y ademas, si con ese digito es sumdivisible
	}



}


bool sumdivisible(int n) {
	/* IMPLEMENTACION:
	   Esta función será el punto de entrada a tu algoritmo.
	   Puedes implementar, además, las funciones auxiliares
	   que consideres oportuno.
	   -- n: El número cuya sumdivisibilidad debes determinar.
	   -- La función deberá devolver 'true' si n es sumdivisible,
	   -- y 'false' en otro caso
	*/
	int digitos, suma;
	return sumdivisibles_aux(n, digitos, suma);

}


/* CODIGO DE LECTURA Y EJECUCION DE CASOS DE PRUEBA:
   NO MODIFICAR */

int main() {
	int n;
	do {
		cin >> n;
		if (n > 0) {
			if (sumdivisible(n))
				cout << "SI" << endl;
			else
				cout << "NO" << endl;
		}
	} while (n > 0);
}

