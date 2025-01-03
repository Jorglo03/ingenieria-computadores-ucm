/*
 * Implementación de grafos dirigidos (digrafos).
 * Copyright (c) 2020  Alberto Verdejo
 *
 */

#include <iostream>
#include <stdexcept>
#include <vector>
#include "Digrafo.h"

class Solucion {

   

public:

    /** Crea un grafo dirigido con V vértices */
    Solucion(Digrafo const& g) : visit(g.V(), false), ant(g.V()),
        apilado(g.V(), false), hayciclo(false) {
        dfs_ciclo(g, 0);
    }

    bool hayCiclo() const{
        return hayciclo;
    }

    bool termina() {
        return visit[visit.size() - 1];
    }

private:

    
    void dfs_ciclo(Digrafo const& g, int v) {
        apilado[v] = true;
        visit[v] = true;
        for (int w : g.ady(v)) {
            if (!visit[w]) { // encontrado un nuevo vértice, seguimos
                ant[w] = v;
                dfs_ciclo(g, w);
            }
            else if (apilado[w]) { // hemos detectado un ciclo
                hayciclo = true;
            }
        }
        apilado[v] = false;
    }

    std::vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs?
    std::vector<int> ant; // ant[v] = vértice anterior en el camino a v
    std::vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
    bool hayciclo;

};
