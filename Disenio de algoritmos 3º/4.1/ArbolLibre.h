#include "Grafo.h"
#include <vector>
using namespace std;

class ArbolLibre {

public:

	ArbolLibre(Grafo const& g) : visit(g.V(), false), ant(g.V()), ciclico(false), libre(false), repetido(g.V(), false)
	{
		dfs(g, 0);
		if (esConexo(g) && !ciclico) {
			libre = true;
		}
	}

	bool esLibre() {
		return libre;
	}

private:
	vector<bool> visit; // visit[v] = ¿hay camino de s a v?
	vector<int> ant; // ant[v] = último vértice antes de llegar a v
	vector<bool> repetido;
	bool ciclico;
	bool libre;
	int s; // vértice origen
	void dfs(Grafo const& G, int v) {
		visit[v] = true;
		repetido[v] = true;
		for (int w : G.ady(v)) {
			if (!visit[w]) {
				ant[w] = v;
				dfs(G, w);
			}
			else if(repetido[w] && ant[v] != w){
				ciclico = true;
				return;
			}
		}
		repetido[v] = false;
	}

	bool esConexo(Grafo const& g) {
		for (int i = 0; i < g.V(); i++) {
			if (!visit[i]) return false;
		}

		return true;
	}

};