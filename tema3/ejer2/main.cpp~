/*
 * Grupo TAIS16, Samuel Lapuente Jiménez, Alvar David Soler Rus
 * 
 * Ejercicio 11. Tema 3.
 * 
 */


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include "Grafo.h"

/**
 * Creación del grafo
 * @return Grafo construido
 */
Grafo leerGrafo(int const _v) {
    int e, v, w;
    std::cin >> e;
    Grafo g(_v);
    for (int i = 0; i < e; ++i) {
	std::cin >> v;
	std::cin >> w;
	g.ponArista(v, w);
    }

    return g;

}

struct Nodo {
    bool visitado;
    int idConjunto;
};


bool resuelve(Grafo const & grafo, size_t s, size_t &count, size_t last, std::vector<Nodo> _marked) {
    Nodo n;
    n.visitado = true;
    ++count;
    if (last == s) n.idConjunto = 0;
    else {
	if (_marked[last].idConjunto == 0) {
	    n.idConjunto = 1;
	} else n.idConjunto = 0;
    }
    _marked[s] = n;
    for (auto w : grafo.adj(s)) {
	if (w != last) {
	    if (!_marked[w].visitado) {
		if (!resuelve(grafo, w, count, s, _marked))
		    return false;
	    } else if (_marked[w].idConjunto == _marked[s].idConjunto) {
		return false;
	    }
	}
    }
    return true;
}

bool resuelve(Grafo const & grafo) {
    std::vector<Nodo> _marked(grafo.V());
    size_t s = 0, count = 0;
    
    return resuelve(grafo, s, count, 0, _marked);

}

void resolverCaso() {
    int v;
    std::cin >> v;
    while (std::cin) {
	auto grafo = leerGrafo(v);
	if (resuelve(grafo)) {
	    std::cout << "SI" << std::endl;
	} else {
	    std::cout << "NO" << std::endl;
	}
	std::cin >> v;
    }
}

int main() {
#ifndef DOMJUDGE

    std::ifstream in("casos.txt");

    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif

    resolverCaso();

#ifndef DOMJUDGE

    std::cin.rdbuf(cinbuf); //reset to standard input again

    //char ch;

    //std::cin >> ch;

    system("PAUSE");

#endif

    return 0;
}