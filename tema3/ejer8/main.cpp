/*
 * Grupo TAIS16, Samuel Lapuente Jiménez, Alvar David Soler Rus
 *
 * Ejercicio 15. Tema 3.
 *
 */


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include "Repartiendo.h"

/**
 * Creación del grafo
 * @return Grafo construido
 */
GrafoDirigidoValorado<int> leerGrafo(int const _v, int & origen, std::vector<int> & destinos) {
    int e, v, w, c;
    std::cin >> e;
    GrafoDirigidoValorado<int> g(_v);
    for (int i = 0; i < e; ++i) {
	std::cin >> v;
	std::cin >> w;
	std::cin >> c;
	AristaDirigida<int> a(v - 1, w - 1, c);
	g.ponArista(a);
    }
    std::cin >> origen;
    std::cin >> e;
    for (int i = 0; i < e; ++i) {
	int a;
	std::cin >> a;
	destinos.push_back(a);
    }

    return g;

}

void resolverCaso() {
    unsigned int v;

    while (std::cin) {
	std::cin >> v;
	int origen;
	std::vector<int> destinos;
	auto grafo = leerGrafo(v, origen, destinos);
	Repartiendo r(grafo, origen, destinos);

	int aux = r.getEsfuerzoMinimo();
	if (aux > 0) std::cout << aux << std::endl;
	else std::cout << "Imposible" << std::endl;




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