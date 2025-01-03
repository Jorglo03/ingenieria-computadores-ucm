#include <iostream>
#include <vector>
#include "IndexPQ.h" // Asegúrate de incluir las bibliotecas adecuadas para IndexPQ y las clases necesarias.
#include "DigrafoValorado.h" // Asegúrate de incluir las bibliotecas adecuadas para DigrafoValorado y las clases necesarias.

using namespace std;

template <typename Valor>
class Dijkstra {
public:
    Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig), maneras_distintas(0),
        dist(g.V(), INF), ulti(g.V()), pq(g.V()), maneras(g.V(), 0) {
        dist[origen] = 0;
        pq.push(origen, 0);
        maneras[origen] = 1; // Inicializa la cantidad de formas para el nodo de inicio en 1.
        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : g.ady(v)) {
                relajar(a, g.V() - 1);
            }
        }
    }
    bool hayCamino(int v) const { return dist[v] != INF; }
    Valor distancia(int v) const { return dist[v]; }
    int maneras_func(int v) const { return maneras[v]; }

private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    int maneras_distintas;
    std::vector<Valor> dist;
    std::vector<AristaDirigida<Valor>> ulti;
    IndexPQ<Valor> pq;
    std::vector<Valor> maneras; // Contiene la cantidad de formas para cada nodo.

    void relajar(AristaDirigida<Valor> a, int colegio_posicion) {
        int v = a.desde(), w = a.hasta();

        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            maneras[w] = maneras[v]; // Actualiza la cantidad de formas al nodo w.
            ulti[w] = a;
            pq.update(w, dist[w]);
        }
        else if (dist[w] == dist[v] + a.valor()) {
            maneras[w] += maneras[v]; // Agrega la cantidad de formas al nodo w.
        }

    }
};
