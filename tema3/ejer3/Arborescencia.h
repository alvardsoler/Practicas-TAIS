/*
* File:   Arborescencia.h
* Author: Samuel Lapuente Jiménez y Alvar David Soler Rus
*
* Created on 13 de noviembre de 2015, 14:12
*/
#include "GrafoDirigido.h"

#ifndef ARBOLBIPARTITO_H
#define	ARBOLBIPARTITO_H

class Arborescencia {
private:
	
	int raiz;
	std::vector<bool> _visited;
	std::vector<bool> _reacheable;
	

	int encontrarRaiz(GrafoDirigido const &grafo){
		for (size_t i = 0; i < grafo.V(); ++i){
			for (auto w : grafo.adj(i)) {
				_visited[w] = true;
			}
		}
		int r = -1;
		for (size_t i = 0; i < _visited.size(); ++i){
			if (!_visited[i] && r == -1) r = i;
			else if (!_visited[i] && r != -1) return -1;
		}
		return r;

	}
	bool visitar(GrafoDirigido const &grafo, size_t indx){
		for (auto w : grafo.adj(indx)) {
			if (_reacheable[w]) {
				return false;
			}
			else{
				_reacheable[w] = true;
				visitar(grafo, w);
			}
		}
		return true;
	}

	int resuelve(GrafoDirigido const &g) {
		int r = encontrarRaiz(g);
		if (r == -1) return -1;
		_reacheable[r] = true;
		if (visitar(g, r)) {
			for (size_t indx = 0; indx < _reacheable.size(); ++indx)
				if (!_reacheable[indx]) return -1;
			return r;
		}
		else return -1;		
	}
public:

	Arborescencia(GrafoDirigido const &g) : raiz(-1), _visited(g.V(), false), _reacheable(g.V(), false){
		raiz =  resuelve(g);
	};

	int getRaiz() {
		return raiz;
	};
};

#endif	/* ARBOLBIPARTITO_H */