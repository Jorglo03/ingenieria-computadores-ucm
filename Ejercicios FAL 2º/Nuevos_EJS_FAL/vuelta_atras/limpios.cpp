

#include <iostream>

using namespace std;

typedef unsigned long long t_num;


/*

(1) En caso de utilizar una generalización, indicar su parámetros, y explicar para que
sirven cada uno de ellos

(2) ¿Cómo son las soluciones parciales de este problema?

(3) ¿Cuándo una solución parcial es viable?

(4) ¿Cuándo una solución parcial es una solución final al problema?

(5) Dada una solución parcial, ¿cómo se generan las siguientes soluciones
parciales viables?

(6) Análisis de casos

(6.1) Caso(s) base


(6.2) Caso(s) recursivos

(7) En caso de utilizar una generalización, explicar cómo se define el algoritmo final
a partir de la misma, por inmersión.



*/

void backtrack(unsigned short d, unsigned short alpha, t_num n, unsigned int s, unsigned int suma, int& total, int num_d, t_num num_actual) {
	for (int i = 1; i < 10; i++) {
		num_actual = num_actual * 10 + i;
		suma += i;
		if (i == d) {
			if (num_actual < n && suma <= s && num_d + 1 < alpha) {
				if (suma == s && num_d + 1 < alpha) {
					total++;
				}
				else {
					if(num_actual * 10 < n)
						backtrack(d, alpha, n, s, suma, total, num_d + 1, num_actual);
				}
			}
		}
		else {
			if (num_actual < n && suma <= s && 0 < alpha) {
				if (suma == s && 0 < alpha) {
					total++;
				}
				else {
					if (num_actual * 10 < n)
						backtrack(d, alpha, n, s, suma, total, 0, num_actual);
				}
			}
		}
		suma -= i;
		num_actual = (num_actual - i) / 10;
	}
}


int num_limpios(unsigned short d, unsigned short alpha, t_num n, unsigned int s) {
	// PUNTO DE ENTRADA DEL ALGORITMO
	int total= 0;

	backtrack(d, alpha, n, s, 0, total, 0, 0);

	return total;
}


bool ejecuta_caso() {
	int d;
	cin >> d;
	if (d == -1) {
		return false;
	}
	else {
		unsigned short alpha;
		unsigned int s;
		t_num n;
		cin >> alpha >> s >> n;
		cout << num_limpios(d, alpha, n, s) << endl;
		return true;
	}
}


int main() {
	while (ejecuta_caso());
}