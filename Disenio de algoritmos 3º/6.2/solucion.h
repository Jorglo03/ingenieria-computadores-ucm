/*
 * Implementación de grafos no dirigidos valorados
 * Copyright (c) 2020  Alberto Verdejo
 * Modificado por 2023 Ignacio Fábregas
 */

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include "GrafoValorado.h"

using namespace std;

class solucion {
public:
        
    solucion(GrafoValorado<int> g, int origen, int ancho1): ancho(ancho1), visit(g.V(), false){
        dfs(g, origen, ancho1);
    }

    void dfs(GrafoValorado<int> const& G, int v, int umbral) {
        visit[v] = true;
        for (auto a : G.ady(v)) {
            if (a.valor() >= umbral) {
                int w = a.otro(v);
                if (!visit[w]) {
                    dfs(G, w, ancho);
                }
            }
        }

    }

    bool llega(int destino) {
        return visit[destino];
    }

private:
    std::vector<bool> visit;
    int ancho;
};