/*
* Grupo TAIS16, Samuel Lapuente Jiménez, Alvar David Soler Rus
*
* Ejercicio 12. Tema 3.
*
*/


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include "Arborescencia.h"
#include "GrafoDirigido.h"

/**
* Creación del grafo
* @return Grafo construido
*/
GrafoDirigido leerGrafo(int const _v) {
	int e, v, w;
	std::cin >> e;
	GrafoDirigido g(_v);
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
		Arborescencia arb(grafo);
		if (arb.getRaiz() == -1) {
			std::cout << "NO" << std::endl;
		}
		else{
			std::cout << "SI " << arb.getRaiz() << std::endl;
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