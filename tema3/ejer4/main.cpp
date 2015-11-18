/*
 * Grupo TAIS16, Samuel Lapuente Jiménez, Alvar David Soler Rus
 * 
 * Ejercicio 13. Tema 3.
 * 
 */


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include "GrafoDirigido.h"

/**
 * Creación del grafo
 * @return Grafo construido
 */
GrafoDirigido leerGrafo(int const _v) {
    int s, e, v, w, k;
    GrafoDirigido g(_v * _v);
    std::cin >> k;
    std::cin >> s;
    std::cin >> e;
    for (int i = 0; i < s + e; ++i) {
	std::cin >> v;
	std::cin >> w;
	g.ponArista(v, w);
    }
    for (int j = 0; j < g.V() - 1; ++j) {
	if (((g.V() - j - 1) / k) < 1) {
	    for (int z = 1; z < (g.V() - j); ++z) {
		g.ponArista(j, j + z);
	    }

	} else
	    for (int z = 1; z <= k; ++z) {
		g.ponArista(j, j + z);
	    }
    }
    //    for (int j = g.V() - k - 1; j < g.V() - 1; ++j) {
    //	for (int z = 1; z < j; ++z) {
    //	    g.ponArista(j, j + z);
    //	}
    //    }
    return g;

}

//int resuelve(GrafoDirigido const & grafo) {
//    DepthFirstDirectedPaths dfdp(grafo, 0);
//    Path camino = dfdp.pathTo(grafo.V() - 1);
//    return camino.size();
//    
//}

int resuelve(GrafoDirigido const & grafo) {
    std::vector<size_t> vec = grafo.adj(0);
    std::vector<size_t>::iterator it2 = vec.begin();
    while (it2 != vec.end())
	std::cout << ' ' << *it2++;

    std::cout << std::endl;
    BreadthFirstDirectedPaths bfdp(grafo, 0);
    
    Path camino = bfdp.pathTo(grafo.V() - 1);
    std::deque<size_t>::iterator it = camino.begin();
    
    while (it != camino.end()){
	
    }
	std::cout << ' ' << *it++;

    return camino.size();
}

void resolverCaso() {
    int v;
    std::cin >> v;
    while (v != 0) {
	auto grafo = leerGrafo(v);

	std::cout << resuelve(grafo) << std::endl;

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
