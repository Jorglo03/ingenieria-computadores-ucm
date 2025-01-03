/*
NOMBRE Y APELLIDOS:

IMPORTANTE: Si no se a?ade el nombre y apellidos,
el ejercicio no se corregir? (puntuar? como 0).

*/

#include <iostream>

using namespace std;

/*
IMPORTANTE: Para superar este ejercicio es necesario desarrollar
correctamente los distintos pasos del dise?o del algoritmo. No
se tendr? en cuenta la codificaci?n del algoritmo, a menos que
est? acompa?ada de la especificaci?n y el dise?o sistem?tico
del mismo.
*/


/*
   vcs: vector de valores cal?ricos.
   vns: vector de valores nutricionales.
   n: N?mero de chuches.
   u: Umbral cal?rico
*/
/*
PRECONDICION DE LA FUNCION:
  ---Escribe aqu? la precondici?n de la funci?n.

*/
int mejor_cajita(int vcs[], int vns[], int n, int u);
/*
POSTCONDICION DE LA FUNCION:
  -- Escribe aqu? la postcondici?n de la funci?n. Para referirte
  -- al resultado puedes usar la pseudovariable 'resul'

*/

/*
DISE?O DEL ALGORITMO:

Paso 1. Variables

Paso 2. Invariante

Paso 3. Inicializaci?n

Paso 4. Condici?n del bucle, y c?digo tras el bucle.

Paso 5. Cuerpo del bucle

Paso 6. Justificaci?n de que el algoritmo siempre termina.

Paso 7. Complejidad:




CASOS:
10
5 2 3 4 1 2 4 7 6 5
3 5 7 5 2 4 5 6 7 4
7
5
1 3 2 4 5
5 4 1 2 3
6
*/
int mejor_cajita(int vcs[], int vns[], int n, int u) {
	// A IMPLEMENTAR: Devolver el mayor valor nutricionales
	// que puede conseguirse sin superar el umbral cal?rico.
	// Recuerda: vcs[n]: vector de valores cal?ricos,
	//           vns[n]: vector de valores nutricionales,
	//           u: umbral cal?rico
	//           Debe devolverse el m?ximo valor nutricional 
	//           que puede conseguirse.
	int i = 0, f = 1, calorias = vcs[0], nutricion = vns[0], resul = vns[0];

	while (f < n) {
		if (calorias + vcs[f] <= u) {
			calorias += vcs[f];
			nutricion += vns[f];
			f++;

			if (nutricion > resul)
				resul = nutricion;
		}
		else if (calorias + vns[f] > u) {
			calorias -= vcs[i];
			nutricion -= vns[i];
			i++;
		}
	}
	return resul;

}

/************************************************************/
// Programa de prueba: NO MODIFICAR. Aquellas soluciones que
// modifiquen el c?digo que sigue no se corregir?n (puntuar?n 0).

const static int MAX_CHUCHES = 1000000;

bool ejecuta_caso() {
	int n;
	cin >> n;
	if (n == -1) return false;
	else {
		static int calorias[MAX_CHUCHES];
		static int nutricionales[MAX_CHUCHES];
		for (int i = 0; i < n; i++) {
			cin >> calorias[i];
		}
		for (int i = 0; i < n; i++) {
			cin >> nutricionales[i];
		}
		int umbral;
		cin >> umbral;
		cout << mejor_cajita(calorias, nutricionales, n, umbral) << endl;
		return true;
	}
}

int main() {
	while (ejecuta_caso());
	return 0;
}