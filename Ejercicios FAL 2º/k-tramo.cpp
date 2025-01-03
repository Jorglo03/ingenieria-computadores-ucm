
#include <iostream>

using namespace std;


/*

PRECONDICION DE LA FUNCION:
  ---Escribe aqu� la precondici�n de la funci�n.
  P (es equivalente a) {0<=n<=tam(a) && k>0 && PARATODOi: 0<=i<n: a[i] = 0 || a[i] = 1}

*/

int tramo_mas_corto(bool a[], int n, int k);

/*
POSTCONDICION DE LA FUNCION:
  -- Escribe aqu� la postcondici�n de la funci�n. Para referirte
  -- al resultado puedes usar la pseudovariable 'resul'

  Q (es equivalente a) {resul = min i,j:0<=i<=j<n && a[i] = true && a[j] = true && (#l:i=l<=j:a[l] = true) = k: (j-i) + 1}

 */


 /*
 DISE�O DEL ALGORITMO:

 Paso 1. Variables
	Una variable i para recorrer el array, "cuenta_aux" para ir contando el numero de elementos entre true y true.
	"cuenta" para devolver el resultado de elementos como solucion, ks, para comprobar cuando ya hemos pasado por k elementos = true,
	"num" para guardar el indice del ultimo numero igual a true, cuenta_aux2 para guardar la ultima cuenta entre 'trues'.
	Dos variables booleanas:"empezar", que se pone a true cuando se encuentra el primer true, en un elemento y "comprobar",
	se pone a true cuando se llega al numero de k's elementos con valor 'true'.

 Paso 2. Invariante
	INV (es equivalente a) {min u,j:0<=u<=j<i && a[u] = true && a[j] = true && (#l:u=l<=j:a[l] = true) = k: (j-u) + 1}

 Paso 3. Inicializaci�n
	Se inicializa i = 0, para recorrer todo el array, cuenta_aux = 0 ya que la lista empieza en 0, igual que ks y cuanta_aux2.
	cuenta se inicializa en n+1, ya que si no hay ningun valor true, sera el valor que se devuelva, num = 0, ya que la primera vez
	que se encuentre a[i] == true, cuenta_aux2 debe ser i, y por ultimo las dos variables booleanas que se inciaran como false
	para que se puedan activar durante el transcurso del bucle.

 Paso 4. Condici�n del bucle, y c�digo tras el bucle.
	El bucle iterara mientras i<n, por tanto, mientras aun haya valores que considerar.
	Al terminar el bucle tenemos la postcondicion, por lo que no se necesita mas codigo

 Paso 5. Cuerpo del bucle

 Paso 6. Justificaci�n de que el algoritmo siempre termina.
	En cada iteración incrementamos i. Por tanto, podemos tomar como expresión de cota n – i.

 Paso 7. Complejidad:
	Hay un factor de complejidad (1) debido a la inicialización de variables, devolución del resultado.
	En el peor caso el bucle realiza n iteraciones.
	El coste de ejecutar el cuerpo del bucle es constante.
	Por tanto, la complejidad del bucle está en (n).
	Por tanto, factor de complejidad (1), más factor de complejidad (n) -> complejidad resultante: (n)

 */

int tramo_mas_corto(bool a[], int n, int k) {
 	int i = 0, cuenta_aux = 0, cuenta = n+1, ks = 0, num=0, cuenta_aux2 = 0;
	bool empezar = false, comprobar = false;

	while (i < n) {
		if (empezar) {
			cuenta_aux++;
		}
		if (a[i] == true) {
			cuenta_aux2 = i - num;
			num = i;
			if (!empezar)
				cuenta_aux++;
			empezar = true;
			ks++;
			if (ks == k) {
				if(cuenta > cuenta_aux || !comprobar)
					cuenta = cuenta_aux;
				ks--;
				cuenta_aux -= cuenta_aux2;
				comprobar = true;
			}
		}
		i++;
	}

	return cuenta;
}

/* CODIGO DE LECTURA Y EJECUCION DE CASOS DE PRUEBA:
   NO MODIFICAR */


void lee_caso(int& n, bool a[], int& k) {
	cin >> n;
	if (n != -1) {
		for (int i = 0; i < n; i++) {
			int elem;
			cin >> elem;
			a[i] = bool(elem);
		}
		cin >> k;
	}
}

const int MAX_TAM = 100;
int main() {
	int n;
	bool a[MAX_TAM];
	int k;
	do {
		lee_caso(n, a, k);
		if (n != -1) {
			cout << tramo_mas_corto(a, n, k) << endl;
		}
	} while (n != -1);
}

