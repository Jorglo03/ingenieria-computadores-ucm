
#include <iostream>
using namespace std;

/*
DISE�O DEL ALGORITMO:
-- Describe con claridad, justificando las decisiones de dise�o realizadas,
-- el funcionamiento de tu algoritmo. Especifica claramente el cometido de cada
-- par�metro (en caso de que utilices una generalizaci�n), los casos base, y los
-- casos recursivos

ANALISIS DE LA COMPLEJIDAD:
-- Determina justificadamente el orden de complejidad del algoritmo dise�ado.
-- Escribe y resuelve las ecuaciones de recurrencia.

*/

bool es_interesante_aux(int n, int& suma_encima, int suma_debajo, bool es) {
	if (n < 10) {			//CASO BASE
		suma_encima = n;						//si hay solo un digito se coge para la suma de los numeros de encima
		return suma_debajo % n == 0;			//devuelve si el digito de mayor valor es divisible entre la suma de los numero de debajo
	}
	else {					//CASO RECURSIVO
		if (n % 10 != 0 && es) {		//Se comprueba que no hay 0s, y que hasta el momento es interesante el numero, sino, ya se descarta	
			suma_debajo += n % 10;		//la suma de los numeros de abajo se va haciendo en la "ida"
			es = es_interesante_aux(n / 10, suma_encima, suma_debajo, es) && (suma_debajo % ((n / 10) % 10)) == 0;	//comprobando que el digito, es divisible entre la suma de los de abajo
			if (es) {
				es = es && (suma_encima % (n % 10)) == 0;		//se comprueba si la suma de los de arriba es divisible entre el digito que estamos
				suma_encima += n % 10;							//la suma de los numeros de arriba, se va haciendo a la "vuelta"
				return es;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}

	}


}

bool es_interesante(unsigned int n) {
	// A IMPLEMENTAR
	int suma_encima = 0, suma_debajo = 0;
	if (n == 0) {
		return false;
	}
	return es_interesante_aux(n, suma_encima, suma_debajo, true);
}

void ejecuta_caso() {
	unsigned int n;
	cin >> n;
	if (es_interesante(n)) {
		cout << "SI" << endl;
	}
	else {
		cout << "NO" << endl;
	}
}

int main() {
	unsigned int num_casos;
	cin >> num_casos;
	for (int i = 0; i < num_casos; i++) {
		ejecuta_caso();
	}
}