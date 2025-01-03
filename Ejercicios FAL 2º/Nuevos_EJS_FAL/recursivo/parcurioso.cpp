#include <iostream>
#include <algorithm>
using namespace std;


/*
(1) Precondición

(2) Postcondición

(3) Si vas a utilizar una generalización, especificación
	pre-pos de la generalización

(4) Casos no recursivos

(5) Casos recursivos

(6) Terminación (expresión de cota)

(7) Si has usado una generalización, definición por
	inmersión de es_paracurioso

(8) Determinación de la complejidad (recurrencias y su resolución)


*/
bool es_parcurioso_aux(int v[], int n,int i, int f, int& pares, int& impares, int& suma_pares, int& suma_impares) {
	if (f-i+1 == 1) {				//CASO BASE	//Si el longitud del tramo es igual a 1
		pares = 0;					//Al llegar al caso base se inicializan todas las variables
		impares = 0;
		suma_pares = 0;
		suma_impares = 0;
		if (v[i] % 2 == 0) {		//se comprueba si el elemento es par o impar para aniadirlo a la variable que corresponda
			pares++;
			suma_pares += v[i];
		}
		else {
			impares++;
			suma_impares += v[i];
		}
		return true;				//Un tramo con un solo elemento es parcurioso
	}
	else {						//CASO RECURSIVO	
		bool es1, es2;			//dos variables bool para cada lado
		int pares_izq, pares_der, impares_izq, impares_der, suma_pares_izq, suma_pares_der, suma_impares_izq, suma_impares_der;	//se inicializan variables para cada lado del tramo (izquierda o derecha)
		int m = (f + i) / 2;	//calculo de la mitad del tramo	
		es1 = es_parcurioso_aux(v, n, i, m, pares_izq, impares_izq, suma_pares_izq, suma_impares_izq);		//mitad izquierda, desde i hasta m
		es2 = es_parcurioso_aux(v, n, m + 1, f, pares_der, impares_der, suma_pares_der, suma_impares_der);	//mitad derecha, desde m+1 hasta f

		suma_pares = suma_pares_izq + suma_pares_der;		//se calculan las variables generales al juntar ese tramo izquierdo con el derecho para al salir de esta llamada recursiva, tengamos ya guardada las sumas y el numero de pares e impares en las variables correspondientes
		suma_impares = suma_impares_izq + suma_impares_der;
		pares = pares_izq + pares_der;			
		impares = impares_izq + impares_der;
		return pares_izq <= impares_der && suma_pares_izq <= suma_impares_der && (es1 || es2); //se devuelve la logica que necesita un tramo para ser parcurioso
	}




}




bool /* resul*/ es_parcurioso(int v[], int n) {
	// A IMPLEMENTAR
	int i = 0, f = n - 1, pares, impares, suma_pares, suma_impares;
	return es_parcurioso_aux(v, n, i, f, pares, impares, suma_pares, suma_impares);
}


// NO MODIFICAR

const static int MAX_ELEMENTS = 100000;

void ejecuta_caso() {
	static int v[MAX_ELEMENTS];
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}
	if (es_parcurioso(v, n)) {
		cout << "SI" << endl;;
	}
	else {
		cout << "NO" << endl;
	}
}


int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		ejecuta_caso();
	return 0;
}