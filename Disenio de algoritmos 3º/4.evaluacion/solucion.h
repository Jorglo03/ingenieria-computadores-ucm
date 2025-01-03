
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge López Carrión y Raúl Arellano Jorge
 *
 *@ </answer> */

#include <iostream>
#include "Grafo.h"  // propios o los de las estructuras de datos de clase
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class solucion{

public:

	solucion(Grafo const& g, int lucas1, int alex1, int trabajo1) :
		dist_lucas(g.V()),
		dist_alex(g.V()),
		dist_trabajo(g.V()), lucas(lucas1 - 1), alex(alex1 - 1), trabajo(trabajo1 - 1), min(INT_MAX){

		bfs(g, lucas, dist_lucas);
		bfs(g, alex, dist_alex);
		bfs(g, trabajo, dist_trabajo);

		int min_actual;
		for (int i = 0; i < g.V(); i++) {
			min_actual = dist_lucas[i] + dist_alex[i] + dist_trabajo[i];
			min = std::min(min, min_actual);
		}
	}
	// retorna el minimo de distancia del recorrido total
	int minimo() const {
		return min;
	}
	

private:
	vector<int> dist_lucas; // dist[v] = aristas en el camino lucas-v más corto
	vector<int> dist_alex; // dist[v] = aristas en el camino alex-v más corto
	vector<int> dist_trabajo; // dist[v] = aristas en el camino trabajo-v más corto
	int min;
	int lucas, alex, trabajo;


	void bfs(Grafo const& g, int num, vector<int>& dist) {
		queue<int> q;
		vector<bool> visit(g.V(), false);
		vector<int> ant(g.V());
		dist[num] = 0; visit[num] = true;
		q.push(num);
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (int w : g.ady(v)) {
				if (!visit[w]) {
					ant[w] = v; dist[w] = dist[v] + 1; visit[w] = true;
					q.push(w);
				}
			}
		}
	}
};