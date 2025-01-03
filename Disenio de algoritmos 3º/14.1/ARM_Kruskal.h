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


template <typename Valor>
class ARM_Kruskal {
private:
    std::vector<Arista<Valor>> _ARM;
    Valor coste;
    GrafoValorado<Valor> g;
public:
    Valor costeARM() const {
        return coste;
    }
    bool posible() const {
        return _ARM.size() == g.V() - 1;
    }

    
    ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0) , g(g){
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a); 
                if (a.valor() > coste) {
                    coste = a.valor();
                }
                if (_ARM.size() == g.V() - 1) {
                    break;
                }
            }
        }
    }
};
