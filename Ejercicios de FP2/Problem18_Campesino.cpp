// Autor/a: Jorge López Carrión
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado: Visual Studio 2019 y Windows
// Nombre del problema: Multiplicacion del campesino egipcio
/* Comentario general sobre la solución explicando como se resuelve el problema: Se lee el numero de casos y en cada caso los dos numeros
a multiplicar. A continuacion, se a la funcion que resuelve el problea, la cual se se cumplen unos requisitos, se llama a sí misma
de manera recursiva. Finalmente se muestra el resultado de la multiplicacion de cada par de numeros en una linea.*/

#include <iostream>
#include <fstream>

using namespace std;


void resuelveCaso();            //Se declaran los prototipos de las funciones
long long int resolver(long long int a, long long int b);

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("datos.in");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
   std::ofstream out("datos.out");
   auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
   
   int numCasos;
   std::cin >> numCasos;
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   std::cout.rdbuf(coutbuf);
   system("PAUSE");
#endif
   return 0;
}

long long int resolver(long long int a, long long int b) {      //Funcion que resuelve el problema
    long long int valor = 0;

    if (b == 0) {                 //Si alguno de los numeros es 0, el resultado es 0
        valor = 0;
    }
    else if (b == 1) {            //Si alguno de los numeros es 1, el resultado es el otro numero
        valor = a;
    }
    else if (b % 2 == 0 && b > 1) {         //Si b es par y mayor que 0, se llama de manera recursiva a la funcion
        valor = resolver(2 * a, b / 2);
    }
    else if(b % 2 == 1) {                   //Si b es par y mayor que 0, se llama de manera recursiva a la funcion 
        valor = resolver(2 * a, b / 2) + a;
    }

    return valor;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    long long int a, b;
    long long int valor;

    cin >> a >> b;                      //Se leen los dos numeros
    valor = resolver(a, b);             //Se resuelve la multiplicacion
    cout << valor << endl;              //Se muestra el resultado
}
