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
struct Par {
	int origen;
	int destino;
};

int getDestino(int v, std::vector<Par> atajos){
	for (Par par : atajos){
		if (par.origen == v) return par.destino;
	}
}


SerpientesEscaleras leerGrafo(int const _v) {
	int s, e, v, w, k;
	int tam = _v * _v;
	GrafoDirigido g(tam);
	std::vector<Par> atajos;
	std::vector<bool> hayAtajos(_v * _v, false);
	std::cin >> k;
	std::cin >> s;
	std::cin >> e;
	for (int i = 0; i < s + e; ++i) {
		std::cin >> v;
		std::cin >> w;
		Par p;
		p.origen = v - 1;
		p.destino = w - 1;
		atajos.push_back(p);
		hayAtajos[v - 1] = true;
	}
	int paso;
	for (int j = 0; j < g.V() - 1; ++j) {
		if (!hayAtajos[j]){
			if ((g.V() - j) > k){
				paso = k;
			}
			else paso = g.V() - j;

			for (int z = 1; z <= paso && j+z < tam; ++z){
				if (!hayAtajos[j + z]) g.ponArista(j, j + z);
				else {
					g.ponArista(j, getDestino(j + z, atajos));
				}
			}

		}
	}
	SerpientesEscaleras se(g);
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
