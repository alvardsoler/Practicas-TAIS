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
#include "Manchas.h"

/**
* Creación del grafo
* @return Grafo construido
*/
Grafo leerGrafo(int const _f, bool  & hayManchas) {
	int _c;
	char _m; 
	std::cin >> _c;
	std::vector < std::vector<bool>> _marked(_f, std::vector<bool>(_c, false));
	Grafo g(_f * _c);
	std::cin.get(_m);
	for (int i = 0; i < _f; ++i) {
		for (int j = 0; j < _c; ++j) {
			std::cin.get(_m);
			if (_m == '#') {
				hayManchas = true;
				_marked[i][j] = true;
				if (i > 0) {
					if (_marked[i - 1][j]) {
						g.ponArista(i * _c + j, ((i - 1) * _c) + j);
					}

				}
				if (j > 0)
					if (_marked[i][j - 1]) {
						g.ponArista(i * _c + j, i * _c + (j - 1));
					}
			}
		}
		std::cin.get(_m);
	}
	
	
	return g;

}

void resolverCaso() {
	int f;
	std::cin >> f;
	while (std::cin) {
		bool hayManchas = false;
		auto grafo = leerGrafo(f,hayManchas);
		if (!hayManchas) std::cout << 0 << std::endl;
		else {
			Manchas manchas(grafo);
			std::cout << manchas.getComponenteMayor() << std::endl;
		}
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
