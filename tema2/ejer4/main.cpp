/*
 * Grupo TAIS16, Samuel Lapuente Jiménez, Alvar David Soler Rus
 *
 * Ejercicio 9. Tema 2.
 *
 */
#include <fstream>
#include <cstdlib>
#include "ColaMedianas.h"
/**
 * Complejidad O(nlogn). Logarítmica al insertar y n al recorrer, siendo n el número de parejas de pájaros.
 */
void resolverCaso() {
    unsigned long long int n;
    std::cin >> n;

    unsigned int m;
    std::cin >> m;
    while (m != 0) {
	ColaMedianas cola;
	cola.inserta(n);
	for (unsigned int i = 0; i < m; ++i) {
	    std::cin >> n;
	    cola.inserta(n);
	    std::cin >> n;
	    cola.inserta(n);
	    std::cout << cola.mediana();
	    if (i + 1 < m) std::cout << " ";
	}
	std::cin >> n;
	std::cin >> m;
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