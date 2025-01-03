/*
NOMBRES Y APELLIDOS DE LOS MIEMBROS DEL GRUPO QUE HAN REALIZADO LA PRACTICA:

Jorge López Carrión.

Si alguno de los miembros del grupo no ha realizado la práctica, indicarlo aquí, junto con el motivo:

David Cendejas Rodriguez ha faltado.

*/

#include <iostream>

using namespace std;


/*
(1) ESPECIFICACION
Etapas = n
Repostajes = c
P (es equivalente a) {0<=n<=tam(etapas) && 0<=c && (PARATODO i: 0<=i<n: etapas[i]>0}
Q (es equivalente a) {EXISTE j: 0<=j<n : (EXISTE k:j<=k<n: (SUMA i: j<=i<=k: etapas[i]))}

(2) GENERALIZACION (EN CASO DE QUE PROCEDA), Y SU ESPECIFICACION
Se necesita buscar, al comienzo, entre la mayor suma (la suma de todos) y 0, y luego ir buscando en tramos mas pequeños mediante
divide y venceras, por lo tanto necesitamos generalizar.
int min_capacidad_aux(int etapas[], int n, int repostajes_permitidos, int result, int suma_tot).
int etapas[] el array con todos los elementos, int n, el numero de elementos del array, int repostajes_permitidos el numero
de repostajes permitidos que se pueden hacer como maximo,int result que es el numero minimo, que terminara siendo el resultado final
e int suma_tot, que comienza siendo la suma de todos los numeros (suma al cual siempre va a ser >= que el resultado) y después va 
disminuyendo hasta llegar al mismo valor que result.
P (es equivalente a) {suma_tot>=(SUMA i:0<=i<n:etapas[i]) && 0<=result<=suma_tot}
Q (es equivalente a) {EXISTE j: 0<=j<n : (EXISTE k:j<=k<n: (SUMA i: j<=i<=k: etapas[i]))}

(3) DISEÑO (CASOS)
int suma(int etapas[], int i, int f): (haya la suma del array recursivamente mediante divide y venceras)
Caso base. Si i == f, entonces estamos buscando en un tramo con un unico elemento, por tanto es el que buscamos y lo retornamos,
sino, hayamos la mitad y llamamos recursivamente  ala funcion para que calcule la suma del tramo de la derecha y el de la izquierda
y simplemente, hacemos la suma entre esos dos tramos obtenidos para obtener el resultado.

min_capacidad_aux(int etapas[], int n, int repostajes_permitidos, int result, int suma_tot):
Caso base. result == suma_tot, se devuelve result , ya que ya habriamos obtenido el resultado al no quedar más llamadas recurivas que hacer,
sino, se haya la media de result y suma_tot, y si es posible con el combustible hallado en la variable media,se llama recursivamente
a la funcion desde el mismo result hasta media, si la funcion factible es false, se llama recursivamente a la funcion desde media+1
hasta la misma variable final/superior.

int factible(int etapas[], int n, int repostajes_permitidos, int combustible, int combustible_acumulado, int repostajes_acumulados, int i)
Caso base. Si i==n, no quedan mas llamadas recursivas para hacer, por lo que habriamos hecho todas las comprobaciones y ninguna
habria devuelto false, por lo que devolvemos true,
sino si etapas[i] > combustible, entonces necesitariamos mas combustible, por lo que no vale (false), acumulamos el combustible 
de esa etapa. Si hay que hacer una parada (combustible_acumulado > combustible),se reinicia el combustible acumulado a la etapa en
la que nos encontramos y sumamos un repostaje mas, ya que hemos tenido que parar, si llevamos mas repostajes de los que
tenemos permitidos devolvemos false, sino hacemos la llamada recursiva a factible.

(4) TERMINACIÓN
Una expresión de cota es (suma_tot + result) / 2.

(5) IMPLEMENTACION POR INMERSION DEL ALGORITMO, SI PROCEDE
int min_capacidad_aux(int etapas[], int n, int repostajes_permitidos, int result, int suma_tot)
La variable result debe comenzar con el valor 0, mientras que suma_tot con un valor mayor o igual que el resultado, como puede
ser la suma de todos.
min_capacidad_aux(etapas, n, repostajes_permitidos, 0, suma_tot);

(6) DETERMINACION DEL COSTE DEL ALGORITMO EN EL PEOR CASO
En el peor caso es
T{T(0) = C0
  T(1) = w(n) + 2(n/2) siendo w(n) de coste O(n)}

  Por tanto el coste en el peor caso es de O(n*log n)
*/

int suma(int etapas[], int i, int f) { //Suma de un array con divide y venceras

	if (i == f) {
		return etapas[f];
	}
	else {
		int mitad = (f+i) / 2;
		int izq = suma(etapas, i, mitad);
		int der = suma(etapas, mitad+1, f);
		return izq + der;
	}
}

int factible(int etapas[], int n, int repostajes_permitidos, int combustible, int combustible_acumulado, int repostajes_acumulados, int i) {

	if (i == n) {		//Si se han hecho todas las llamadas recursivas ya
		return true;
	}
	else {
		if (etapas[i] > combustible) {
			return false;
		}
		combustible_acumulado += etapas[i];
		if (combustible_acumulado > combustible) {		//Si hay que hacer una parada
			combustible_acumulado = etapas[i];
			repostajes_acumulados++;
			if (repostajes_acumulados > repostajes_permitidos) {
				return false;
			}
		}
		return factible(etapas, n, repostajes_permitidos, combustible, combustible_acumulado, repostajes_acumulados, i + 1);
	}
}

int min_capacidad_aux(int etapas[], int n, int repostajes_permitidos, int result, int suma_tot) {

	if (result == suma_tot) {
		return result;
	}
	else {
		int mitad = (suma_tot + result) / 2;
		if (factible(etapas, n, repostajes_permitidos, mitad, 0, 0, 0)) {
			return min_capacidad_aux(etapas, n, repostajes_permitidos, result, mitad);
		}
		else {
			return min_capacidad_aux(etapas, n, repostajes_permitidos, mitad+1, suma_tot);
		}
	}
}

int min_capacidad(int etapas[], int n, int repostajes_permitidos) {
	int suma_tot = suma(etapas, 0, n - 1);

	return min_capacidad_aux(etapas, n, repostajes_permitidos, 0, suma_tot);
}


const int MAX_ETAPAS = 100000;


bool ejecuta_caso() {
	static int v[MAX_ETAPAS];
	int n, c;
	cin >> n;
	if (n == -1) return false;
	else {
		cin >> c;
		for (int i = 0; i < n; ++i)
			cin >> v[i];
		cout << min_capacidad(v, n, c) << endl;
		return true;
	}
}

int main() {
	while (ejecuta_caso());
	return 0;
}

