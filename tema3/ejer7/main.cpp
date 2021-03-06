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
#include "BarroCity.h"

/**
 * Creación del grafo
 * @return Grafo construido
 */
GrafoValorado<int> leerGrafo(int const _v) {
    int e, v, w, c;
    std::cin >> e;
    GrafoValorado<int> g(_v);
    for (int i = 0; i < e; ++i) {
	std::cin >> v;
	std::cin >> w;
	std::cin >> c;
	Arista<int> a(v - 1, w - 1, c);
	g.ponArista(a);
    }

    return g;

}

void resolverCaso() {
    int f;
    std::cin >> f;
    while (std::cin) {
	auto grafo = leerGrafo(f);
	BarroCity barro(grafo);
	if (barro.getCoste() >= 0)
	    std::cout << barro.getCoste() << std::endl;
	else
	    std::cout << "Imposible" << std::endl;
	std::cin >> f;
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
