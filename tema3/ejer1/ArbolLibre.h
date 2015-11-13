/* 
 * File:   ArbolLibre.h
 * Author: furia
 *
 * Created on 13 de noviembre de 2015, 13:52
 */
#include "Grafo.h"

#ifndef ARBOLLIBRE_H
#define	ARBOLLIBRE_H

class ArbolLibre {
private:
    Grafo grafo;
    bool libre;

    void resuelve() {
	std::vector<bool> _marked(grafo.V());
	size_t s = 0, count = 0;

	if (resuelve(s, count, 0, _marked)) {
	    if (count == grafo.V()) libre = true;
	    else libre = false;
	} else libre = false;
    }

        /**
     * Función recursiva para comprobar si un grafo es un Árbol libre. Se hace una especie de recorrido en anchura
     * del grafo, comprobando que no existan ciclos (_marked) y que sea conexo (count). La complejidad es
     * O(|v|) , siendo |v| el número de vértices del grafo.     
     * @param s indice del nodo
     * @param count número de nodos visitados
     * @param last ultimo nodo visitado
     * @param _marked vector para conocer si los nodos han sido visitados previamente
     * @return 
     */
    bool resuelve(size_t s, size_t &count, int const last, std::vector<bool> _marked) {
	++count;
	if (count > grafo.V()) return false;
	_marked[s] = true;
	for (auto w : grafo.adj(s)) {
	    if (w != last)
		if (!_marked[w]) {
		    if (!resuelve(w, count, s, _marked)) return false;
		} else return false;

	}
	return true;
    }

public:

    ArbolLibre(Grafo g) : grafo(g), libre(false) {
	resuelve();
    };

    bool esLibre() {
	return libre;
    };

};

#endif	/* ARBOLLIBRE_H */