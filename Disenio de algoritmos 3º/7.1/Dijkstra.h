#include <iostream>
#include <vector>
#include "IndexPQ.h"
#include "DigrafoValorado.h"

using namespace std;

template <typename Valor>
class Dijkstra {
public:
	Dijkstra(DigrafoValorado<Valor> const& g, int orig, vector<Valor> cargas) : origen(orig),
		dist(g.V(), INF), cargas(cargas), ulti(g.V()), pq(g.V()) {
		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a, cargas);
		}
	}
	bool hayCamino(int v) const { return dist[v] != INF; }
	Valor distancia(int v) const { return dist[v]; }

private:
	const Valor INF = std::numeric_limits<Valor>::max();
	int origen;
	std::vector<Valor> dist;
	std::vector<AristaDirigida<Valor>> ulti;
	IndexPQ<Valor> pq;
	std::vector<Valor> cargas;

	void relajar(AristaDirigida<Valor> a, vector<Valor> cargas) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor() + cargas[w]) {
			dist[w] = dist[v] + a.valor() + cargas[w]; ulti[w] = a;
			pq.update(w, dist[w] + cargas[w]);
		}
	}
};