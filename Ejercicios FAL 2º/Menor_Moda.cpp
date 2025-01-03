#include <iostream>

using namespace std;

const int TMAX = 1000000;  // No habr� vectores de m�s de un mill�n de elementos



/*

PRECONDICION DE LA FUNCION:
  P (es equivalente a) {0 < n <= tam(a) && PARATODOi:0 <= i < n-1: a[i] < a[i+1]}

*/
int menor_moda(const int a[], int n);

/*
POSTCONDICION DE LA FUNCION:
  -- Escribe aqu� la postcondici�n de la funci�n. Para referirte
  -- al resultado puedes usar la pseudovariable 'resul'
  Q (es equivalente a) { resul = min i: 0<=i<n && ((# j: 0<=j<n: a[i]=a[j]) = (max j: 0<=j<n: (# k: 0<=k<n: a[j]=a[k]))): a[i] }

*/


/*
DISE�O DEL ALGORITMO:
-- Especifica cada paso del dise�o en cada apartado indicado

Paso 1. Variables
	Las variables son resultado  = 0, para guardar el numero de la menor moda, una variable i para recorrer el array,
	otra variable lon para calcular las veces que se repite el numero por el que vamos iterando, y por ultimo num_veces que 
	contiene el numero de veces que se repite la menor moda, por ultimo un bool para comprobar si seguimos en la misma moda
Paso 2. Invariante
	INV (es equivalente a) {0 < i < n && (min u: 0<=u<i && ((# j: 0<=j<i: a[u]=a[j]) = (max j: 0<=j<i: (# k: 0<=k<i: a[j]=a[k]))): a[i])}

Paso 3. Inicializaci�n
	Se inicializa resultado = a[0], la cual se supone al principio como menor moda, la variable i = 0 para recorrer todo el array
	la variable lon que se inicializa a 1 , ya que cuanta el numero de veces que hay un numero y cada numero que se lee se 
	encuentra minimo una vez en el array, y por ultimo num_veces que tambien se inicializa a 1 porque cada numero se encuentra
	minimo 1 vez. Comprobar que se inicializa en false, para luego poder comprobar si seguimos contando la lon del mismo numero


Paso 4. Condici�n del bucle, y c�digo tras el bucle
	El bucle se recorrera mientras i < n - 1, para que tenga sentido a[i+1]


Paso 5. Cuerpo del bucle
	La condición de continuación del bucle (i<n-1) garantiza que, inmediatamente antes de comenzar a ejecutar su cuerpo,
	a[i] y a[i+1] tiene sentido.
	Se diferencian dos casos, si a[i] == a[i + 1], que se restableceria lon incrementandolo en 1, y si llevamos una long mas larga
	que la guardada anteriormente, se guaradara el numero que estamos leyendo en a[i], ya que sera el resultado final,
	o si a[i] != a[i + 1], y se reestablece lon en 1 y ,se guarda la longitud de la moda que estabamos leyendo. 
	Se cambia de valor comprobar, para indicar que hemos cambiado de numero y finalmente para respetar el invariante,
	se incrementa i.

Paso 6. Justificaci�n de que el algoritmo siempre termina
	En cada iteración incrementamos i. Por tanto, podemos tomar como expresión de cota n – i+1.


Paso 7. Complejidad
	Hay un factor de complejidad (1) debido a la inicialización de variables, devolución del resultado.
	En el peor caso el bucle realiza n iteraciones.
	El coste de ejecutar el cuerpo del bucle es constante.
	Por tanto, la complejidad del bucle está en (n).
	Por tanto, factor de complejidad (1), más factor de complejidad (n) -> complejidad resultante: (n)

*/



int menor_moda(const int a[], int n) {
	int resultado = a[0], i = 0, lon = 1, num_veces = 1;
	bool comprobar = false;

	while (i < n-1) {
		if (a[i] == a[i + 1]) {
			lon++;
			if (lon > num_veces) {
				resultado = a[i];
				comprobar = true;
			}
		}
		else {
			if (comprobar) {
				num_veces = lon;
			}
			lon = 1;
			comprobar = false;
		}
		i++;
	}

	return resultado;
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
			cout << menor_moda(a, n) << endl;
		}
	} while (n != -1);
}