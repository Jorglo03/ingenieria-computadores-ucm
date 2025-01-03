// Autor/a: Jorge López Carrión
// email: jorglo03@ucm.es
// Compilador y S.O. utilizado: C++ y Windows
// Nombre del problema: Diversión con matrices. Parte 1
// Comentario general sobre la solución
// explicando como se resuelve el problema:Se lee la matriz del archivo y, dependiendo de la instruccion que se pida
// se recurre a una funcion if concreta, para efectuar los cambios. Finalmente se imprime la matriz en el archivo

#include <iostream>
#include <fstream>
#include <string>
// Introduce más librerías si son necesarias
using namespace std;

const int MAX = 20;

typedef int tMatriz[MAX][MAX];



void resolver(tMatriz datos);
bool resuelveCaso();

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}


// función que resuelve el problema
void resolver(tMatriz datos, int filas, int columnas) {

    for (int i = 0; i < filas; i++) {           //Se imprime en el archivo la matriz
        for (int j = 0; j < columnas; j++) {
            cout << datos[i][j];
            if (j != columnas - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << "---" << endl;

}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int filas, columnas, instrucciones, cambio1, cambio2, insertar_cambio, cambio_aux1, cambio_aux2, cambio_aux1_2, cambio_aux2_2, cambio_aux1_3, cambio_aux2_3;
    tMatriz matriz, matriz_aux;
    string transformaciones;

    cin >> filas;
    cin >> columnas;
    if ((filas != 0) && (columnas != 0)) {      //Se comprueba que no se el centinela
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                cin >> matriz[i][j];                    //Se lee toda la matriz y se guarda
            }
        }

        cin >> instrucciones;

        for (int i = 0; i < instrucciones; i++) {
            cin >> transformaciones;                //Dependiendo de la transformacion que sea, se realiza una u otra
            if (transformaciones == "columnas") {
                cin >> cambio1;
                cin >> cambio2; 
                for (int i = 0; i < filas; i++) {           //Se intercambian las columnas ayudandonos de una matriz auxiliar
                    matriz_aux[i][0] = matriz[i][cambio1 - 1];
                    matriz[i][cambio1 - 1] = matriz[i][cambio2 - 1];
                    matriz[i][cambio2 - 1] = matriz_aux[i][0];
                }
            }
            else if (transformaciones == "filas") {
                cin >> cambio1;                             //Se intercambian las filas ayudandonos de una matriz auxiliar
                cin >> cambio2;
                for (int i = 0; i < columnas; i++) {
                    matriz_aux[0][i] = matriz[cambio1 - 1][i];
                    matriz[cambio1 - 1][i] = matriz[cambio2 - 1][i];
                    matriz[cambio2 - 1][i] = matriz_aux[0][i];
                }
            }
            else if (transformaciones == "cruz") {
                cin >> cambio1;
                cin >> cambio2;
                cin >> insertar_cambio;             //Se guarda la fila y columna del elemento dado para cambiar sus diagonales
                cambio1--;
                cambio2--;
                cambio_aux1 = cambio1;
                cambio_aux2 = cambio2;
                cambio_aux1_2 = cambio1;
                cambio_aux2_2 = cambio2;
                cambio_aux1_3 = cambio1;
                cambio_aux2_3 = cambio2;
                //Se van recorriendo todas las diagonales del elemento y se va cambiando al numero dado

                while ((cambio1 >= 0 && cambio1 < filas) && (cambio2 >= 0 && cambio2 < columnas)) {
                    matriz[cambio1][cambio2] = insertar_cambio;
                    cambio1++;
                    cambio2++;      
                }
                while ((cambio_aux1 >= 0 && cambio_aux1 < filas) && (cambio_aux2 >= 0 && cambio_aux2 < columnas)) {
                    matriz[cambio_aux1][cambio_aux2] = insertar_cambio;
                    cambio_aux1++;
                    cambio_aux2--;
                }
                while ((cambio_aux1_2 >= 0 && cambio_aux1_2 < filas) && (cambio_aux2_2 >= 0 && cambio_aux2_2 < columnas)) {
                    matriz[cambio_aux1_2][cambio_aux2_2] = insertar_cambio;
                    cambio_aux1_2--;
                    cambio_aux2_2--;
                }
                while ((cambio_aux1_3 >= 0 && cambio_aux1_3 < filas) && (cambio_aux2_3 >= 0 && cambio_aux2_3 < columnas)) {
                    matriz[cambio_aux1_3][cambio_aux2_3] = insertar_cambio;
                    cambio_aux1_3--;
                    cambio_aux2_3++;
                }
            }
        }
    }
    else if ((filas == 0) && (columnas == 0))       //centinela
        return false;

    resolver(matriz, filas, columnas);          

    return true;
}
