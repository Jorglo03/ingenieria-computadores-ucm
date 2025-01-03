/*
NOMBRES Y APELLIDOS DE LOS MIEMBROS DEL GRUPO QUE HAN REALIZADO LA PRACTICA:
Jorge López Carrión.

Si alguno de los miembros del grupo no ha realizado la práctica, indicarlo aquí, junto con el motivo:
David Cendejas Rodriguez no ha realizado la practica.

*/

#include<iostream>

using namespace std;


/* Representacion de los personajes */
typedef enum {PRINCESA,CABALLERO,DRAGON} tPersonaje;


bool ejecuta_caso();
void es_divertida_aux(tPersonaje personajes[], int i, int j, bool& resul, int& dragones, int& caballeros, int& princesas);
bool es_divertida(tPersonaje personajes[], int n);


/*
(1) ESPECIFICACION:
P:{0<=n<=tan(personajes) && PARATODO i: 0<=i<n:a[i] = 0 || a[i] = 1 || a[i] = 2}

Q:{{resul=es_divertido(a,0,n-1)}
	es_divertido: (j-i)+1<2 || ((j-i)+1>=2 && es_divertido(personajes,i,(i+j)/2 – 1) && es_divertido(personajes,(i+j)/2 + 1, j) &&
	((dragones_izq > caballeros_der) && (personajes[m] == CABALLERO))
	|| ((caballeros_der == dragones_izq) && (personajes[m] == PRINCESA))
	|| ((caballeros_der > dragones_izq) && (((personajes[m] == DRAGON) && (princesas) > 0) || (personajes[m] == PRINCESA) && (princesas) == 0)))

(2) GENERALIZACION (EN CASO DE QUE PROCEDA), Y SU ESPECIFICACION
Necesitamos saber el tramo que estamos analizando: parámetros de entrada i (comienzo del tramo) y j (fin del tramo).
Además de si el tramo es o no divertido (parámetro de salida resul) necesitamos saber también cuál es el num de caballeros, dragones, y princesas
del tramo (parámetros de salida dragones, caballeros y princesas).
P: {0<i<=j<=n}
Q: {resul = es_divertido(personajes,i,j) &&  (resul -> ((dragones_izq > caballeros_der) && (personajes[m] == CABALLERO))
											|| ((caballeros_der == dragones_izq) && (personajes[m] == PRINCESA))
											|| ((caballeros_der > dragones_izq) && (((personajes[m] == DRAGON) && (princesas) > 0) || (personajes[m] == PRINCESA) && (princesas) == 0)))}

(3) DISEÑO
CASOS BASE:
Longitud del tramo igual a 0:j - i + 1 == 0
	Se inicializan los valores de todos los personajes
	resul = true, ya que cualquier tramo con longitud <2 es divertido.
Longitud del tramo igual a 1: i == j
	Se inicializan los valores de todos los personajes
	resul = true, ya que cualquier tramo con longitud <2 es divertido.
	Dependiendo de que personaje sea el que hay en el tramo, se actualiza la variable correspondiente a ese personaje
CASOS RECURSIVOS:
	Sea m= (i+j)/2, y supongamos resuelto el problema para a[i..m) (es decir, supongamos hecho:
	es_divertida_aux(personajes, i, m - 1, resul_izq, dragones_izq, caballeros_izq, princesas_izq)
	Si resul_izq = false, podemos afirmar directamente resul = false, puesto que la mitad inferior no es divertida.
	En otro caso (resul_izq = true), supongamos resuelto también el problema para el tramo superior a(m..j] (es decir, supongamos hecho:
	es_divertida_aux(personajes, m + 1, j, resul_der, dragones_der, caballeros_der, princesas_der)
	o Si resul_der = false, podemos afirmar resul = false, puesto que la mitad superior no es divertida.
	o En otro caso, para que el tramo sea divertida:
	resul = ((dragones_izq > caballeros_der) && (personajes[m] == CABALLERO))
	|| ((caballeros_der == dragones_izq) && (personajes[m] == PRINCESA))
	|| ((caballeros_der > dragones_izq) && (((personajes[m] == DRAGON) && (princesas) > 0) || (personajes[m] == PRINCESA) && (princesas) == 0)).
	si resul = true, entonces se suman el total de cada personaje y se añade el personaje del medio, el cual esta en la posicion personajes[m] (m)

(4) TERMINACIÓN: 
Una cota de este algoritmo es (j-i)+1

(5) IMPLEMENTACION POR INMERSION DEL ALGORITMO, SI PROCEDE:
Si se resuelve el problema para a[0..n), es decir, si suponemos hecho:
es_divertida_aux(personajes, 0, n - 1, resul, dragones, caballeros, princesas) la solución será resul.

(6) DETERMINACION DEL COSTE DEL ALGORITMO EN EL PEOR CASO:
Complejidad, en el peor caso, de es_divertida_aux
Tamaño del problema: longitud l = (j-i)+1 del tramo
Recurrencias:
T(1) = c0
T(2) = c1
T(l) = c3 + 2 T(l/2)
k=0, a=2 > b^(k) = 2^(0) = 1. Por tanto, T(l) está en O(l^(log b (a)) = O(l^(log 2 (2)) = O(^(1)  = O(l)
Complejidad de resul: complejidad de es_divertida_aux(personajes, 0, n - 1, resul, dragones, caballeros, princesas).
En este caso, l = ((n-1)-0)+1 = n. Por tanto, el coste está en O(n)

*/

