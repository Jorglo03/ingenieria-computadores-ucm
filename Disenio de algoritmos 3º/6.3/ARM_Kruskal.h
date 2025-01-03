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
	bool recorrido_entero;

public:
	
	ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0), recorrido_entero(false) {
		PriorityQueue<Arista<Valor>> pq(g.aristas());
		ConjuntosDisjuntos cjtos(g.V());
		while (!pq.empty()) {
			Arista<Valor> a = pq.top();
			pq.pop();
			int v = a.uno(), w = a.otro(v);
			if (!cjtos.unidos(v, w)) {
				cjtos.unir(v, w);
				_ARM.push_back(a);
				coste += a.valor();
				if (_ARM.size() == g.V() - 1)
					break;
			}
		}
		if (g.V() - 1 == _ARM.size()) {
			recorrido_entero = true;
		}
	}

	Valor costeARM() const {
		return coste;
	}

	vector<Arista<Valor>> const& ARM() const {
		return _ARM;
	}
	
	int recorrido_entero_funct() {
		return recorrido_entero;
	}

};