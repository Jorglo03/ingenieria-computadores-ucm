#include <iostream>
#include <vector>
#include "IndexPQ.h" // Asegúrate de incluir las bibliotecas adecuadas para IndexPQ y las clases necesarias.
#include "DigrafoValorado.h" // Asegúrate de incluir las bibliotecas adecuadas para DigrafoValorado y las clases necesarias.
#include <queue>

using namespace std;

template <typename Valor>
class Dijkstra {
public:
    Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
        dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        camino.push(origen);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    bool hayCamino(int v) const { return dist[v] != INF; }
    Valor distancia(int v) const { return dist[v]; }
    deque<AristaDirigida<Valor>> camino_final(int v) const {
        deque<AristaDirigida<Valor>> cam;
        // recuperamos el camino retrocediendo
        AristaDirigida<Valor> a;
        for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
            cam.push_front(a);
        cam.push_front(a);
        return cam;
    }

private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist;
    std::vector<AristaDirigida<Valor>> ulti;
    IndexPQ<Valor> pq;
    queue<Valor> camino;

    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();

        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor(); ulti[w] = a;
            camino.push(w);
            pq.update(w, dist[w]);
        }
    }
};