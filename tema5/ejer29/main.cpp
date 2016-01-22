/**
 * TAIS16. Álvar Soler y Samuel Lapuente
 * Ejercicio 29.
 *
 **/
#include <iostream>
#include <climits>
#include <fstream>
#include "Matriz.h"

/**
 * caso base
 * coste(i, i+1) = alquiler(i, i+1)
 * recursiva
 * coste(i, j) = min { alquiler(i, j), (i < k < j) {coste(i, k) + coste(k, j)} }
 * 
 * 
 */
Matriz<int> canoas(Matriz<int> const &alquiler) {
    Matriz<int> coste = alquiler;
    size_t N = alquiler.numcols();
    for (size_t d = 2; d <= N - 1; ++d) {
	for (size_t i = 1; i <= N - d; ++i) {
	    size_t j = i + d;
	    for (size_t k = i + 1; k <= j - 1; ++k) {
		coste[i][j] = std::min(coste[i][j], coste[i][k] + coste[k][j]);
	    }
	}
    }
    return coste;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif
    int n;

    std::cin >> n;

    while (std::cin) {
	Matriz<int> alquiler(n + 1, n + 1, INT_MAX);

	for (size_t i = 1; i < n + 1; ++i) {
	    for (size_t j = i + 1; j < n + 1; ++j) {
		std::cin >> alquiler[i][j];
	    }
	}

	Matriz<int> c = canoas(alquiler);

	for (size_t i = 1; i < n + 1; ++i) {
	    for (size_t j = i + 1; j < n + 1; ++j) {
		std::cout << c[i][j];
		if (j < n) std::cout << " ";
	    }
	    if (i < n)
		std::cout << std::endl;
	}
	std::cin >> n;
    }

#ifndef DOMJUDGE

    std::cin.rdbuf(cinbuf); //reset to standard input again

    system("PAUSE");
#endif
    return 0;
}
