#include <iostream>

using namespace std;

const int TMAX = 2000000;  // No habr� vectores de m�s de dos millones de elementos


/*

PRECONDICION DE LA FUNCION:
  ---Escribe aqu� la precondici�n de la funci�n.
  P (es equivalente a) {(0<n<=tam(a)) && (k>0) && (PARATODOi:0<=i<n:a[i]>0 && a[i] <=k)}
*/

int llena_mochila(const int a[], int n, int k);

/*
POSTCONDICION DE LA FUNCION:
  -- Escribe aqu� la postcondici�n de la funci�n. Para referirte
  -- al resultado puedes usar la pseudovariable 'resul'
  Q(es equivalente a) {res = max i,j: 0<=i<=j<n && (SUMu:i<=u<=j:a[u])<=k: (j-i)+1}


 */


 /*
 DISE�O DEL ALGORITMO:

 Paso 1. Variables
	 Hay una variable para recorrer el array "i",otra variable para calcular la suma de los pesos, "num_elementos" para
	 guardar el resultado total, "num_aux" para guardar los reusltados preovisionales mientras se va recorriendo el array,
	 y num, para ir quitando pesos a la suma total.

 Paso 2. Invariante
	INV (es equivalente a) {(0<i<=n) && max k,j: 0<=k<=j<i && (SUMu:k<=u<=j:a[u])<=k: (j-k)+1}

 Paso 3. Inicializaci�n
	Se inicializa i = 1, ya que suma = a[0], por lo que no haria falta recorrer la primera posicion, num_aux = 1, 
	ya que cualquier cantidad de elementos que se lean tendra minimo un elemento,y lo mismo para num_elementos, y num = 0, 
	ya que empezaremos eliminando carga desde a[0], ya que recorremos el array de 0 a n-1.
 Paso 4. Condici�n del bucle, y c�digo tras el bucle.
	El bucle iterara mientras i<n, es decir, mientras aun haya valores que considerar

 Paso 5. Cuerpo del bucle
	El bucle comienza con i=1, y la suma = a[0], por lo que el primer elemento no habra que recorrerlo y comenzaremos en el
	segundo.Comenzaremos sumando el peso del elemento y añadiendo un elemento a la lista auxiliar. A continuacion diferenciaremos
	dos posibilidades, si suma>k, que restaremos el primer elemento que hayamos sumado , restaremos uno a la lista auxiliar y
	sumaremos uno a num, para tener el siguiente elemento listo para eliminar si es necesario.
	El otro caso es si suma <=k, donde comprobaremos si num_aux >= num_elementos, y si es cierto guardaremos la lista auxiliar
	en la definitiva, la cual sera la que contenga el resultado.

 Paso 6. Justificaci�n de que el algoritmo siempre termina.
	Terminación. En cada iteración incrementamos i. Por tanto, podemos tomar como expresión de cota n – i.


 Paso 7. Complejidad:
	Hay un factor de complejidad (1) debido a la inicialización de variables, devolución del resultado.
	En el peor caso el bucle realiza n iteraciones.
	El coste de ejecutar el cuerpo del bucle es constante.
	Por tanto, la complejidad del bucle está en (n).
	Por tanto, factor de complejidad (1), más factor de complejidad (n) -> complejidad resultante: (n)
 */

int llena_mochila(const int a[], int n, int k) {
	int i = 1 , suma = a[0], num_aux = 1, num_elementos = 1, num=0; 

	while (i < n) {
		suma += a[i];
		num_aux++;
		if (suma > k) {
			suma -= a[num];
			num_aux--;
			num++;
		}
		else {
			if (num_aux >= num_elementos) {
				num_elementos = num_aux;
			}
		}
		i++;
	}

	return num_elementos;
}


/* CODIGO PARA LEER Y EJECUTAR LOS CASOS DE PRUEBA */

void lee_vector(int a[], int& n) {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
}

int main() {
	static int a[TMAX];
	int n;
	do {
		lee_vector(a, n);
		if (n >= 0) {
			int k;
			cin >> k;
			cout << llena_mochila(a, n, k) << endl;
		}
	} while (n != -1);
}