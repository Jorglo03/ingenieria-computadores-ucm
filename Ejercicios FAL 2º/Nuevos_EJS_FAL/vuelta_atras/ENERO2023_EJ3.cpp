/*
NOMBRE Y APELLIDOS:

*/


#include <iostream>

using namespace std;

static const int MAX_MONEDAS = 100;

/* Tipo para representar los datos de entrada */
typedef struct {
  int num_monedas;     /* Número de monedas a repartir */
  int min_monedas;     /* Mínimo de monedas que debe recibir cada pirata -los dos deben
                          recibir este mínimo número de monedas */
  int valor_monedas[MAX_MONEDAS];  /* Valor de las distintas monedas a repartir */
} tEntrada;


/*
(1) ¿Cómo son las soluciones parciales viables de este problema?
Las soluciones se generan de forma que se asignan monedas a los piratas, y estan todas las monedas asignadas
hasta moneda_actual y se asignan si quedan las suficientes monedas minimas para asignar a el otro pirata de
forma que tenga minimo datos.min_monedas monedas(poda)

(2) ¿Cuándo una solución es final?
Cuando se han asignado todas las monedas y la diferencia minima es menor o igual que la anterior y mayor que 0

(3) Dada una solución viable, ¿cómo se generan nuevas soluciones viables a partir de ella?
Se comprueba si si quedan las suficientes monedas minimas para asignar a el otro pirata de
forma que tenga minimo datos.min_monedas monedas(poda), y se genera una nueva solucion viable de manera que 
se asigna la moneda moneda+1.


(4) ¿Cómo se representarán las soluciones en este problema? Describe los distintos elementos
    de información que las componen, indicando si se representan como parámetros de entrada,
	de entrada/salida (estado global), si se representan implícitamente...
	Como se trata de monedas, que son numeros enteros , se hara explicitamente, como un parametro de entrada
	indicando que moneda se esta intentando asignar, el programa dispondra de memoria para saber la moneda
	y las monedas que tiene cada pirata y cuantas quedan por asignar


(5) ¿Qué marcadores utiliza el algoritmo? Describe claramente su propósito, los elementos
    de información que los componen, así como si dichos elementos se representan como parámetros
	de entrada, de entrada/salida (estado global)... 
	(Escribir las variables utilizadas para la poda principalmente)

(6) Si el algoritmo utiliza generalización, indica como es la misma, describiendo claramente
    el propósito de cada parámetro.
	tEntrada datos => datos de entrada
	int& min_diferencia =>minima diferencia obtenida hasta el momento int& 
	veces_repetida=> las veces que se ha repetido esa minima diferencia obtenida
	int moneda_actual=>Moneda que se esta intentando asignar en el momento
	int pirata1=>valor de las monedas del pirata1
	int pirata2=>valor de las monedas del pirata2
	int monedas_pirata1=>num monedas del pirata 1
	int monedas_pirata2=>numero de monedas del pirata2

(7) Análisis de casos: casos base, casos recursivos
    CASO BASE : si se han asignado toda las monedas
        CASO1)si la diferencia entre piratas es menor que la diferencia minima obtenida hasta el momento y ademas es >0
            min_diferencia = nueva diferencia minima;
            veces_repetida = 1;
        }
        CASO2) lo mismo que el caso 1 pero si el que tiene mas valor de monedas es el pirata 1 en vez del pirata 2  
            min_diferencia = nueva diferencia minima;
            veces_repetida = 1;
        }
        CASO3) si la minima diferencia es igual que la obtenida hasta el momento
            veces_repetida++;
        }
    }
    CASO RECURSIVO
        //asigna al 1er pirata
        if //poda(si quedan las suficientes monedas minimas para asignar a el otro pirata de forma que tenga minimo datos.min_monedas monedas)
            backtracking(datos, min_diferencia, veces_repetida, moneda_actual + 1, pirata1 + datos.valor_monedas[moneda_actual], pirata2, monedas_pirata1 + 1, monedas_pirata2);

        //asigna al 2er pirata
        if  //poda(la misma poda pero para el otro pirata)
            backtracking(datos, min_diferencia, veces_repetida, moneda_actual + 1, pirata1, pirata2 + datos.valor_monedas[moneda_actual], monedas_pirata1, monedas_pirata2 + 1);
    }

(8) Si el algoritmo utiliza una generalización, describe cómo se implementa el algoritmo
    en términos de la misma (inmersión)
	Paritiendo de la moneda 0, se guarda el numero de monedas de cada pirata, el valor de esas monedas
	para cada pirata , la minima diferencia encontrada y las veces que se ha repetido y se hace la llamada
	recursiva.
*/

