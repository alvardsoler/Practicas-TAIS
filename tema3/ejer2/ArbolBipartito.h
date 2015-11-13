/* 
 * File:   ArbolBipartito.h
 * Author: furia
 *
 * Created on 13 de noviembre de 2015, 14:12
 */
#include "Grafo.h"

#ifndef ARBOLBIPARTITO_H
#define	ARBOLBIPARTITO_H

struct Nodo {
    bool visitado;
    int idConjunto;
};

class ArbolBipartito {
private:
    Grafo grafo;
    bool bipartito;    
    std::vector<bool> _visited;
    std::vector<bool> _colors;

    void resuelve() {
	bipartito = resuelve(0, false);
    }

    bool resuelve(size_t v, bool colorPadre) {
	
	_visited[v] = true;
	_colors[v] = !colorPadre;
	for (auto w : grafo.adj(v)) {
	    if (!_visited[w]) {
		if (!resuelve(w, !colorPadre)) return false;
	    } else if (_colors[w] == _colors[v]) return false;
	}
	return true;
    }
public:

    ArbolBipartito(Grafo g) : grafo(g), bipartito(false),_visited(g.V(), false), _colors(g.V(), false) {
	resuelve();
    };

    bool esBipartito() {
	return bipartito;
    };
};

#endif	/* ARBOLBIPARTITO_H */

