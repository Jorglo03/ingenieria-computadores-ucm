
#include <iostream>
using namespace std;

/*
DISE�O DEL ALGORITMO:
-- Describe con claridad, justificando las decisiones de dise�o realizadas,
-- el funcionamiento de tu algoritmo. Especifica claramente el cometido de cada
-- par�metro (en caso de que utilices una generalizaci�n), los casos base, y los
-- casos recursivos

ANALISIS DE LA COMPLEJIDAD:
-- Determina justificadamente el orden de complejidad del algoritmo diseñado.
-- Escribe y resuelve las ecuaciones de recurrencia.

*/

void es_interesante_aux(int n, int& sum_izq, int& sum_der, bool& posible);
void sum(int& total, int n);
bool es_interesante(unsigned int n);
void ejecuta_caso();

void es_interesante_aux(int n, int& sum_izq, int& sum_der, bool& posible) {
    if (n % 10 == 0 && n != 0) {
        posible = false;
    }
    if (posible && n > 0) {
        sum_izq -= (n % 10);
        sum_der += (n % 10);
        posible = sum_izq % (n % 10) == 0 && sum_der % (n % 10) == 0;
        es_interesante_aux(n / 10, sum_izq, sum_der, posible);
    }
    else if (posible && n == 0) {
        posible = true;
    }
    else if (!posible) {
        posible = false;
    }
}
void sum(int& total, int n) {
    if (n != 0) {
        total += n % 10;
        sum(total, n / 10);
    }
}
bool es_interesante(unsigned int n) {
    bool posible;
    if (n == 0) {
        return false;
    }
    else if (n < 10) {
        return true;
    }
    else {
        int sum_izq = 0;
        int sum_der = 0;
        bool posible = true;
        sum(sum_izq, n);
        es_interesante_aux(n, sum_izq, sum_der, posible);
        return posible;
    }
}

void ejecuta_caso() {
    unsigned int n;
    cin >> n;
    if (es_interesante(n)) {
        cout << "SI" << endl;
    }
    else {
        cout << "NO" << endl;
    }
}

int main() {
    unsigned int num_casos;
    cin >> num_casos;
    for (int i = 0; i < num_casos; i++) {
        ejecuta_caso();
    }
}