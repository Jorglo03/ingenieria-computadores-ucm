/*
 * Implementación de grafos no dirigidos valorados
 * Copyright (c) 2020  Alberto Verdejo
 * Modificado por 2023 Ignacio Fábregas
 */


#include <iostream>
#include <vector>
#include "PriorityQueue.h"
#include "ConjuntoDisjunto.h"
#include "GrafoValorado.h"

using namespace std;

template <typename Valor>
class ARM_Kruskal {
private:
    std::vector<Arista<Valor>> _ARM;
    Valor coste;
    bool es_posible;
public:
    Valor costeARM() const {
        return coste;
    }
    bool posible() const {
        return es_posible;
    }

    ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0), es_posible(false){
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a); 
                coste += a.valor();
                if (_ARM.size() == g.V() - 1) {
                    break;
                }
            }
        }
        if (_ARM.size() == g.V() - 1) {
            es_posible = true;
        }

    }
};
