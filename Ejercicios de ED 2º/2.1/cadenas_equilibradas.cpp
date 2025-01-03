#include <iostream>
#include <string>
#include "pila.h"

using namespace std;



bool esEquilibrada(const string& cadena) {
    Pila<char> pila;

    for (char letra : cadena) {
        if (letra == '(' || letra == '[' || letra == '{') {
            pila.apila(letra);
        }
        else if (letra == ')'|| letra == ']' || letra == '}') {
            if (!pila.esVacia()) {
                if (letra == ')') {
                    if (pila.cima() == '(') {
                        pila.desapila();
                    }
                    else
                        return false;
                }
                else if (letra == ']') {
                    if (pila.cima() == '[') {
                        pila.desapila();
                    }
                    else
                        return false;
                }
                else if (letra == '}') {
                    if (pila.cima() == '{') {
                        pila.desapila();
                    }
                    else
                        return false;
                }
            }
            else
                return false;
        }
    }
       
    if (pila.esVacia())
        return true;
    else
        return false;
}


int main() {
    string cadena;
    while (getline(cin, cadena)) {
        if (esEquilibrada(cadena))
            cout << "EQUILIBRADA" << endl;
        else
            cout << "NO_EQUILIBRADA" << endl;
    }
    return 0;
}