/*
 * File:   ManchasCrecientes.h
 * Author: Samuel Lapuente Jiménez y Alvar David Soler Rus
 *
 */

#ifndef REPARTIENDO_H
#define	REPARTIENDO_H
#include <climits>
#include "IndexPQ.h"
#include "GrafoDirigidoValorado.h"


class Repartiendo {
private:
    int esfuerzo;
    IndexPQ<int> pq;
    std::vector<AristaDirigida<int>> edgeTo;
    std::vector<int> distTo;
    std::vector<bool> marked;

    /**
     * Metodo auxiliar. Se calculan las distancias mas cortas a cada vertice 
     * adyacente a v. Coste O(|N|) siendo N los vertices adyacentes a v
     * @param g grafo
     * @param v vertice de salida
     */
    void visitar(GrafoDirigidoValorado<int> const & g, int v) {
	marked[v] = true;
	for (AristaDirigida<int> a : g.adj(v)) {
	    int w = a.to();
	    if (marked[w]) continue;
	    if (a.valor() < distTo[w]) {
		edgeTo[w] = a;
		distTo[w] = a.valor();
		pq.update(w, a.valor());
	    }
	}
    };

    /**
     * Coste O(|V*V|) ya que visitar es O(|V|) en el caso peor, y resuelve lo llama
     * V veces.
     * @param g grafo sobre el que trabajar
     * @return coste del camino
     */
    int resuelve(GrafoDirigidoValorado<int> const & g, int const & origen, int const & destino) {
	distTo[origen] = 0;
	pq.push(origen, 0);
	int topElem;
	while (!pq.empty()) {
	    topElem = pq.top().elem;
	    pq.pop();
	    if (topElem != destino)
		visitar(g, topElem);
	}
	int aux = 0;
	for (int i : distTo)
	    aux += i;
	return aux + esfuerzo;
    };
public:

    Repartiendo(GrafoDirigidoValorado<int> const & g, int const & origen, std::vector<int> const & destinos)
    : pq(g.V()), edgeTo(g.V()), distTo(g.V(), INT_MAX), marked(g.V(), false) {
	if (g.V() == 1) esfuerzo = 0;
	else {
	    for (unsigned int i = 0; i < destinos.size(); ++i) {
		esfuerzo = resuelve(g, origen, destinos[i]);
		esfuerzo = resuelve(g, destinos[i], origen);
	    }
	}

    };

    int getEsfuerzoMinimo() {
	for (int i = 0; i < marked.size(); ++i)
	    if (!marked[i]) return -1;
	return esfuerzo;
    };

};

#endif	/* REPARTIENDO_H */

