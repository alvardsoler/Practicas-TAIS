/* 
 * File:   BarroCity.h
 * Author: alvar
 *
 * Created on 26 de noviembre de 2015, 10:44
 */
#include "GrafoValorado.h"
#include "IndexPQ.h"
#include <climits>

#ifndef BARROCITY_H
#define	BARROCITY_H

class BarroCity {
private:
    int coste;
    IndexPQ<int> pq;
    std::vector<Arista<int>> edgeTo;
    std::vector<int> distTo;
    std::vector<bool> marked;

    void visitar(GrafoValorado<int> const & g, int v) {
	marked[v] = true;
	for (Arista<int> a : g.adj(v)) {
	    int w = a.otro(v);
	    if (marked[w]) continue;
	    if (a.valor() < distTo[w]) {
		edgeTo[w] = a;
		distTo[w] = a.valor();
		pq.update(w, a.valor());
	    }
	}
    };

    int resuelve(GrafoValorado<int> const & g) {
	distTo[0] = 0;
	
	pq.push(0, 0);
	int topElem;
	while (!pq.empty()) {
	    topElem = pq.top().elem;
	    pq.pop();

	    visitar(g, topElem);
	}
	int aux = 0;
	for (int i : distTo)
	    aux += i;
	return aux;
    };

public:

    BarroCity(GrafoValorado<int> const & g) : pq(g.V()), edgeTo(g.V()),
    distTo(g.V(), INT_MAX), marked(g.V(), false) {
	if (g.V() == 1) coste = 0;
	else
	    coste = resuelve(g);

    };

    int getCoste() {
	return coste;
    };


};
#endif	/* BARROCITY_H */
