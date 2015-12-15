/**
* TAIS16. Álvar Soler y Samuel Lapuente
* Ejercicio 24.
*
**/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "PriorityQueue.h"

struct conferencia {
	int comienzo;
	int fin;
	bool operator<(const conferencia & rhs) const {
		return comienzo < rhs.comienzo;
	}

	bool operator<=(const conferencia & rhs) const {
		return comienzo <= rhs.comienzo;
	}
};

int resuelve(std::vector<conferencia> const & c, int const n) {
	int totalSalas = 1;
	PriorityQueue<unsigned int> aulaLibre;
	aulaLibre.push(c[0].fin);
	for (size_t i = 1; i < n; ++i) {
		if (c[i].comienzo < aulaLibre.top()) { //si la conferencia que estamos considerando empieza antes que la primera conferencia en acabar, necesitamos otra sala nueva.
			totalSalas++;
			aulaLibre.push(c[i].fin); //si añadimos una sala nueva, estará disponible a la hora que acabe esa conferencia
		}
		else { //si no podemos reutilizar esa sala. Al estar ordenados de menor a mayor por orden de comienzo, siempre nos interesa, de poder, meter la nueva conferencia en la sala que acabe antes.
			aulaLibre.pop(); //a esa hora ya no va a estar libre esa sala porque la hemos asignado.
			aulaLibre.push(c[i].fin); //si la hemos reutilizado, esa sala ahora estará disponible a la hora que acabe la conferencia asignada
		}
	}
	return totalSalas;
}

void resuelveCaso(unsigned int const n) {

	std::vector<conferencia> conf(n);
	int c, f;
	conferencia aux;
	for (size_t i = 0; i < n; ++i) {
		std::cin >> c >> f;
		aux.comienzo = c;
		aux.fin = f;
		conf[i] = aux;
	}

	std::sort(conf.begin(), conf.end()); //ordenamos por comienzo.

	std::cout << resuelve(conf, n) << std::endl;


}

int main() {
#ifndef DOMJUDGE

	std::ifstream in("casos.txt");

	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif
	unsigned int casos;
	std::cin >> casos;
	while (casos != 0) {
		resuelveCaso(casos);
		std::cin >> casos;
	}


#ifndef DOMJUDGE

	std::cin.rdbuf(cinbuf); //reset to standard input again

	system("PAUSE");
#endif
	return 0;
}