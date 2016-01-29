/*
 * TAIS16 Alvar David Soler Rus y Samuel Lapuente Jiménez ejercicio 31
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include "Matriz.h"

#define MAX 1e7

int monedas(std::vector<int> & monedas, std::vector<int> & cantidad, int const precio) {
    size_t n = monedas.size();
    Matriz<int> matriz(n + 1, precio + 1, MAX);
    matriz[0][0] = 0;
    for (size_t i = 1; i <= n; ++i) {
	matriz[i][0] = 0;
	for (size_t j = 1; j <= precio; ++j) {
	    if (j < monedas[i - 1]) {
		matriz[i][j] = matriz[i - 1][j];
	    } else {
		matriz[i][j] = matriz[i - 1][j];
		size_t temp = 1e9;

		for (size_t k = 1; k <= cantidad[i - 1] && j - k * monedas[i - 1] >= 0 && j - k * monedas[i - 1] <= precio; ++k) {
		    temp = matriz[i - 1][j - k * monedas[i - 1]] + k;
		    if (temp < matriz[i][j]) {
			matriz[i][j] = temp;
		    }
		}
	    }
	}
    }    
    
    return matriz[n][precio];
}

int main() {
#ifndef DOMJUDGE

    std::ifstream in("casos.txt");

    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif

    int n, C;
    std::cin >> n;
    while (std::cin) {
	std::vector<int> m(n), cantidades(n);
	for (size_t i = 0; i < n; ++i) std::cin >> m[i];
	for (size_t i = 0; i < n; ++i) std::cin >> cantidades[i];
	std::cin >> C;
	size_t r = monedas(m, cantidades, C);
	if (r != MAX)
	    std::cout << "SI " << r << std::endl;
	else
	    std::cout << "NO" << std::endl;
	std::cin >> n;
    }

#ifndef DOMJUDGE

    std::cin.rdbuf(cinbuf); //reset to standard input again


    system("PAUSE");

#endif

    return 0;
}

