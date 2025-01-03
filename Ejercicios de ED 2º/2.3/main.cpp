#include "cola.h"
#include <iostream>
using namespace std;


bool ejecuta_caso() {
	Cola<int> cola;
	int v;
	if (cin >> v) {
	   while (v != -1) {
		  cola.pon(v);
		  cin >> v;
	   }
	   int pos;
	   cin >> pos;
	   try {              
			cola.llevarAlPrincipio(pos);
			cola.imprime();
		}
		catch (EPosicionInvalida) {
			cout << "POSICION_INVALIDA" << endl;
		}
	   return true;
	}
	else return false;
}

int main() {
	while (ejecuta_caso()); 
}