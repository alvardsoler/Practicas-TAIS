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
#include "ArbolBipartito.h"

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


void resolverCaso() {
    int v;
    std::cin >> v;
    while (std::cin) {
	auto grafo = leerGrafo(v);
	ArbolBipartito ab(grafo);
	if (ab.esBipartito()) {
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

    system("PAUSE");

#endif

    return 0;
}