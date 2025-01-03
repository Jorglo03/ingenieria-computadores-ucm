/*
 * Implementación de grafos no dirigidos valorados
 * Copyright (c) 2020  Alberto Verdejo
 * Modificado por 2023 Ignacio Fábregas
 */


#include <iostream>
#include <vector>
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"
#include "GrafoValorado.h"

using namespace std;

template <typename Valor>
class Solucion {
public:

   
    Solucion(GrafoValorado<Valor> const& g) : coste(0), termina(false) {
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top();
            pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a); 
                coste = a.valor();
                if (_ARM.size() == g.V() - 1) break;
            }
        }
        if (_ARM.size() == g.V() - 1) {
            termina = true;
        }
    }

    bool func_termina() const {
        return termina;
    }
    Valor costeARM() const {
        return coste;
    }
    
private:
    vector<Arista<Valor>> _ARM;
    Valor coste;
    bool termina;
};
