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
#include "SerpientesEscaleras.h"
#include "GrafoDirigido.h"


/**
* Creación del grafo
* @return Grafo construido
*/
SerpientesEscaleras leerGrafo(int const _v) {
	int s, e, v, w, k;
	GrafoDirigido g(_v * _v);
	std::vector<int> atajos;
	std::vector<bool> hayAtajos(_v * _v, false);
	std::cin >> k;
	std::cin >> s;
	std::cin >> e;
	for (int i = 0; i < s + e; ++i) {
		std::cin >> v;
		std::cin >> w;
		g.ponArista(v, w);		
		atajos.push_back(v);
		hayAtajos[v] = true;
	}
	for (int j = 0; j < g.V() - 1; ++j) {
		if (!hayAtajos[j]){		
		if (((g.V() - j - 1) / k) < 1) {
			for (int z = 1; z < (g.V() - j); ++z) {
				g.ponArista(j, j + z);
			}

		}
		else
			for (int z = 1; z <= k; ++z) {
				g.ponArista(j, j + z);
			}
		}
	}
	//    for (int j = g.V() - k - 1; j < g.V() - 1; ++j) {
	//	for (int z = 1; z < j; ++z) {
	//	    g.ponArista(j, j + z);
	//	}
	//    }
	SerpientesEscaleras se(g, atajos);
	return se;

}

void resolverCaso() {
	int v;
	std::cin >> v;
	while (v != 0) {
		SerpientesEscaleras se = leerGrafo(v);
		
		std::cout << se.getSaltos() << std::endl;
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