void backtracking(tEntrada datos, int& min_diferencia, int& veces_repetida, int moneda_actual, int pirata1, int pirata2, int monedas_pirata1, int monedas_pirata2) {

    if (moneda_actual == datos.num_monedas) {
        //if (monedas_pirata1 >= datos.min_monedas_x_pirata && monedas_pirata2 >= datos.min_monedas_x_pirata) {
        if (pirata1 - pirata2 >= 0 && pirata1 - pirata2 < min_diferencia) {
            min_diferencia = pirata1 - pirata2;
            veces_repetida = 1;
        }
        else if (pirata2 - pirata1 >= 0 && pirata2 - pirata1 < min_diferencia) {
            min_diferencia = pirata2 - pirata1;
            veces_repetida = 1;
        }
        else if (abs(pirata1 - pirata2) == min_diferencia) {
            veces_repetida++;
        }
        // }
    }
    else {
        //asigna al 1er pirata
        if (datos.num_monedas - (monedas_pirata1 + 1) >= datos.min_monedas) //poda(si quedan las suficientes monedas minimas para asignar a el otro pirata de forma que tenga minimo datos.min_monedas monedas)
            backtracking(datos, min_diferencia, veces_repetida, moneda_actual + 1, pirata1 + datos.valor_monedas[moneda_actual], pirata2, monedas_pirata1 + 1, monedas_pirata2);

        //asigna al 2er pirata
        if (datos.num_monedas - (monedas_pirata2 + 1) >= datos.min_monedas) //poda
            backtracking(datos, min_diferencia, veces_repetida, moneda_actual + 1, pirata1, pirata2 + datos.valor_monedas[moneda_actual], monedas_pirata1, monedas_pirata2 + 1);
    }

}
 
  /* - En min_dif debe devolverse la mínima diferencia que puede conseguirse.
     - En num_formas debe devolverse el número de soluciones que presentan dicha diferencia mínima.
   */	 
 void reparte(const tEntrada& entrada, int& min_dif, int& num_formas) {
	 // A IMPLEMENTAR
	 //asigna al 1er pirata
	 min_dif = 0;
	 for (int i = 0; i < entrada.num_monedas; i++) {
		 min_dif += entrada.valor_monedas[i];
	 }

	 num_formas = 0;

	 backtracking(entrada, min_dif, num_formas, 0, 0, 0, 0, 0);

 }

/**** PROGRAMA DE PRUEBA: NO MODIFICAR ****/

 bool ejecuta_caso() {
	 int num_monedas;
	 cin >> num_monedas;
	 if (num_monedas == -1) return false;
	 else {
		 tEntrada entrada;
		 entrada.num_monedas = num_monedas;
		 cin >> entrada.min_monedas;
		 for (int m = 0; m < num_monedas; m++) {
			 cin >> entrada.valor_monedas[m];
		 }
		 int min_dif;
		 int num_formas;
		 reparte(entrada, min_dif, num_formas);
		 cout << min_dif << " " << num_formas << endl;
		 return true;
	 }
 }

 int main() {
	 while (ejecuta_caso());
	 return 0;
 }