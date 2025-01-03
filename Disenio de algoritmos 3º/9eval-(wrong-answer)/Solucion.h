#include <iostream>
#include <vector>
#include <algorithm>

#include "IndexPQ.h"
#include "DigrafoValorado.h"

using namespace std;

template <typename Valor>
class Solucion {
public:
	Solucion(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
		dist(g.V(), INF), pq(g.V()) {
		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}
	vector<Valor> vect() const {
		return dist;
	}

private:
	const Valor INF = std::numeric_limits<Valor>::max();
	int origen;
	std::vector<Valor> dist;
	IndexPQ<Valor> pq;

	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor();
			pq.update(w, dist[w]);
		}
	}
};