void es_divertida_aux(tPersonaje personajes[], int i, int j, bool& resul, int& dragones, int& caballeros, int& princesas) {

	if (j - i + 1 == 0) {
		dragones = 0;
		caballeros = 0;
		princesas = 0;
		resul = true;
	}
	else if (i==j) {
		dragones = 0;
		caballeros = 0;
		princesas = 0;
		resul = true;
		
		if (personajes[i] == CABALLERO) {
			caballeros++;
		}
		else if (personajes[i] == PRINCESA) {
			princesas++;
		}
		else if (personajes[i] == DRAGON) {
			dragones++;
		}
	}
	else {
		int m = (i + j) / 2;
		int dragones_izq, caballeros_izq, princesas_izq;
		bool resul_izq;
		es_divertida_aux(personajes, i, m - 1, resul_izq, dragones_izq, caballeros_izq, princesas_izq);
		if (resul_izq) {
			int dragones_der, caballeros_der, princesas_der;
			bool resul_der;
			es_divertida_aux(personajes, m + 1, j, resul_der, dragones_der, caballeros_der, princesas_der);
			if (resul_der) {
				//Las princesas se suman antes ya que la evaluacion se hace con las princesas totales
				princesas = princesas_izq + princesas_der;
				
				resul = ((dragones_izq > caballeros_der) && (personajes[m] == CABALLERO)) || ((caballeros_der == dragones_izq) && (personajes[m] == PRINCESA)) ||
				((caballeros_der > dragones_izq) && (((personajes[m] == DRAGON) && (princesas) > 0) || (personajes[m] == PRINCESA) && (princesas) == 0));
				
				if (resul) {
					dragones = dragones_izq + dragones_der;
					caballeros = caballeros_izq + caballeros_der;

					//Se calcula el personaje del medio (en la posicion m)
					if (personajes[m] == CABALLERO) {
						caballeros++;
					}
					else if (personajes[m] == PRINCESA) {
						princesas++;
					}
					else if (personajes[m] == DRAGON) {
						dragones++;
					}
				}
			} else {
				resul = false;
			}
		}
		else {
			resul = false;
		}
	}
}

bool es_divertida(tPersonaje personajes[], int n) {
	bool resul;
	int dragones = 0, caballeros = 0, princesas = 0;
	es_divertida_aux(personajes, 0, n - 1, resul, dragones, caballeros, princesas);
	return resul;
}

// NO MODIFICAR NADA A PARTIR DE AQUI

const int MAX_TAM = 1000000;
const int REPS = 500;

bool ejecuta_caso() {
  int n;
  cin >> n;
  if (n== -1) {
    return false;
  }
  else {
    static tPersonaje personajes[MAX_TAM];
	for (int i = 0; i < n; i++) {
		int p;
	    cin >> p;
		personajes[i] = tPersonaje(p);
     }
	
	if(n == MAX_TAM) {
	 for (int i=0; i < REPS; i++) {
	   es_divertida(personajes,n);
	 }
	}
	if (es_divertida(personajes,n)) {
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
  return 0;
}