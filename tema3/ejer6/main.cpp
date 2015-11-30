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
#include "ManchasCrecientes.h"

void resolverCaso() {
    unsigned int _f, _c;

    while (std::cin) {
	_f = 0;
	_c = 0;
	std::cin >> _f;
	std::cin >> _c;
	ManchasCrecientes mc(_f, _c);
	if (_c == 0 && _f == 0) break;
	std::cout << mc.getComponenteMayor();
	while (mc.leerMancha()) {
	    std::cout << " " << mc.getComponenteMayor();
	}
	std::cout << std::endl;

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