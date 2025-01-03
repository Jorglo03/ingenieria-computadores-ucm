/*
NOMBRE Y APELLIDOS:

*/

#include <iostream>
using namespace std;


/*

PRECONDICION DE LA FUNCION:
---Escribe aquí la precondición de la función.
	P: {0 ≤ n ≤ 1000000 && c>=0 && PARATODO i: 0<=i<n: a[i]>0}

*/

bool /* resul */ hay_c_tramo(int a[], int n, int c);

/*
	   POSTCONDICION DE LA FUNCION:
	   ---Escribe aquí la poscondición de la función. Para refirte
	   ---al valor devuelto por la función, utiliza la pseudo-variable
	   ---'resul'
	(1) Definiciones auxiliares (si procede):
		suma(a, i, j) = SUMA u: i<=u<=j: a[u]

	(2) Postcondición
		Q: {(resul = max i, j: 0<=i<=j<n && suma(a, i, j) <= c: suma(a, i, j))}


 */



/* DISEÑO DEL ALGORITMO:
	--- Detalla aquí el proceso seguido para diseñar el
	--- algoritmo

	PASO 1. Variables adicionales (aparte de los parámetros y el resultado)
	int i = 0=>Para el principio de la ventana
	f = 0 => Para el final de la ventana que se esta calculando
	suma = 0=> Para la suma total de la ventana que se lleva

	PASO 2. Invariante
	   (2.1) Definiciones auxiliares (si procede)
			suma(a, i, j) = SUMA u: i<=u<=j: a[u]
			ventana_completa(a, i, j, u) = 0<i && j<n -> suma(a, i-1, j) > c

	   (2.2) Invariante
			Q: {(resul = max i, j: 0<=i<=j<n && suma(a, i, j) <= c: suma(a, i, j)) && 
				 suma = suma(a, i, j-1) &&
				 ventana_completa(a, i, j, u) &&
				 0<=i<=j<=n
				 }

	PASO 3. Código de inicialización, justificando que, tras
	        dicho código, se cumple el invariante
			int i = 0, f = 0, suma = 0;
			Es directo que se cumple el invatiante completo ya que 
			0<=i<=j<=n && suma = suma(a, i, j) son directas
			ventana_completa(a, i, j, u) no se cumple la condicion de que i>0 por tanto no afecta
			(resul = max i, j: 0<=i<=j<n && suma(a, i, j) <= c: suma(a, i, j)) tambien es directa ya que la suma 
			es <=c ya que c>0 y la suma entre i y j es maxima, ya que no hay ningun numero entre medias.
	
	PASO 4. Condición del bucle, código tras el bucle (si procede),
	        y justificación de que, una vez finalizado el algoritmo,
			se cumple la postcondición
			Condicion del bucle=>f < n.
			Codigo tras el bucle=> No hay.
			(resul = max i, j: 0<=i<=j<n && suma(a, i, j) <= c: suma(a, i, j))

    PASO 5. Diseño del cuerpo del bucle, justificando que dicho código
	        preserva el invariante

			CASO 1)	if (suma + a[f] <= c) {
						suma += a[f];
						--> se viola suma(a, i , j)
						f++;
						--> se reestablece suma(a, i , j)
						--> se puede violar (resul = max i, j: 0<=i<=j<n && suma(a, i, j) <= c: suma(a, i, j))
						if (suma == c)
							return true;
							-->se reestablece (resul = max i, j: 0<=i<=j<n && suma(a, i, j) <= c: suma(a, i, j))
					}
			CASO 2)	else {
						suma -= a[i];
						--> se viola suma(a, i , j)
						i++;
						--> se reestablece suma(a, i , j)
					}


	PASO 6: Expresión de cota y justificación de que el algoritmo siempre 
	        termina
			Expresion de cota=> 2n-(i+f)
			Todas las iteraciones tienen complejidad constante debido a que el cuerpo del bucle es esencialmente un "if"
			Además en todas las iteraciones aumenta o i o f.

	PASO 7: Determinación justificada de la complejidad del algoritmo
			Como todas las iteraciones son constantes, y el bucle se ejecuta un maximo de 2n veces, la complejidad es lineal.
			Por tanto, el coste del algoritmo es O(n).
*/

bool /* resul */ hay_c_tramo(int a[], int n, int c){
	/* IMPLEMENTACION */
	int i = 0, f = 0, suma = 0;
	
	while (f < n) {
		if (suma + a[f] <= c) {
			suma += a[f];
			f++;
			if (suma == c)
				return true;
		}
		else {
			suma -= a[i];
			i++;
		}
	}
	return false;
}	


/**** PROGRAMA DE PRUEBA: NO MODIFICAR ****/


const static int MAX_ELEMS=1000000;
bool ejecuta_caso() {
  	static int a[MAX_ELEMS];
	int n;
	cin >> n;
	if (n == -1) return false;
	else {
      for (int i=0; i < n; i++) {
		  cin >> a[i];
	  }
	  int c;
	  cin >> c;
	  if (hay_c_tramo(a,n,c)) {
		  cout << "SI" << endl;
	  }
	  else {
	      cout << "NO" << endl;
	  }	  
      return true;	  
	}
}

int main() {
	while(ejecuta_caso());
}
