#include <iostream>
#include <vector>

#include "PriorityQueue.h"
#include "GrafoValorado.h"
#include "ConjuntoDisjunto.h"

using namespace std;

template <typename Valor>
class ARM_Kruskal {
private:
	std::vector<Arista<Valor>> _ARM;
	Valor coste;
	int costeAeropuerto;
	int numAeropuertos;

public:
	
	ARM_Kruskal(GrafoValorado<Valor> const& g, int costeAeropuerto) : coste(0), costeAeropuerto(costeAeropuerto), numAeropuertos(0)	{
		PriorityQueue<Arista<Valor>> pq(g.aristas());
		ConjuntosDisjuntos cjtos(g.V());
		while (!pq.empty()) {
			Arista<Valor> a = pq.top();
			pq.pop();
			int v = a.uno(), w = a.otro(v);
			if (!cjtos.unidos(v, w)) {
				if (a.valor() < costeAeropuerto) {
					cjtos.unir(v, w);
					_ARM.push_back(a);
					coste += a.valor();
					if (_ARM.size() == g.V() - 1)
						break;
				}
				else {
					cjtos.unir(v, w);
					_ARM.push_back(a);
					numAeropuertos++;
					coste += costeAeropuerto;
					
				}
			}
		}
		numAeropuertos += cjtos.num_cjtos();
		coste += costeAeropuerto * cjtos.num_cjtos();
	}

	int numAeropuerto() {
		return numAeropuertos;
	}

	Valor costeARM() const {
		return coste;
	}

	vector<Arista<Valor>> const& ARM() const {
		return _ARM;
	}

};