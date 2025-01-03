#include <iostream>
#include "cola.h"

using namespace std;

unsigned int afortunado(unsigned int n, unsigned int m) { //n>=1  m>=2 
	Cola<int> cola;
	int num = n, ind = 1;

	if (n != 1) {
		for (unsigned int i = 1; i <= n; i++) {
			cola.pon(i);
		}

		while (num != 1) {
			if(ind % m == 0){
				cola.quita();
				num--;
			}
			else {
				cola.pon(cola.primero());
				cola.quita();
			}
			ind++;
		}
	}
	else {
		return n;
	}

	return cola.primero();
}


int main() {
	int n, m;
	while ((cin >> n)) {
		cin >> m;
		cout << afortunado(n, m) << endl;
	}
	return 0;
}